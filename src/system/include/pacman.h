#include "settings.h"

#ifndef PACMAN_H
#define PACMAN_H

namespace arch_safeguard {
namespace pacman {

file_path locate_log_file_path(file_path pacman_config_path = settings::pacman_config_path());

timestamp read_upgrade_time(const file_path& pacman_log_path);

timestamp latest_upgrade_time();

} // pacman
} // arch_safeguard
#endif // PACMAN_H
