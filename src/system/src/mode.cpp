#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#include "utils.h"
#include "mode.h"
#include "exceptions.h"

namespace arch_safeguard {

std::string read_file(const file_path& mode_path) {
    auto mode_file_stream = std::ifstream(mode_path);
    if(!mode_file_stream) {
        throw file_open_exception(mode_path);
    }

    auto stream_begin = std::istreambuf_iterator<char>(mode_file_stream);
    auto stream_end = std::istreambuf_iterator<char>();
    return std::string(stream_begin, stream_end);
}

const auto STRING2STATUS = [](){
    return std::unordered_map<std::string, mode>({{"ENFORCED", mode::ENFORCED},
                                                    {"COMPLAIN", mode::COMPLAIN},
                                                    {"DISABLED", mode::DISABLED}});
}();

mode parse_mode(std::string mode_string) {
    trim(mode_string);
    toupper(mode_string);

    auto mode = STRING2STATUS.find(mode_string);
    if(mode == STRING2STATUS.end()) {
        throw std::runtime_error("Mode not recognized: " + mode_string);
    }

    return mode->second;
}

mode read_mode(const file_path& mode_path) {
    auto mode_string = read_file(mode_path);
    trim(mode_string);

    auto handle = STRING2STATUS.find(mode_string);
    if(handle == STRING2STATUS.end()) {
        throw file_format_exception(mode_path, "Invalid mode description");
    }
    return handle->second;
}

const auto STATUS2STRING = [](){
    auto array = std::array<std::string, 3>();
    array[static_cast<size_t>(mode::ENFORCED)] = "ENFORCED";
    array[static_cast<size_t>(mode::COMPLAIN)] = "COMPLAIN";
    array[static_cast<size_t>(mode::DISABLED)] = "DISABLED";
    return array;
}();

std::ostream& operator<<(std::ostream& stream, mode mode) {
    return stream << STATUS2STRING[static_cast<size_t>(mode)];
}

void write_mode(mode mode, const file_path& mode_path) {
    auto mode_file_stream = std::ofstream(mode_path);
    if(!mode_file_stream) {
        throw file_open_exception(mode_path);
    }
    mode_file_stream << mode << std::endl;
}


} // arch_safeguard
