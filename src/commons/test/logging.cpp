#include <memory>
#include <sstream>

#include <catch2/catch.hpp>

#include "logging.h"

bool ends_with(std::string const & value, std::string const & ending){
    if (ending.size() > value.size()) {
        return false;
    }
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

std::string log_some_message(arch_safeguard::logging::level level) {
    using namespace arch_safeguard::logging;

    auto sstream_ptr = new std::ostringstream();
    log_to(std::unique_ptr<std::ostringstream>(sstream_ptr));
    log(level) << "some message";
    return sstream_ptr->str();
}

TEST_CASE("Logging to custom streams.", "[enable]") {
    using namespace arch_safeguard;
    using namespace arch_safeguard::logging;

    SECTION("Formatting of Info messages.") {
        REQUIRE(ends_with(log_some_message(level::INFO), "[INFO] some message"));
    }

    SECTION("Formatting of Warning messages.") {
        REQUIRE(ends_with(log_some_message(level::WARN), "[WARN] some message"));
    }

    SECTION("Formatting of Error messages.") {
       REQUIRE(ends_with(log_some_message(level::ERROR), "[ERROR] some message"));
    }
}

