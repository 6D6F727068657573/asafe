#include "types.h"
#include "settings.h"

#ifndef MODE_H
#define MODE_H

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

} // arch_safeguard
#endif // MODE_H
