#include <config.hpp>
#include <doctest/doctest.h>
#include <sstream>

TEST_CASE("config parsing") {
    std::istringstream iss{R"(
    # comment
    key1 value1

    # comment 2
    key2 "some value 2"
    key3 42
    )"};

    poost::Config config;
    config.load(iss);

    CHECK(config.value<std::string>("key1", "") == "value1");
    CHECK(config.value<std::string>("key2", "") == "some value 2");
    CHECK(config.value("key3", 42) == 42);
    CHECK(config.value<std::string>("key99", "default") == "default");
    CHECK(config.value("key100", 42) == 42);
}
