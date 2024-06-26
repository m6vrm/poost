#include <iostream>
#include <log.hpp>

namespace poost {

namespace log {

LogSettings global{
    .stream = &std::cerr,
    .log_level = LogLevel::Info,
    .use_colors = true,
};

} // namespace log

const char *log_level_label(LogLevel level) {
    static const char *level_strings[] = {
        "",      //
        "TRACE", //
        "DEBUG", //
        "INFO",  //
        "WARN",  //
        "ERROR", //
        "FATAL", //
        ""       //
    };

    return level_strings[static_cast<int>(level)];
}

const char *log_level_color(LogLevel level) {
    static const char *level_colors[] = {
        "",         //
        "\x1b[37m", // TRACE = white
        "\x1b[34m", // DEBUG = blue
        "\x1b[32m", // INFO = green
        "\x1b[33m", // WARN = yellow
        "\x1b[31m", // ERROR = red
        "\x1b[35m", // FATAL = purple
        ""          //
    };

    return level_colors[static_cast<int>(level)];
}

} // namespace poost
