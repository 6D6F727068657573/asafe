#include <tuple>
#include <array>
#include <string>
#include <string_view>

#include "types.h"

#ifndef UTILS_H
#define UTILS_H

namespace arch_safeguard {

void toupper(std::string& str);

void trim(std::string& str);

std::string trim(const std::string& str);

std::string_view trim(const std::string_view& str);

template<class Base, class Tuple>
constexpr auto pointer_array(const Tuple& tuple) {
    using array_t = std::array<const Base*, std::tuple_size<Tuple>::value>;
    return std::apply([](auto& ... x){ return array_t{static_cast<const Base*>(&x) ... }; }, tuple);
}

timestamp next_month(timestamp time);

} // arch_safeguard
#endif // UTILS_H
