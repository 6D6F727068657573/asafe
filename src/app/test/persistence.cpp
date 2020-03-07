#include <catch2/catch.hpp>

#include "exceptions.h"
#include "persistence.h"

TEST_CASE("read_mode reads the mode from the filesystem", "[read_mode]" ) {
    using namespace arch_safeguard;

    SECTION( "throw exception if file does not exist" ) {
        auto non_existing_file = file_path("/non/existing/file");
        REQUIRE_THROWS_AS(read_mode(non_existing_file), file_open_exception);
    }

    SECTION( "throws exception if file has wrong format" ) {
        auto invalid_format_file = file_path("files/mode_invalid");
        REQUIRE_THROWS_AS(read_mode(invalid_format_file), file_format_exception);
    }

    SECTION( "parse 'ENFORED' file" ) {
        auto mode_enforced_file = file_path("files/mode_enforced");
        REQUIRE(mode::ENFORCED == read_mode(mode_enforced_file));
    }

    SECTION( "parse 'COMPLAIN' file" ) {
        auto mode_complain_file = file_path("files/mode_complain");
        REQUIRE(mode::COMPLAIN == read_mode(mode_complain_file));
    }

    SECTION( "parse 'DISABLED' file" ) {
        auto mode_disabled_file = file_path("files/mode_disabled");
        REQUIRE(mode::DISABLED == read_mode(mode_disabled_file));
    }
}

TEST_CASE("write_mode writes the mode to the filesystem", "[write_mode]" ) {
    using namespace arch_safeguard;

    auto writable_file = file_path("files/mode_write");

    SECTION( "write mode overrides the file content" ) {
        write_mode(mode::ENFORCED, writable_file);
        REQUIRE(mode::ENFORCED == read_mode(writable_file));

        write_mode(mode::COMPLAIN, writable_file);
        REQUIRE(mode::COMPLAIN == read_mode(writable_file));

        write_mode(mode::DISABLED, writable_file);
        REQUIRE(mode::DISABLED == read_mode(writable_file));
    }
}

TEST_CASE("read_timestamp reads the timestamp from the filesystem", "[read_timestamp]" ) {
    using namespace arch_safeguard;

    SECTION( "parse normal file" ) {
        auto writable_file = file_path("files/time_normal");
	auto timestamp = read_timestamp(writable_file);
	auto ctimestamp = std::chrono::system_clock::to_time_t(timestamp);
	auto expected_time = std::string("Sat Feb  3 04:05:06 2001\n");
        REQUIRE(expected_time == std::ctime(&ctimestamp));
    }
}
