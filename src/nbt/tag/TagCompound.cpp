#include "TagCompound.h"

void TagCompound::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    for (auto& entry : m_items) {
        entry->write(buffer, true);
    }
}

std::list<std::shared_ptr<Tag>> TagCompound::get_items() const {
    return m_items;
}
