#include <doctest/doctest.h>
#include <config.hpp>
#include <sstream>
#include <string>

TEST_CASE("Config") {
    std::istringstream iss{R"(
        # single value
        key1    value1

        # another values
        key2    "some value 2"
        key3    42  # inline comment

        # multiple values
        key4    1
        key4    2
        key4    3
    )"};

    poost::Config config{iss};

    CHECK(config.get<std::string>("key1", "") == "value1");
    CHECK(config.get<std::string>("key2", "") == "some value 2");
    CHECK(config.get("key3", 0) == 42);
    CHECK(config.get<std::string>("key99", "default") == "default");
    CHECK(config.get("key4", 0) == 1);
    CHECK(config.get("key100", 42) == 42);
}
