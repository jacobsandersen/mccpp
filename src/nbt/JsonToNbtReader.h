#ifndef MCCPP_JSONTONBTREADER_H
#define MCCPP_JSONTONBTREADER_H

#include <fstream>
#include "json/json.h"
#include "tag/Tag.h"
#include "tag/TagCompound.h"
#include "tag/TagList.h"

class JsonToNbtReader {
public:
    explicit JsonToNbtReader(const std::string& file_name);
    std::shared_ptr<TagList> parseJsonAsTagList();
    std::shared_ptr<TagCompound> parseJsonAsTagCompound();
private:
    Json::Value m_json_value;
};


#endif //MCCPP_JSONTONBTREADER_H
