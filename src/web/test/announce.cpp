#include <catch2/catch.hpp>

#include "announce.h"

const auto SAMPLE_OCTOBER_2019 = R"V0G0N(
From arch-announce at archlinux.org  Sun Nov 10 21:41:24 2019
From: arch-announce at archlinux.org (Arch Linux: Recent news updates: Giancarlo Razzolini)
Date: Sun, 10 Nov 2019 21:41:24 -0000
Subject: [arch-announce] New kernel packages and mkinitcpio hooks
Message-ID: <157342208436.2629483.1158312855743403539@apollo>

       ...

URL: https://www.archlinux.org/news/new-kernel-packages-and-mkinitcpio-hooks/

From arch-announce at archlinux.org  Mon Nov 25 13:03:45 2019
From: arch-announce at archlinux.org (Arch Linux: Recent news updates: Giancarlo Razzolini)
Date: Mon, 25 Nov 2019 13:03:45 -0000
Subject: [arch-announce] primus_vk>=1.3-1 update requires manual intervention
Message-ID: <157468702595.507.11971706989768642224@apollo.archlinux.org>

        ...

URL: https://www.archlinux.org/news/primus_vk13-1-update-requires-manual-intervention)V0G0N";

TEST_CASE( "Parsing of arch announcements", "[parse_announcements]") {
    using namespace arch_safeguard;

    SECTION( "Test parsing of empty text yields no announcements." ) {
        auto parsed_announcements = parse_announcements("");
        REQUIRE(parsed_announcements.empty());
    }

    SECTION( "Test parsing of empty lines yields no announcements." ) {
        auto parsed_announcements = parse_announcements("\n\n\n");
        REQUIRE(parsed_announcements.empty());
    }

    SECTION( "Test parsing original of original sample." ) {
        auto parsed_announcements = parse_announcements(SAMPLE_OCTOBER_2019);

        auto first_announcement = "Mon, 25 Nov 2019 12:03:45 +0000: primus_vk>=1.3-1 update requires manual intervention\n"
                                  "[https://www.archlinux.org/news/primus_vk13-1-update-requires-manual-intervention]";

        auto second_announcement = "Sun, 10 Nov 2019 20:41:24 +0000: New kernel packages and mkinitcpio hooks\n"
                                   "[https://www.archlinux.org/news/new-kernel-packages-and-mkinitcpio-hooks/]";

        REQUIRE(first_announcement == parsed_announcements[0].str());
        REQUIRE(second_announcement == parsed_announcements[1].str());
        REQUIRE(2 == parsed_announcements.size());
    }
}

TEST_CASE( "Formatting of arch announce url", "[arch_announce_url]") {
    using namespace arch_safeguard;

    // 9th November, 2019
    auto day = 9;
    auto month = 11;
    auto year = 2019;

    std::tm tm = { /* .tm_sec  = */ 0,
                   /* .tm_min  = */ 0,
                   /* .tm_hour = */ 0,
                   /* .tm_mday = */ day,
                   /* .tm_mon  = */ month - 1,
                   /* .tm_year = */ year - 1900,
                   /* .tm_wday = */ 5,
                   /* .tm_yday = */ 313,
                   /* .tm_idst = */ 0,
                   /* .tm_gmtoff = */ 0,
                   /* .tm_zone = */ "GMT",
                 };
    tm.tm_isdst = -1; // Use DST value from local time zone
    auto some_date_in_november_2019 = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    auto expected_url_november_2019 = "https://lists.archlinux.org/pipermail/arch-announce/2019-November.txt";
    REQUIRE(expected_url_november_2019 == arch_announce_url(some_date_in_november_2019));
}
