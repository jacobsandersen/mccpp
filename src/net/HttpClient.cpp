#include <curl/curl.h>
#include <sstream>
#include <iostream>
#include "HttpClient.h"

static size_t write_body(void *contents, size_t size, size_t nmemb, std::string *s) {
    s->append(static_cast<char *>(contents), size*nmemb);
    return size*nmemb;
}

bool HttpClient::get_url(const string& url, const map<string, string>& query_params, std::string *resp_body, int64_t *resp_code) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        return false;
    }

    std::ostringstream os;

    os << url;

    bool first = true;
    for (const auto& entry : query_params) {
        if (first) {
            os << "?" << entry.first << "=" << entry.second;
            first = false;
        } else {
            os << "&" << entry.first << "=" << entry.second;
        }
    }

    std::cout << os.str() << std::endl;

    CURLcode res;
    curl_easy_setopt(curl, CURLOPT_URL, os.str().data());

    if (resp_body != nullptr) {
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_body);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, resp_body);
    }

    res = curl_easy_perform(curl);

    if (resp_code != nullptr) {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, resp_code);
    }

    curl_easy_cleanup(curl);

    return res == CURLE_OK;
}
