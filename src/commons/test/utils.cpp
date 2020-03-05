#include <catch2/catch.hpp>
#include <cstdlib>

#include "utils.h"

TEST_CASE( "Trim removes leading and trailing whitespace.", "[tim]" ) {
    using namespace arch_safeguard;

    SECTION( "Test for nonconst std::string reference." ) {
        auto non_const_string = std::string(" trimmed content ");
        trim(non_const_string);
        REQUIRE("trimmed content" == non_const_string);
    }

    SECTION( "Test for const std::string reference." ) {
        const auto const_string = std::string(" trimmed content ");
        REQUIRE("trimmed content" == trim(const_string));
    }

    SECTION( "Test for const std::string_view reference." ) {
        const auto const_string = std::string(" trimmed content ");
        auto str_view = std::string_view(const_string);
        REQUIRE("trimmed content" == trim(str_view));
    }
}

TEST_CASE( "Construction of pointer array.", "[pointer_array]") {
    using namespace arch_safeguard;

    SECTION( "Test location of pointers matches location of tuple objects." ) {
        auto tuple = std::make_tuple(0, 1, 2);
        auto array = pointer_array<int, decltype (tuple)>(tuple);
        REQUIRE(&std::get<0>(tuple) == array[0]);
        REQUIRE(&std::get<1>(tuple) == array[1]);
        REQUIRE(&std::get<2>(tuple) == array[2]);
    }
}


TEST_CASE( "Calculation of next month", "[next_month]") {
    using namespace arch_safeguard;

    SECTION( "Test increment of timestamp increases by one month" ) {
	std::srand(0);
	auto iterations = 1000;
        auto initial_time = timestamp();

	for(auto i = 0; i < iterations; ++i) {
	    auto time = initial_time + std::chrono::hours(std::rand());
	    auto next_time = next_month(time);

	    auto timeinfo = std::chrono::system_clock::to_time_t(time);
	    auto next_timeinfo = std::chrono::system_clock::to_time_t(next_time);

	    auto month = gmtime(&timeinfo)->tm_mon;
	    auto next_month = gmtime(&next_timeinfo)->tm_mon;

	    REQUIRE(((month == 11 && next_month == 0) || (next_month - month == 1)));
	}
    }
}
