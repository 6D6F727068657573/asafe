#include <sstream>

#include "exceptions.h"

namespace arch_safeguard {

std::string file_open_message(const std::string& path) {
    auto stream = std::stringstream();
    stream << "Could not open '" << path << "'.";
    return stream.str();
}

std::string file_open_message(const std::experimental::filesystem::path path) {
    return file_open_message(path.string());
}

std::string file_format_message(const std::string& path, const std::string& message) {
    auto stream = std::stringstream();
    stream << "Wrong file format in '" << path << "': " << message << ".";
    return stream.str();
}

std::string file_format_message(const std::experimental::filesystem::path path, const std::string& message) {
    return file_format_message(path.string(), message);
}

file_open_exception::file_open_exception(const std::string& path)
    : std::runtime_error(file_open_message(path)) {}

file_open_exception::file_open_exception(const std::experimental::filesystem::path& path)
    : std::runtime_error(file_open_message(path)) {}

file_format_exception::file_format_exception(const std::string& path, const std::string& message)
    : std::runtime_error(file_format_message(path, message)) {}

file_format_exception::file_format_exception(const std::experimental::filesystem::path& path, const std::string& message)
    : std::runtime_error(file_format_message(path, message)) {}

} // arch_safeguard

