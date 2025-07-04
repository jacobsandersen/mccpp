#include <glog/logging.h>
#include "NetworkManager.h"
#include "../VarInt.h"
#include "../MinecraftServer.h"

void NetworkManager::start()
{
    start_accept();

    const int thread_count = std::max(2u, std::thread::hardware_concurrency());

    LOG(INFO) << "NetworkManager starting " << thread_count << " network worker threads...";
    std::vector<std::thread> threads;
    for (int i = 0; i < thread_count; ++i)
    {
        threads.emplace_back([this]()
        {
            try
            {
                m_context.run();
            }
            catch (const std::exception& err)
            {
                LOG(FATAL) << "Network thread crashed: " << err.what() << std::endl;
                m_context.stop();
            }
        });
    }

    LOG(INFO) << "Worker threads started";
    for (auto& thread : threads)
    {
        thread.join();
    }
}

void NetworkManager::start_accept()
{
    auto conn = std::make_shared<Connection>(m_context);
    m_acceptor.async_accept(*conn->get_socket(), [this, conn](const boost::system::error_code& err)
    {
        if (!err)
        {
            LOG(INFO) << "Connection established from " << conn->get_socket()->remote_endpoint().address().to_string();
            std::thread([this, conn]()
            {
                start_read(conn);
            }).detach();

            start_accept();
        }
        else
        {
            LOG(WARNING) << "Failed to accept connection: " << err.message();
        }
    });
}

void NetworkManager::start_read(const std::shared_ptr<Connection>& conn)
{
    auto buf = std::make_shared<boost::asio::streambuf>();

    LOG(INFO) << "Starting read...";

    boost::asio::async_read(
        *conn->get_socket(),
        *buf,
        boost::asio::transfer_at_least(1),
        [this, conn, buf](const boost::system::error_code& err, const size_t bytes_transferred)
        {
            if (!err)
            {
                std::istream is(buf.get());

                ByteBuffer tmp;
                for (int i = 0; i < bytes_transferred; i++)
                {
                    char raw;
                    is.read(&raw, 1);
                    tmp.write_byte(raw);
                }

                tmp.set_data(conn->decrypt_bytes(tmp.get_data()));
                conn->get_data_buffer().append(tmp);

                process_buffer(conn);
                start_read(conn);
            }
            else
            {
                MinecraftServer::get_server()->remove_player(conn->get_unique_id());
                conn->get_socket()->close();
            }
        });
}

void NetworkManager::process_buffer(const std::shared_ptr<Connection>& conn)
{
    BufferReadContext& ctx = conn->get_read_context();
    ByteBuffer& buffer = conn->get_data_buffer();

    switch (ctx.read_state)
    {
    case BufferReadState::ReadPacketLength:
        {
            LOG(INFO) << "process :: read packet length";
            if (buffer.get_data_length() == 0)
            {
                LOG(INFO) << "nothing left to do";
                return;
            }

            if (!ctx.packet_length)
            {
                ctx.packet_length = std::make_unique<int32_t>(buffer.read_varint());
            }

            LOG(INFO) << "process :: read packet length :: " << *ctx.packet_length;

            if (buffer.get_data_length() < *ctx.packet_length)
            {
                LOG(WARNING) << "process :: read packet length :: buffer's data length is less than packet length";
                return;
            }

            if (conn->get_compress_packets())
            {
                LOG(INFO) << "process :: read packet length -> read data length";
                ctx.read_state = BufferReadState::ReadDataLength;
            }
            else
            {
                LOG(INFO) << "process :: read packet length -> build partial buffer";
                ctx.partial_buffer = std::make_unique<ByteBuffer>();
                ctx.partial_buffer->write_ubytes(buffer.read_ubytes(*ctx.packet_length));
                LOG(INFO) << "process :: read packet length -> read packet id";
                ctx.read_state = BufferReadState::ReadPacketId;
            }

            process_buffer(conn);
            break;
        }
    case BufferReadState::ReadDataLength:
        {
            LOG(INFO) << "process :: read data length";
            if (!ctx.data_length)
            {
                ctx.data_length = std::make_unique<int32_t>(buffer.read_varint());
            }

            if (buffer.get_data_length() < *ctx.data_length && *ctx.data_length != 0)
            {
                LOG(WARNING) << "Remaining buffer data length is less than declared packet data length";
                return;
            }

            LOG(INFO) << "process :: read data length :: " << *ctx.data_length;

            ctx.partial_buffer = std::make_unique<ByteBuffer>();
            ctx.partial_buffer->write_ubytes(
                buffer.read_ubytes(*ctx.packet_length - VarInt::encoding_length(*ctx.data_length)));

            if (*ctx.data_length == 0)
            {
                LOG(INFO) << "process :: read data length -> read packet id";
                ctx.read_state = BufferReadState::ReadPacketId;
            }
            else
            {
                LOG(INFO) << "process :: read data length -> decompress data";
                ctx.read_state = BufferReadState::DecompressData;
            }

            process_buffer(conn);
            break;
        }

    case BufferReadState::DecompressData:
        {
            LOG(INFO) << "process :: decompress data";
            ctx.partial_buffer->decompress_buffer();
            LOG(INFO) << "process :: decompress data -> read packet id";
            ctx.read_state = BufferReadState::ReadPacketId;
            process_buffer(conn);
            break;
        }

    case BufferReadState::ReadPacketId:
        {
            LOG(INFO) << "process :: read packet id";
            ctx.packet_id = std::make_unique<int32_t>(ctx.partial_buffer->read_varint());
            LOG(INFO) << "process :: read packet id :: " << *ctx.packet_id << " (conn state = " << static_cast<int>(conn
                ->get_state()) << ")";
            LOG(INFO) << "process :: read packet id -> handle packet";
            ctx.read_state = BufferReadState::HandlePacket;
            process_buffer(conn);
            break;
        }

    case BufferReadState::HandlePacket:
        {
            LOG(INFO) << "process :: handle packet";
            if (const auto& handlers = *m_packet_handlers.find(conn->get_state())->second; !handlers.contains(
                *ctx.packet_id))
            {
                LOG(WARNING) << "Tried to handle unknown packet " << *ctx.packet_id << " in state " << static_cast<int>(
                    conn->get_state());
            }
            else
            {
                LOG(INFO) << "process :: handle packet :: passing to handler";
                handlers.find(*ctx.packet_id)->second->handle(conn, ctx.partial_buffer);
            }

            LOG(INFO) << "process :: done handle packet, reset and process again";

            ctx.packet_length = nullptr;
            ctx.data_length = nullptr;
            ctx.packet_id = nullptr;
            ctx.partial_buffer = nullptr;
            ctx.read_state = BufferReadState::ReadPacketLength;

            process_buffer(conn);

            break;
        }
    }
}
