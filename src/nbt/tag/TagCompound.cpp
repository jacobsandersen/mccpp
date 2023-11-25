#include <iostream>
#include "TagCompound.h"
#include "TagByte.h"
#include "TagShort.h"
#include "TagInt.h"
#include "TagLong.h"
#include "TagFloat.h"
#include "TagDouble.h"
#include "TagByteArray.h"
#include "TagString.h"
#include "TagList.h"
#include "TagIntArray.h"
#include "TagLongArray.h"

TagCompound TagCompound::read(ByteBuffer &buffer) {
    return read(buffer, true);
}

TagCompound TagCompound::read(ByteBuffer &buffer, bool include_name) {
    std::list<std::shared_ptr<Tag>> items{};

    icu::UnicodeString name = include_name ? buffer.read_string_modified_utf8() : "";

    while (true) {
        if (buffer.get_data_length() == 0) {
            throw std::runtime_error("ByteBuffer ended while reading TagCompound, TagEnd never found.");
        }

        TagType next_type = buffer.read_nbt_tag_type();
        if (next_type == TagType::End) {
            break;
        }

        switch (next_type.get_type_id()) {
            case 1:
                items.push_back(std::make_shared<TagByte>(TagByte::read(buffer)));
                break;
            case 2:
                items.push_back(std::make_shared<TagShort>(TagShort::read(buffer)));
                break;
            case 3:
                items.push_back(std::make_shared<TagInt>(TagInt::read(buffer)));
                break;
            case 4:
                items.push_back(std::make_shared<TagLong>(TagLong::read(buffer)));
                break;
            case 5:
                items.push_back(std::make_shared<TagFloat>(TagFloat::read(buffer)));
                break;
            case 6:
                items.push_back(std::make_shared<TagDouble>(TagDouble::read(buffer)));
                break;
            case 7:
                items.push_back(std::make_shared<TagByteArray>(TagByteArray::read(buffer)));
                break;
            case 8:
                items.push_back(std::make_shared<TagString>(TagString::read(buffer)));
                break;
            case 9:
                items.push_back(std::make_shared<TagList>(TagList::read(buffer)));
                break;
            case 10:
                items.push_back(std::make_shared<TagCompound>(TagCompound::read(buffer)));
                break;
            case 11:
                items.push_back(std::make_shared<TagIntArray>(TagIntArray::read(buffer)));
                break;
            case 12:
                items.push_back(std::make_shared<TagLongArray>(TagLongArray::read(buffer)));
                break;
        }
    }

    return {name, items};
}

void TagCompound::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    for (auto& entry : m_items) {
        entry->write(buffer, true);
    }
}

std::list<std::shared_ptr<Tag>> TagCompound::get_items() const {
    return m_items;
}

icu::UnicodeString TagCompound::to_string(uint8_t indent) {
    icu::UnicodeString indentation;
    for (int i = 0; i < indent; i++) indentation.append("\t");

    int32_t actual_size = static_cast<int32_t>(get_items().back()->get_type() == TagType::End
            ? get_items().size() - 1
            : get_items().size());

    auto str = icu::UnicodeString(Tag::to_string(indent) + " " + icu::UnicodeString::fromUTF8(std::to_string(actual_size)) + " entries");
    str += "\n" + indentation + "{\n";
    for (auto& entry : get_items()) {
        if (entry->get_type() == TagType::End) continue;
        str += entry->to_string(indent + 1) += "\n";
    }
    str += indentation + "}";

    return str;
}
