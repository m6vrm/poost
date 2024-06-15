#include <doctest/doctest.h>
#include <log.hpp>
#include <sstream>

TEST_CASE("log level labels") {
    std::ostringstream oss;
    const poost::LogSettings log_settings{
        .stream = &oss,
        .log_level = poost::LogLevel::All,
        .use_colors = false,
    };

    POOST_TRACE_EX(log_settings, "Hello");
    POOST_INFO_EX(log_settings, "Hello");
    POOST_DEBUG_EX(log_settings, "Hello");
    POOST_WARN_EX(log_settings, "Hello");
    POOST_ERROR_EX(log_settings, "Hello");
    poost::log_print(log_settings, poost::LogLevel::Fatal, "Hello");

    CHECK(oss.str() == "[TRACE] Hello\n"
                       "[INFO ] Hello\n"
                       "[DEBUG] Hello\n"
                       "[WARN ] Hello\n"
                       "[ERROR] Hello\n"
                       "[FATAL] Hello\n");
}

TEST_CASE("log level colors") {
    std::ostringstream oss;
    const poost::LogSettings log_settings{
        .stream = &oss,
        .log_level = poost::LogLevel::All,
        .use_colors = true,
    };

    POOST_TRACE_EX(log_settings, "Hello");
    POOST_INFO_EX(log_settings, "Hello");
    POOST_DEBUG_EX(log_settings, "Hello");
    POOST_WARN_EX(log_settings, "Hello");
    POOST_ERROR_EX(log_settings, "Hello");
    poost::log_print(log_settings, poost::LogLevel::Fatal, "Hello");

    CHECK(oss.str() == "\x1b[37m[TRACE]\x1b[0m Hello\n"
                       "\x1b[32m[INFO ]\x1b[0m Hello\n"
                       "\x1b[34m[DEBUG]\x1b[0m Hello\n"
                       "\x1b[33m[WARN ]\x1b[0m Hello\n"
                       "\x1b[31m[ERROR]\x1b[0m Hello\n"
                       "\x1b[35m[FATAL]\x1b[0m Hello\n");
}
