#include "TagCompoundBuilder.h"

std::shared_ptr<TagCompoundBuilder> TagCompoundBuilder::create() {
    return create(L"");
}

std::shared_ptr<TagCompoundBuilder> TagCompoundBuilder::create(std::wstring name) {
    return std::shared_ptr<TagCompoundBuilder>(new TagCompoundBuilder(std::move(name)));
}

TagCompound TagCompoundBuilder::end() {
    m_items.push_back(std::make_shared<TagEnd>());
    return {m_name, m_items};
}

std::shared_ptr<TagCompound> TagCompoundBuilder::end_shared() {
    return std::make_shared<TagCompound>(end());
}

std::shared_ptr<TagCompoundBuilder> TagCompoundBuilder::add_byte(std::wstring name, int8_t value) {
    m_items.push_back(std::make_shared<TagByte>(std::move(name), value));
    return shared_from_this();
}

std::shared_ptr<TagCompoundBuilder> TagCompoundBuilder::add_short(std::wstring name, int16_t value) {
    m_items.push_back(std::make_shared<TagShort>(std::move(name), value));
    return shared_from_this();
}

std::shared_ptr<TagCompoundBuilder> TagCompoundBuilder::add_int(std::wstring name, int32_t value) {
    m_items.push_back(std::make_shared<TagInt>(std::move(name), value));
    return shared_from_this();
}

std::shared_ptr<TagCompoundBuilder> TagCompoundBuilder::add_long(std::wstring name, int64_t value) {
    m_items.push_back(std::make_shared<TagLong>(std::move(name), value));
    return shared_from_this();
}

std::shared_ptr<TagCompoundBuilder> TagCompoundBuilder::add_float(std::wstring name, float value) {
    m_items.push_back(std::make_shared<TagFloat>(std::move(name), value));
    return shared_from_this();
}

std::shared_ptr<TagCompoundBuilder> TagCompoundBuilder::add_double(std::wstring name, double value) {
    m_items.push_back(std::make_shared<TagDouble>(std::move(name), value));
    return shared_from_this();
}

std::shared_ptr<TagCompoundBuilder> TagCompoundBuilder::add_byte_array(std::wstring name, std::list<int8_t> value) {
    m_items.push_back(std::make_shared<TagByteArray>(std::move(name), std::move(value)));
    return shared_from_this();
}

std::shared_ptr<TagCompoundBuilder> TagCompoundBuilder::add_string(std::wstring name, std::wstring value) {
    m_items.push_back(std::make_shared<TagString>(std::move(name), std::move(value)));
    return shared_from_this();
}

std::shared_ptr<TagCompoundBuilder> TagCompoundBuilder::add_list(std::shared_ptr<TagList> value) {
    m_items.push_back(std::move(value));
    return shared_from_this();
}

std::shared_ptr<TagCompoundBuilder> TagCompoundBuilder::add_compound(std::shared_ptr<TagCompound> value) {
    m_items.push_back(std::move(value));
    return shared_from_this();
}

std::shared_ptr<TagCompoundBuilder> TagCompoundBuilder::add_int_array(std::wstring name, std::list<int32_t> value) {
    m_items.push_back(std::make_shared<TagIntArray>(std::move(name), std::move(value)));
    return shared_from_this();
}

std::shared_ptr<TagCompoundBuilder> TagCompoundBuilder::add_long_array(std::wstring name, std::list<int64_t> value) {
    m_items.push_back(std::make_shared<TagLongArray>(std::move(name), std::move(value)));
    return shared_from_this();
}
