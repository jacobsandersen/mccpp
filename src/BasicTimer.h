#ifndef MCCPP_BASICTIMER_H
#define MCCPP_BASICTIMER_H


#include <asio/io_context.hpp>
#include <asio/steady_timer.hpp>

class BasicTimer {
public:
    explicit BasicTimer(asio::io_context& context) : m_timer(context) {}

    void start(const std::chrono::seconds& duration, std::function<void()> callback);
    void cancel();
private:
    asio::steady_timer m_timer;
    std::function<void()> m_callback;
};


#endif //MCCPP_BASICTIMER_H
