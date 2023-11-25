#ifndef MCCPP_TAGLISTBUILDER_H
#define MCCPP_TAGLISTBUILDER_H

#include <list>
#include <memory>
#include "tag/Tag.h"
#include "tag/TagType.h"
#include "tag/TagByte.h"
#include "tag/TagList.h"
#include "tag/TagCompound.h"
#include "tag/TagShort.h"
#include "tag/TagInt.h"
#include "tag/TagLong.h"
#include "tag/TagFloat.h"
#include "tag/TagDouble.h"
#include "tag/TagByteArray.h"
#include "tag/TagString.h"
#include "tag/TagIntArray.h"
#include "tag/TagLongArray.h"

class TagListBuilder : public std::enable_shared_from_this<TagListBuilder> {
public:
    static std::shared_ptr<TagListBuilder> create(TagType list_type);
    static std::shared_ptr<TagListBuilder> create(icu::UnicodeString name, TagType list_type);
    std::shared_ptr<TagListBuilder> add_byte(int8_t value);
    std::shared_ptr<TagListBuilder> add_short(int16_t value);
    std::shared_ptr<TagListBuilder> add_int(int32_t value);
    std::shared_ptr<TagListBuilder> add_long(int64_t value);
    std::shared_ptr<TagListBuilder> add_float(float value);
    std::shared_ptr<TagListBuilder> add_double(double value);
    std::shared_ptr<TagListBuilder> add_byte_array(std::list<int8_t> value);
    std::shared_ptr<TagListBuilder> add_string(icu::UnicodeString value);
    std::shared_ptr<TagListBuilder> add_list(std::shared_ptr<TagList> value);
    std::shared_ptr<TagListBuilder> add_compound(std::shared_ptr<TagCompound> value);
    std::shared_ptr<TagListBuilder> add_int_array(std::list<int32_t> value);
    std::shared_ptr<TagListBuilder> add_long_array(std::list<int64_t> value);
    TagList build();
    std::shared_ptr<TagList> build_shared();
private:
    TagListBuilder(icu::UnicodeString name, TagType list_type) : m_name(std::move(name)), m_list_type(std::move(list_type)) {}
    icu::UnicodeString m_name;
    TagType m_list_type;
    std::list<std::shared_ptr<Tag>> m_items{};
};

#endif //MCCPP_TAGLISTBUILDER_H
