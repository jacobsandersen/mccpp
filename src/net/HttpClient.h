#ifndef MCCPP_HTTPCLIENT_H
#define MCCPP_HTTPCLIENT_H

#include <string>
#include <map>

using std::string, std::map;

class HttpClient {
public:
    static bool get_url(const string& url, const map<string, string>& query_params, std::string *resp_body);
};


#endif
