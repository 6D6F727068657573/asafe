#include <memory>
#include <string>
#include <chrono>
#include <optional>
#include <stdexcept>
#include <functional>
#include <curl/curl.h>

#include "types.h"

#ifndef HTTP_H
#define HTTP_H

namespace arch_safeguard {

namespace http {

using curl_handle = std::unique_ptr<CURL, std::function<void(CURL*)>>;

struct curl_api_exception : public std::runtime_error {

    explicit curl_api_exception(const std::string& message);

    explicit curl_api_exception(const std::string& message, url url);
};

enum class setting {

    SSL_PEER_VERIFICATION,

    SSL_HOST_VERIFICATION,

    FOLLOW_LOCATION
};

using response = std::optional<std::string>;

class http_client {
    curl_handle curl;

public:
    http_client();

    void enable(setting setting);

    void disable(setting setting);

    void timeout(std::chrono::duration<size_t, std::milli> duraction);

    response peek(const url& url);
};

} // http
} // arch_safeguard

#endif // HTTP_H
