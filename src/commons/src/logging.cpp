#include <mutex>
#include <array>
#include <memory>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <functional>

#include "logging.h"
#include "settings.h"

namespace arch_safeguard {
namespace logging {

log_handle open_log_file() {
    return std::make_unique<std::ofstream>(LOG_PATH, std::ios::app);
}

using initializer = std::function<log_handle()>;

log_handle handle = nullptr;
initializer init = open_log_file;

void log_to(log_handle new_handle) {
    handle = std::move(new_handle);
    init = [&]() { return std::move(handle); };
}

stream& get_stream() {
    handle = init();
    init = [&]() { return std::move(handle); };
    return *handle;
}

const auto LEVEL2STRING = [](){
     auto array = std::array<std::string, 3>();
     array[static_cast<size_t>(level::INFO)] = " [INFO] ";
     array[static_cast<size_t>(level::WARN)] = " [WARN] ";
     array[static_cast<size_t>(level::ERROR)] = " [ERROR] ";
     return array;
}();

stream& log(level level) {
    auto time = std::time(nullptr);
    return get_stream() << std::put_time(std::localtime(&time), "%c")
                        << LEVEL2STRING[static_cast<size_t>(level)];
}

} // log
} // arch_safeguard
