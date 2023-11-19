#include <curl/curl.h>
#include <sstream>
#include <iostream>
#include "HttpClient.h"

static size_t write_body(void *contents, size_t size, size_t nmemb, std::string *s) {
    std::cout << "size: " << size << "; nmemb: " << nmemb << std::endl;
    for (int i = 0; i < size*nmemb; i++) {
        std::cout << static_cast<char*>(contents)[i] << std::endl;
    }

    s->append(static_cast<char *>(contents), size*nmemb);
    return size*nmemb;
}

bool HttpClient::get_url(const string& url, const map<string, string>& query_params, std::string *resp_body) {
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

    CURLcode res;
    curl_easy_setopt(curl, CURLOPT_URL, os.str().data());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_body);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, resp_body);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return res == CURLE_OK;
}
