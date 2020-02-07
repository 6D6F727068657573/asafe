#include <clocale>
#include <iostream>

#include "http.h"
#include "mode.h"
#include "utils.h"
#include "pacman.h"
#include "logging.h"
#include "announce.h"
#include "exceptions.h"

using namespace arch_safeguard;
using namespace arch_safeguard::http;
using namespace arch_safeguard::logging;

std::vector<announcement> fetch() {
    auto client = http_client();
    auto latest_upgrade_time = pacman::latest_upgrade_time();
    auto latest_announcements = std::vector<announcement>();

    auto time = latest_upgrade_time;
    while (time < std::chrono::system_clock::now()) {
        auto url = arch_announce_url(time);
        auto response = client.peek(url);

        if(!response) {
            throw std::runtime_error("cannot connect to arch announce.");
        }

        auto announcements = parse_announcements(*response);
        latest_announcements.insert(latest_announcements.end(),
              std::make_move_iterator(announcements.begin()),
              std::make_move_iterator(announcements.end()));

        time = next_month(time);
    }

    std::sort(latest_announcements.begin(), latest_announcements.end(), [](auto& first, auto& second) {
        return first.date > second.date;
    });

    auto handled_announcement = std::find_if(latest_announcements.rbegin(), latest_announcements.rend(), [&](const auto& announcement) {
        return announcement.date > latest_upgrade_time;
    }).base();

    latest_announcements.erase(handled_announcement, latest_announcements.end());
    return latest_announcements;
}

int check() {
    auto mode = read_mode();
    if(mode == mode::DISABLED) {
        return EXIT_SUCCESS;
    }

    auto announcements = fetch();
    if(announcements.empty()) {
        log(level::INFO) << "No recent announcements detected!";
        return EXIT_SUCCESS;
    }

    log(level::INFO) << "Detected " << announcements.size() << " announcement(s)";
    std::cout << "Detected announcements:\n";
    std::for_each(announcements.begin(), announcements.end(), [](auto& announcement) {
        std::cout << announcement.str() << "\n\n";
    });

    return mode == mode::COMPLAIN ? EXIT_SUCCESS : EXIT_FAILURE;
}

int help() {
    std::cout << "Download all announcements since the last system upgrade.\n"
              << "Usage:\n"
              << "\n"
              << "\t check \n"
              << "\t set-mode <mode>\n"
              << "\n"
              << "Modes:\n"
              << "\n"
              << "\t enforced  - log and exit as failure if recent announcements have been found\n"
              << "\t complain - log and exit as success if recent announcements have been found\n"
              << "\t disabled - do nothing"
              << std::endl;

    return EXIT_SUCCESS;
}

int set_mode(std::string mode_str) {
    write_mode(parse_mode(mode_str));
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {

    try {
        std::setlocale(LC_TIME, "en_US.UTF-8");

        if(argc == 2 && strcmp("check", argv[1]) == 0) {
            return check();
        }

        if(argc == 3 && strcmp("set-mode", argv[1]) == 0) {
            return set_mode(argv[2]);
        }

        return help();

    } catch(const std::exception& e) {
        std::cerr << "An error has occured: '" << e.what() << "'.";
        log(level::ERROR) << e.what();
        return EXIT_FAILURE;
    }
}

