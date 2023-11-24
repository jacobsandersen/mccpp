#include "TagList.h"

void TagList::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    buffer.write_ubyte(m_list_type.get_type_id());
    buffer.write_int(htobe32(static_cast<int32_t>(m_items.size())));
    for (auto& entry : m_items) {
        entry->write(buffer, false);
    }
}

TagType TagList::get_list_type() const {
    return m_list_type;
}

std::list<std::shared_ptr<Tag>> TagList::get_items() const {
    return m_items;
}
