#include <string>
#include <fstream>

#include "pacman.h"
#include "settings.h"
#include "exceptions.h"

namespace arch_safeguard {
namespace pacman {

std::string find_last_line_match(const file_path& file_path, const std::regex& regex, const size_t group_id=0) {
    auto file_stream = std::ifstream(file_path);
    if(!file_stream) {
        throw file_open_exception(file_path);
    }

    auto last_match = std::string();
    for (std::string line; std::getline(file_stream, line); ) {
        auto match = std::smatch();
        bool is_match = std::regex_match(line, match, regex);
        if(is_match) {
            last_match = std::move(match[group_id]);
        }
    }

    return last_match;
}

const auto log_config_pattern = R"(\s*LogFile\s*=\s*(.+)\s*)";
const auto log_config_regex = std::regex(log_config_pattern);

file_path locate_log_file_path(file_path pacman_config_path) {
    auto configured_path_match = find_last_line_match(pacman_config_path, log_config_regex, 1);
    if(configured_path_match.empty()) {
        return settings::pacman_default_log_path();
    }

    return file_path(configured_path_match);
}

timestamp parse_time(const std::string& formatted_date) {
    std::tm tm = {};
    strptime(formatted_date.c_str(), settings::pacman_log_time_format(), &tm);
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

const auto upgrade_entry_pattern = R"(\[([^\s^\]]+)\] \[PACMAN\] starting full system upgrade)";
const auto upgrade_entry_regex = std::regex(upgrade_entry_pattern);

timestamp read_upgrade_time(const file_path& pacman_log_path) {
    const auto PACMAN_UPGRADE_COMMAND = command("pacman -Syu --noconfirm --noprogressbar");
    auto formatted_timestamp_match = find_last_line_match(pacman_log_path, upgrade_entry_regex, 1);
    if(formatted_timestamp_match.empty()) {
        throw file_format_exception(pacman_log_path, "No system upgrade found");
    }

    return parse_time(formatted_timestamp_match);
}

timestamp latest_upgrade_time() {
    return read_upgrade_time(locate_log_file_path());
}

} // pacman
} // arch_safeguard
