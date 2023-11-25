#include "TagListBuilder.h"

static void ensure_eq(const TagType& a, const TagType& b) {
    if (a != b) {
        throw std::domain_error("Tried to add invalid type to TagList");
        //throw std::domain_error("Cannot add " + a.get_type_name() + " to list containing " + b.get_type_name());
    }
}

std::shared_ptr<TagListBuilder> TagListBuilder::create(TagType list_type) {
    return create("", std::move(list_type));
}

std::shared_ptr<TagListBuilder> TagListBuilder::create(icu::UnicodeString name, TagType list_type) {
    return std::shared_ptr<TagListBuilder>(new TagListBuilder(std::move(name), std::move(list_type)));
}

std::shared_ptr<TagListBuilder> TagListBuilder::add_byte(int8_t value) {
    ensure_eq(TagType::Byte, m_list_type);
    m_items.push_back(std::make_shared<TagByte>("", value));
    return shared_from_this();
}

std::shared_ptr<TagListBuilder> TagListBuilder::add_short(int16_t value) {
    ensure_eq(TagType::Short, m_list_type);
    m_items.push_back(std::make_shared<TagShort>("", value));
    return shared_from_this();
}

std::shared_ptr<TagListBuilder> TagListBuilder::add_int(int32_t value) {
    ensure_eq(TagType::Int, m_list_type);
    m_items.push_back(std::make_shared<TagInt>("", value));
    return shared_from_this();
}

std::shared_ptr<TagListBuilder> TagListBuilder::add_long(int64_t value) {
    ensure_eq(TagType::Long, m_list_type);
    m_items.push_back(std::make_shared<TagLong>("", value));
    return shared_from_this();
}

std::shared_ptr<TagListBuilder> TagListBuilder::add_float(float value) {
    ensure_eq(TagType::Float, m_list_type);
    m_items.push_back(std::make_shared<TagFloat>("", value));
    return shared_from_this();
}

std::shared_ptr<TagListBuilder> TagListBuilder::add_double(double value) {
    ensure_eq(TagType::Double, m_list_type);
    m_items.push_back(std::make_shared<TagDouble>("", value));
    return shared_from_this();
}

std::shared_ptr<TagListBuilder> TagListBuilder::add_byte_array(std::list<int8_t> value) {
    ensure_eq(TagType::ByteArray, m_list_type);
    m_items.push_back(std::make_shared<TagByteArray>("", std::move(value)));
    return shared_from_this();
}

std::shared_ptr<TagListBuilder> TagListBuilder::add_string(icu::UnicodeString value) {
    ensure_eq(TagType::String, m_list_type);
    m_items.push_back(std::make_shared<TagString>("", std::move(value)));
    return shared_from_this();
}

std::shared_ptr<TagListBuilder> TagListBuilder::add_list(std::shared_ptr<TagList> value) {
    ensure_eq(TagType::List, m_list_type);
    m_items.push_back(std::move(value));
    return shared_from_this();
}

std::shared_ptr<TagListBuilder> TagListBuilder::add_compound(std::shared_ptr<TagCompound> value) {
    ensure_eq(TagType::Compound, m_list_type);
    m_items.push_back(std::move(value));
    return shared_from_this();
}

std::shared_ptr<TagListBuilder> TagListBuilder::add_int_array(std::list<int32_t> value) {
    ensure_eq(TagType::IntArray, m_list_type);
    m_items.push_back(std::make_shared<TagIntArray>("", std::move(value)));
    return shared_from_this();
}

std::shared_ptr<TagListBuilder> TagListBuilder::add_long_array(std::list<int64_t> value) {
    ensure_eq(TagType::LongArray, m_list_type);
    m_items.push_back(std::make_shared<TagLongArray>("", std::move(value)));
    return shared_from_this();
}

TagList TagListBuilder::build() {
    return {std::move(m_name), m_list_type, std::move(m_items)};
}

std::shared_ptr<TagList> TagListBuilder::build_shared() {
    return std::make_shared<TagList>(build());
}
