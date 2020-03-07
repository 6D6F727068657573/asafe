#include <regex>

#include "types.h"

#ifndef SETTINGS_H
#define SETTINGS_H

namespace arch_safeguard {

constexpr auto LOG_PATH = "/var/log/asafe.log";
constexpr auto MODE_PATH = "/usr/share/asafe/mode";
constexpr auto TIME_PATH = "/usr/share/asafe/time";

const auto ARCH_ANNOUNCE_URL_FORMAT = "https://lists.archlinux.org/pipermail/arch-announce/%Y-%B.txt";
const auto ARCH_ANNOUNCE_DATE_FORMAT = "%a, %d %b %Y %T %z"; // Sun, 10 Nov 2019 21:41:24 -0000


namespace settings {

inline file_path log_path() { return file_path(LOG_PATH); }

inline file_path mode_path() { return file_path(MODE_PATH); }

inline file_path time_path() { return file_path(TIME_PATH); }

inline const char* arch_announce_url_format() { return ARCH_ANNOUNCE_URL_FORMAT; }

inline const char* arch_announce_date_format() { return ARCH_ANNOUNCE_DATE_FORMAT; }

} // settings
} // arch_safeguard
#endif // SETTINGS_H
