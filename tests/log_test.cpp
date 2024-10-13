#include "log.hpp"
#include <doctest/doctest.h>
#include <sstream>

TEST_CASE("Log") {
    std::ostringstream oss;
    poost::LogSettings log_settings{
        .stream = &oss,
        .log_level = poost::LogLevel::ALL,
        .use_colors = false,
    };

    POOST_TRACE_EX(log_settings, "Hello");
    POOST_INFO_EX(log_settings, "Hello");
    POOST_DEBUG_EX(log_settings, "Hello");
    POOST_WARN_EX(log_settings, "Hello");
    POOST_ERROR_EX(log_settings, "Hello");
    poost::log_print(log_settings, poost::LogLevel::FATAL, __FILE_NAME__, __LINE__, __FUNCTION__,
                     "Hello");

    CHECK(oss.str() ==
          "[TRACE] log_test.cpp(13) DOCTEST_ANON_FUNC_2: Hello\n"
          "[INFO ] log_test.cpp(14) DOCTEST_ANON_FUNC_2: Hello\n"
          "[DEBUG] log_test.cpp(15) DOCTEST_ANON_FUNC_2: Hello\n"
          "[WARN ] log_test.cpp(16) DOCTEST_ANON_FUNC_2: Hello\n"
          "[ERROR] log_test.cpp(17) DOCTEST_ANON_FUNC_2: Hello\n"
          "[FATAL] log_test.cpp(18) DOCTEST_ANON_FUNC_2: Hello\n");
}

TEST_CASE("log level colors") {
    std::ostringstream oss;
    poost::LogSettings log_settings{
        .stream = &oss,
        .log_level = poost::LogLevel::ALL,
        .use_colors = true,
    };

    POOST_TRACE_EX(log_settings, "Hello");
    POOST_INFO_EX(log_settings, "Hello");
    POOST_DEBUG_EX(log_settings, "Hello");
    POOST_WARN_EX(log_settings, "Hello");
    POOST_ERROR_EX(log_settings, "Hello");
    poost::log_print(log_settings, poost::LogLevel::FATAL, __FILE_NAME__, __LINE__, __FUNCTION__,
                     "Hello");

    CHECK(oss.str() ==
          "\x1b[37m[TRACE] log_test.cpp(38) DOCTEST_ANON_FUNC_4:\x1b[0m Hello\n"
          "\x1b[32m[INFO ] log_test.cpp(39) DOCTEST_ANON_FUNC_4:\x1b[0m Hello\n"
          "\x1b[34m[DEBUG] log_test.cpp(40) DOCTEST_ANON_FUNC_4:\x1b[0m Hello\n"
          "\x1b[33m[WARN ] log_test.cpp(41) DOCTEST_ANON_FUNC_4:\x1b[0m Hello\n"
          "\x1b[31m[ERROR] log_test.cpp(42) DOCTEST_ANON_FUNC_4:\x1b[0m Hello\n"
          "\x1b[35m[FATAL] log_test.cpp(43) DOCTEST_ANON_FUNC_4:\x1b[0m Hello\n");
}
