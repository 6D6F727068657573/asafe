#include "types.h"
#include "settings.h"

#ifndef PERSISTENCE_H
#define PERSISTENCE_H

namespace arch_safeguard {

enum class mode {
    ENFORCED,
    COMPLAIN,
    DISABLED
};

mode parse_mode(std::string mode_str);

mode read_mode(const file_path& mode_path = settings::mode_path());

void write_mode(mode mode, const file_path& mode_path = settings::mode_path());

std::ostream& operator<<(std::ostream& stream, mode mode);

timestamp read_timestamp(const file_path& time_path = settings::time_path());

void update_timestamp(const file_path& time_path = settings::time_path());

} // arch_safeguard
#endif // PERSISTENCE_H
