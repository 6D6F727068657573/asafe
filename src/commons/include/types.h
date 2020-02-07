#include <chrono>
#include <string>

#ifndef TYPES_H
#define TYPES_H

namespace arch_safeguard {

using url = std::string;
using command = std::string;
using file_path = std::string;
using timestamp = std::chrono::time_point<std::chrono::system_clock>;

} // arch_safeguard
#endif // TYPES_H
