//
// Created by Jacob Andersen on 7/19/25.
//

#include "TagCompoundBuilder.h"

std::shared_ptr<TagCompoundBuilder> TagCompoundBuilder::create(icu::UnicodeString name)
{
    return std::shared_ptr<TagCompoundBuilder>(new TagCompoundBuilder(std::move(name)));
}


TagCompound TagCompoundBuilder::build()
{
    return std::move(m_compound);
}
