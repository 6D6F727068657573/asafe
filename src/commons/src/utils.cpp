#include <array>
#include <chrono>
#include <algorithm>

#include "utils.h"

namespace arch_safeguard {

void toupper(std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(), [](auto c) { return std::toupper(c); });
}

bool isnospace(int ch) {return !std::isspace(ch);}

void trim(std::string& str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), isnospace));
    str.erase(std::find_if(str.rbegin(), str.rend(), isnospace).base(), str.end());
}

std::string trim(const std::string& str) {
    auto copy = str;
    trim(copy);
    return copy;
}

std::string_view trim(const std::string_view& str) {
    auto begin = std::find_if(str.begin(), str.end(), isnospace);
    auto end = std::find_if(str.rbegin(), str.rend(), isnospace).base();
    return std::string_view(begin, std::distance(begin, end));
}

bool is_leap_year(int year) {
    return year % 4 == 0 && (year % 400 == 0 || year % 100 != 0);
}

int days_in_month(int month, int year) {
    if(month == 1) {
        return is_leap_year(year) ? 29 : 28;
    }
    return 31 - (month % 2);
}

timestamp next_month(timestamp time) {
    auto timeinfo = std::chrono::system_clock::to_time_t(time);
    auto utc_time_ptr = gmtime(&timeinfo);

    auto day = utc_time_ptr->tm_mday;
    auto year = utc_time_ptr->tm_year;
    auto month = utc_time_ptr->tm_mon;

    auto hours_to_next_month = 24 * (days_in_month(month, year) - day) + 1;
    return time + std::chrono::hours(hours_to_next_month);
}

} // arch_safeguard
