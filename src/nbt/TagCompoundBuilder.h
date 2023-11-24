#ifndef MCCPP_TAGCOMPOUNDBUILDER_H
#define MCCPP_TAGCOMPOUNDBUILDER_H

#include <list>
#include <utility>
#include "tag/Tag.h"
#include "tag/TagEnd.h"
#include "tag/TagByte.h"
#include "tag/TagShort.h"
#include "tag/TagInt.h"
#include "tag/TagLong.h"
#include "tag/TagFloat.h"
#include "tag/TagDouble.h"
#include "tag/TagByteArray.h"
#include "tag/TagString.h"
#include "tag/TagList.h"
#include "tag/TagCompound.h"
#include "tag/TagIntArray.h"
#include "tag/TagLongArray.h"

class TagCompoundBuilder : public std::enable_shared_from_this<TagCompoundBuilder> {
public:
    static std::shared_ptr<TagCompoundBuilder> create();
    static std::shared_ptr<TagCompoundBuilder> create(std::wstring name);
    TagCompound end();
    std::shared_ptr<TagCompound> end_shared();
    std::shared_ptr<TagCompoundBuilder> add_byte(std::wstring name, int8_t value);
    std::shared_ptr<TagCompoundBuilder> add_short(std::wstring name, int16_t value);
    std::shared_ptr<TagCompoundBuilder> add_int(std::wstring name, int32_t value);
    std::shared_ptr<TagCompoundBuilder> add_long(std::wstring name, int64_t value);
    std::shared_ptr<TagCompoundBuilder> add_float(std::wstring name, float value);
    std::shared_ptr<TagCompoundBuilder> add_double(std::wstring name, double value);
    std::shared_ptr<TagCompoundBuilder> add_byte_array(std::wstring name, std::list<int8_t> value);
    std::shared_ptr<TagCompoundBuilder> add_string(std::wstring name, std::wstring value);
    std::shared_ptr<TagCompoundBuilder> add_list(std::shared_ptr<TagList> value);
    std::shared_ptr<TagCompoundBuilder> add_compound(std::shared_ptr<TagCompound> value);
    std::shared_ptr<TagCompoundBuilder> add_int_array(std::wstring name, std::list<int32_t> value);
    std::shared_ptr<TagCompoundBuilder> add_long_array(std::wstring name, std::list<int64_t> value);
private:
    explicit TagCompoundBuilder(std::wstring name) : m_name(std::move(name)) {}

    std::wstring m_name{};
    std::list<std::shared_ptr<Tag>> m_items{};
};


#endif //MCCPP_TAGCOMPOUNDBUILDER_H
