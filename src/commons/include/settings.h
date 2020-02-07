#include <regex>

#include "types.h"

#ifndef SETTINGS_H
#define SETTINGS_H

namespace arch_safeguard {

constexpr auto LOG_PATH = "/var/log/arch-safeguard.log";
constexpr auto MODE_PATH = "/var/cache/asafe/mode";

const auto PACMAN_CONFIG_PATH = "/etc/pacman.conf";
const auto PACMAN_LOG_TIMEFORMAT = "%FT%T%z";
const auto PACMAN_DEFAULT_LOG_PATH = "/var/log/pacman.log";

const auto ARCH_ANNOUNCE_URL_FORMAT = "https://lists.archlinux.org/pipermail/arch-announce/%Y-%B.txt";
const auto ARCH_ANNOUNCE_DATE_FORMAT = "%a, %d %b %Y %T %z"; // Sun, 10 Nov 2019 21:41:24 -0000


namespace settings {

inline file_path log_path() { return file_path(LOG_PATH); }

inline file_path mode_path() { return file_path(MODE_PATH); }

inline file_path pacman_config_path() {return file_path(PACMAN_CONFIG_PATH); }

inline file_path pacman_default_log_path() {return file_path(PACMAN_DEFAULT_LOG_PATH); }

inline const char* pacman_log_time_format() { return PACMAN_LOG_TIMEFORMAT; }

inline const char* arch_announce_url_format() { return ARCH_ANNOUNCE_URL_FORMAT; }

inline const char* arch_announce_date_format() { return ARCH_ANNOUNCE_DATE_FORMAT; }

} // settings
} // arch_safeguard
#endif // SETTINGS_H
