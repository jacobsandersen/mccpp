#include "JsonToNbtReader.h"
#include "TagCompoundBuilder.h"
#include "TagListBuilder.h"



JsonToNbtReader::JsonToNbtReader(const std::string &file_name) {
    std::ifstream is(file_name);
    if (!is.is_open() || is.fail()) {
        throw std::invalid_argument("JsonToNbtReader failed to open file");
    }

    Json::Reader reader;
    if (!reader.parse(is, m_json_value)) {
        throw std::runtime_error("JsonToNbtReader failed to parse JSON data");
    }

    is.close();
}

std::shared_ptr<TagList> JsonToNbtReader::parseJsonAsTagList() {
    return {};
}

std::shared_ptr<TagCompound> JsonToNbtReader::parseJsonAsTagCompound() {
    return {};
}

//std::shared_ptr<Tag> JsonToNbtReader::convertToTag() {
//    return convertToTag(m_json_value);
//}
//
//std::shared_ptr<Tag> JsonToNbtReader::convertToTag(const Json::Value& value) {
//    std::shared_ptr<Tag> tag;
//
//    if (value.isObject()) {
//        auto builder = TagCompoundBuilder::create();
//        for (auto& inner_value : value) {
//            std::shared_ptr<Tag> inner_tag = convertToTag(inner_value);
//            switch (inner_tag->get_type().get_type_id()) {
//                case 1: {
//                    auto casted = std::dynamic_pointer_cast<TagByte>(inner_tag);
//                    builder = builder->add_byte(casted->get_name(), casted->get_value());
//                    break;
//                }
//                case 2: {
//                    auto casted = std::dynamic_pointer_cast<TagShort>(inner_tag);
//                    builder = builder->add_short(casted->get_name(), casted->get_value());
//                    break;
//                }
//                case 3: {
//                    auto casted = std::dynamic_pointer_cast<TagInt>(inner_tag);
//                    builder = builder->add_int(casted->get_name(), casted->get_value());
//                    break;
//                }
//                case 4: {
//                    auto casted = std::dynamic_pointer_cast<TagLong>(inner_tag);
//                    builder = builder->add_long(casted->get_name(), casted->get_value());
//                    break;
//                }
//                case 5: {
//                    auto casted = std::dynamic_pointer_cast<TagFloat>(inner_tag);
//                    builder = builder->add_float(casted->get_name(), casted->get_value());
//                    break;
//                }
//                case 6: {
//                    auto casted = std::dynamic_pointer_cast<TagDouble>(inner_tag);
//                    builder = builder->add_double(casted->get_name(), casted->get_value());
//                    break;
//                }
//                case 7: {
//                    auto casted = std::dynamic_pointer_cast<TagByteArray>(inner_tag);
//                    builder = builder->add_byte_array(casted->get_name(), casted->get_value());
//                    break;
//                }
//                case 8: {
//                    auto casted = std::dynamic_pointer_cast<TagString>(inner_tag);
//                    builder = builder->add_string(casted->get_name(), casted->get_value());
//                    break;
//                }
//                case 9: {
//                    auto casted = std::dynamic_pointer_cast<TagList>(inner_tag);
//                    builder = builder->add_list(casted);
//                    break;
//                }
//                case 10: {
//                    auto casted = std::dynamic_pointer_cast<TagCompound>(inner_tag);
//                    builder = builder->add_compound(casted);
//                    break;
//                }
//                case 11: {
//                    auto casted = std::dynamic_pointer_cast<TagIntArray>(inner_tag);
//                    builder = builder->add_int_array(casted->get_name(), casted->get_value());
//                    break;
//                }
//                case 12: {
//                    auto casted = std::dynamic_pointer_cast<TagLongArray>(inner_tag);
//                    builder = builder->add_long_array(casted->get_name(), casted->get_value());
//                    break;
//                }
//            }
//        }
//    } else if (value.isArray()) {
//        if (value.empty()) {
//            return TagListBuilder::create(TagType::End)->build_shared();
//        } else {
//            Json::ValueType arrayValueType = value[0].type();
//
//            if (!std::all_of(value.begin(), value.end(), [arrayValueType](const Json::Value& member) {
//                return member.type() == arrayValueType;
//            })) {
//                throw std::runtime_error("JSON Array did not contain all the same JSON type - cannot convert to NBT.");
//            }
//
//            TagType expectedTagType = TagType::End;
//
//            if (arrayValueType == Json::nullValue) {
//                return TagListBuilder::create(TagType::End)->build_shared();
//            } else if (arrayValueType == Json::uintValue || arrayValueType == Json::intValue) {
//                expectedTagType = TagType::expected_tag_type(value[0].asInt64());
//                if (!std::all_of(value.begin(), value.end(), [expectedTagType](const Json::Value& member) {
//                    return TagType::expected_tag_type(member.asInt64()) == expectedTagType;
//                })) {
//                    throw std::runtime_error("JSON array contained various integral types. Each member must all be 8-bits, 16-bits, 32-bits, or 64-bits. It cannot be a mixture. Cannot convert to NBT.");
//                }
//            } else if (arrayValueType == Json::realValue) {
//                expectedTagType = TagType::expected_tag_type(value[0].asDouble());
//                if (!std::all_of(value.begin(), value.end(), [expectedTagType](const Json::Value& member) {
//                    return TagType::expected_tag_type(member.asDouble()) == expectedTagType;
//                })) {
//                    throw std::runtime_error("JSON Array contained all floating points, but they're not all representable in the same floating point type (double or float). They must all be floats, or all be doubles. Cannot convert to NBT.");
//                }
//            } else {
//                switch (arrayValueType) {
//                    case Json::stringValue:
//                        expectedTagType = TagType::String;
//                        break;
//                    case Json::booleanValue:
//                        expectedTagType = TagType::Byte;
//                        break;
//                    case Json::arrayValue:
//                        expectedTagType = TagType::List;
//                        break;
//                    case Json::objectValue:
//                        expectedTagType = TagType::Compound;
//                        break;
//
//                    // handled already
//                    case Json::nullValue:
//                    case Json::intValue:
//                    case Json::uintValue:
//                    case Json::realValue:
//                        break;
//                }
//            }
//
//            for (auto& member : value) {
//            }
//        }
//        auto builder = TagListBuilder::create();
//        for (auto& inner_value : value) {
//            std::shared_ptr<Tag> inner_tag = convertToTag(inner_value);
//            switch (inner_tag->get_type().get_type_id()) {
//                case 1: {
//                    auto casted = std::dynamic_pointer_cast<TagByte>(inner_tag);
//                    builder = builder->add_byte(casted->get_name(), casted->get_value());
//                    break;
//                }
//                case 2: {
//                    auto casted = std::dynamic_pointer_cast<TagShort>(inner_tag);
//                    builder = builder->add_short(casted->get_name(), casted->get_value());
//                    break;
//                }
//                case 3: {
//                    auto casted = std::dynamic_pointer_cast<TagInt>(inner_tag);
//                    builder = builder->add_int(casted->get_name(), casted->get_value());
//                    break;
//                }
//                case 4: {
//                    auto casted = std::dynamic_pointer_cast<TagLong>(inner_tag);
//                    builder = builder->add_long(casted->get_name(), casted->get_value());
//                    break;
//                }
//                case 5: {
//                    auto casted = std::dynamic_pointer_cast<TagFloat>(inner_tag);
//                    builder = builder->add_float(casted->get_name(), casted->get_value());
//                    break;
//                }
//                case 6: {
//                    auto casted = std::dynamic_pointer_cast<TagDouble>(inner_tag);
//                    builder = builder->add_double(casted->get_name(), casted->get_value());
//                    break;
//                }
//                case 7: {
//                    auto casted = std::dynamic_pointer_cast<TagByteArray>(inner_tag);
//                    builder = builder->add_byte_array(casted->get_name(), casted->get_value());
//                    break;
//                }
//                case 8: {
//                    auto casted = std::dynamic_pointer_cast<TagString>(inner_tag);
//                    builder = builder->add_string(casted->get_name(), casted->get_value());
//                    break;
//                }
//                case 9: {
//                    auto casted = std::dynamic_pointer_cast<TagList>(inner_tag);
//                    builder = builder->add_list(casted);
//                    break;
//                }
//                case 10: {
//                    auto casted = std::dynamic_pointer_cast<TagCompound>(inner_tag);
//                    builder = builder->add_compound(casted);
//                    break;
//                }
//                case 11: {
//                    auto casted = std::dynamic_pointer_cast<TagIntArray>(inner_tag);
//                    builder = builder->add_int_array(casted->get_name(), casted->get_value());
//                    break;
//                }
//                case 12: {
//                    auto casted = std::dynamic_pointer_cast<TagLongArray>(inner_tag);
//                    builder = builder->add_long_array(casted->get_name(), casted->get_value());
//                    break;
//                }
//            }
//        }
//    } else if (value.isNumeric()) {
//        if (value.isIntegral()) {
//
//        } else if (value.isDouble()) {
//
//        }
//    } else if (value.isString()) {
//        std::string valueStr = value.asString();
//
//        // a string
//    } else if (value.isBool()) {
//        // bool
//    } else if (value.isNull()) {
//
//    }
//
//    return tag;
//}
