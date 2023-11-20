#ifndef MCCPP_UUIDUTIL_H
#define MCCPP_UUIDUTIL_H

#include <string>
#include <algorithm>
#include <stdexcept>
#include <ios>
#include <iomanip>
#include <uuid.h>

class UUIDUtil {
public:
    static bool valid_undashed_uuid(std::string uuid);

    static std::string canonicalize_uuid(const std::string &uuid_no_dashes);
};

#endif
