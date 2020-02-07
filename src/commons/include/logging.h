#include <string>
#include <ostream>
#include <exception>

#include "settings.h"

#ifndef LOGGING_H
#define LOGGING_H

namespace arch_safeguard {
namespace logging {

using stream = std::ostream;
using log_handle = std::unique_ptr<stream>;

enum class level {
    INFO,
    WARN,
    ERROR
};

void log_to(log_handle handle);

stream& log(level level);

} // log
} // arch_safeguard

#endif // LOGGING_H
