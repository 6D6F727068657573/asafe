#include <array>
#include <atomic>
#include <sstream>

#include "http.h"

namespace arch_safeguard {
namespace http {

std::string error_message(const std::string& message, url url) {
    auto sstream = std::stringstream();
    sstream << message << " host: " << url;
    return sstream.str();
}

curl_api_exception::curl_api_exception(const std::string& message)
    : std::runtime_error(message) {}

curl_api_exception::curl_api_exception(const std::string& message, url host)
    : std::runtime_error(error_message(message, host)) {}

size_t index(setting setting) {
    return static_cast<size_t>(setting);
}

const auto SETTING2CURL_FLAG = []() {
    auto array = std::array<decltype(CURLOPT_SSL_VERIFYPEER), 3>();
    array[index(setting::SSL_PEER_VERIFICATION)] = CURLOPT_SSL_VERIFYPEER;
    array[index(setting::SSL_HOST_VERIFICATION)] = CURLOPT_SSL_VERIFYHOST;
    array[index(setting::FOLLOW_LOCATION)] = CURLOPT_FOLLOWLOCATION;
    return array;
}();

auto curl_flag(setting setting) {
    return SETTING2CURL_FLAG[index(setting)];
}

curl_handle open_handle() {
    static std::atomic_size_t connection_count = 0;

    auto raw_ptr = curl_easy_init();
    if(raw_ptr == nullptr) {
        throw curl_api_exception("Failed to initialize curl handle");
    }

    if((++connection_count) == 0) {
        curl_global_init(CURL_GLOBAL_DEFAULT);
    }

    return curl_handle(raw_ptr, [](CURL* curl) {
        if(curl != nullptr) {
            curl_easy_cleanup(curl);
        }
        if((--connection_count) == 0) {
            curl_global_cleanup();
        }
    });
}

http_client::http_client() : curl(open_handle()) {}

void check(CURLcode code, const char* message) {
    if(code != CURLE_OK) {
        throw curl_api_exception(message);
    }
}

void http_client::enable(setting setting) {
    check(curl_easy_setopt(curl.get(), curl_flag(setting), 1L), "Can't enable setting.");
}

void http_client::disable(setting setting) {
   check(curl_easy_setopt(curl.get(), curl_flag(setting), 0L), "Can't disable setting.");
}

void http_client::timeout(std::chrono::duration<size_t, std::milli> duraction) {
    auto duration_ms = duraction.count();
    check(curl_easy_setopt(curl.get(), CURLOPT_TIMEOUT_MS, duration_ms), "Can't set timout.");
}

size_t write_callback(char *ptr, size_t size, size_t nmemb, std::stringstream *userdata) {
    auto characters = size * nmemb;
    userdata->write(ptr, characters);
    return characters;
}

response http_client::peek(const url& url) {
    auto buffer = std::stringstream();
    auto handle = curl.get();

    check(curl_easy_setopt(handle, CURLOPT_URL, url.c_str()), "Couldn't define url.");
    check(curl_easy_setopt(handle, CURLOPT_WRITEDATA, &buffer), "Couldn't set write data.");
    check(curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_callback), "Couldn't set write function.");

    auto return_status = curl_easy_perform(curl.get());
    return return_status == CURLE_OK ? response(buffer.str()) : std::nullopt;
}

} // http
} // arch_safeguard



