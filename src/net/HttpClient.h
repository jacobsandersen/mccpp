#ifndef MCCPP_HTTPCLIENT_H
#define MCCPP_HTTPCLIENT_H

#include <string>
#include <map>

using std::string, std::string_view, std::map;

class HttpClient
{
public:
    static bool get_url(const string_view&, const map<string, string>&, std::string*, int64_t*);
};


#endif
