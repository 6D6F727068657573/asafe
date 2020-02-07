#include <string>
#include <experimental/filesystem>

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

namespace arch_safeguard {

struct file_open_exception : public std::runtime_error {

    explicit file_open_exception(const std::string& path);

    explicit file_open_exception(const std::experimental::filesystem::path& path);
};

struct file_format_exception : public std::runtime_error {

    explicit file_format_exception(const std::string& path, const std::string& message);

    explicit file_format_exception(const std::experimental::filesystem::path& path, const std::string& message);
};

} // arch_safeguard
#endif // EXCEPTIONS_H
