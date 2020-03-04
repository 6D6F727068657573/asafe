#include <ctime>
#include <catch2/catch.hpp>

#include "pacman.h"
#include "exceptions.h"

TEST_CASE("locate_log_file_path locates the pacman log file", "[locate_log_file_path]" ) {
    using namespace arch_safeguard;
    using namespace arch_safeguard::pacman;

    SECTION( "throws exception if config file is not present" ) {
        auto non_existing_file = file_path("/non/existing/file");
        REQUIRE_THROWS_AS(locate_log_file_path(non_existing_file), file_open_exception);
    }

    SECTION( "returns path from config file if present" ) {
        auto config_file_with_custom_log = file_path("files/pacman_custom_log.conf");
        REQUIRE(file_path("/custom/pacman.log") == locate_log_file_path(config_file_with_custom_log));
    }

    SECTION( "returns default path if config option is not set" ) {
        auto config_file_without_custom_log = file_path("files/pacman_default_log.conf");
        REQUIRE(file_path("/var/log/pacman.log") == locate_log_file_path(config_file_without_custom_log));
    }
}

TEST_CASE("read_upgrade_time parses the latest upgrade time", "[read_upgrade_time]" ) {
    using namespace arch_safeguard;
    using namespace arch_safeguard::pacman;

    SECTION( "throws exception if log file is not present" ) {
        auto non_existing_file = file_path("/non/existing/file");
        REQUIRE_THROWS_AS(read_upgrade_time(non_existing_file), file_open_exception);
    }

    SECTION( "returns latsest/lowest date written in the logfile") {
        using namespace std::chrono;

        auto pacman_log = file_path("files/pacman.log");
        auto upgrade_time = read_upgrade_time(pacman_log);
        auto upgrade_ctime = system_clock::to_time_t(upgrade_time);
        auto expected_time = std::string("Wed Jan  1 20:07:51 2020\n");
        REQUIRE(expected_time== std::ctime(&upgrade_ctime));
    }
}
