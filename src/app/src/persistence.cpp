#include <array>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#include "utils.h"
#include "exceptions.h"
#include "persistence.h"

namespace arch_safeguard {

std::string read_file(const file_path& file_path) {
    auto file_stream = std::ifstream(file_path);
    if(!file_stream) {
        throw file_open_exception(file_path);
    }

    auto stream_begin = std::istreambuf_iterator<char>(file_stream);
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

const auto TIME_FORMAT = "%F %T %z";

timestamp read_timestamp(const file_path& time_path) {
    auto time_str = read_file(time_path); 
    trim(time_str);

    if(time_str.empty()) {
	return std::chrono::system_clock::now();
    }

    std::tm tm = {};
    strptime(time_str.data(), TIME_FORMAT, &tm);
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

void update_timestamp(const file_path& time_path) {
    auto time_file_stream = std::ofstream(time_path);
    if(!time_file_stream) {
    	throw file_open_exception(time_path);
    }
    auto time = std::time(0); 
    time_file_stream << std::put_time(localtime(&time), TIME_FORMAT);
}

} // arch_safeguard
