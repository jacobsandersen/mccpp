#include <iostream>
#include "TagList.h"
#include "TagByte.h"
#include "TagShort.h"
#include "TagInt.h"
#include "TagLong.h"
#include "TagFloat.h"
#include "TagDouble.h"
#include "TagByteArray.h"
#include "TagString.h"
#include "TagCompound.h"
#include "TagIntArray.h"
#include "TagLongArray.h"

TagList TagList::read(ByteBuffer &buffer) {
    return read(buffer, true);
}

TagList TagList::read(ByteBuffer &buffer, bool include_name) {
    std::list<std::shared_ptr<Tag>> items{};

    icu::UnicodeString name = include_name ? buffer.read_string_modified_utf8() : "";
    std::string namestr;
    name.toUTF8String(namestr);

    TagType list_type = buffer.read_nbt_tag_type();

    int32_t length = buffer.read_be_int();
    if (length > 0) {
        if (list_type == TagType::End) {
            throw std::runtime_error("Encountered NBT Tag List with End Type Tag, but length longer than 0.");
        }

        for (int i = 0; i < length; i++) {
            switch (list_type.get_type_id()) {
                case 1:
                    items.push_back(std::make_shared<TagByte>(TagByte::read(buffer, false)));
                    break;
                case 2:
                    items.push_back(std::make_shared<TagShort>(TagShort::read(buffer, false)));
                    break;
                case 3:
                    items.push_back(std::make_shared<TagInt>(TagInt::read(buffer, false)));
                    break;
                case 4:
                    items.push_back(std::make_shared<TagLong>(TagLong::read(buffer, false)));
                    break;
                case 5:
                    items.push_back(std::make_shared<TagFloat>(TagFloat::read(buffer, false)));
                    break;
                case 6:
                    items.push_back(std::make_shared<TagDouble>(TagDouble::read(buffer, false)));
                    break;
                case 7:
                    items.push_back(std::make_shared<TagByteArray>(TagByteArray::read(buffer, false)));
                    break;
                case 8:
                    items.push_back(std::make_shared<TagString>(TagString::read(buffer, false)));
                    break;
                case 9:
                    items.push_back(std::make_shared<TagList>(TagList::read(buffer, false)));
                    break;
                case 10:
                    items.push_back(std::make_shared<TagCompound>(TagCompound::read(buffer, false)));
                    break;
                case 11:
                    items.push_back(std::make_shared<TagIntArray>(TagIntArray::read(buffer, false)));
                    break;
                case 12:
                    items.push_back(std::make_shared<TagLongArray>(TagLongArray::read(buffer, false)));
                    break;
            }
        }
    }

    return {name, list_type, items};
}

void TagList::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    buffer.write_ubyte(m_list_type.get_type_id());
    buffer.write_be_int(static_cast<int32_t>(m_items.size()));
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

icu::UnicodeString TagList::to_string(uint8_t indent) {
    icu::UnicodeString indentation;
    for (int i = 0; i < indent; i++) indentation.append("\t");

    auto str = icu::UnicodeString(Tag::to_string(indent) + " " + icu::UnicodeString::fromUTF8(std::to_string(get_items().size())) + " entries");
    str += "\n" + indentation + "{\n";
    for (auto& entry : get_items()) {
        str += entry->to_string(indent + 1) += "\n";
    }
    str += indentation + "}";

    return str;
}
