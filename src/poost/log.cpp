#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <log.hpp>

namespace poost {

namespace log {

LogSettings global{
    .stream = std::cerr,
    .log_level = LogLevel::Info,
    .use_colors = true,
};

} // namespace log

static auto log_level_label(LogLevel level) -> const char *;
static auto log_level_color(LogLevel level) -> const char *;

void log_print(const LogSettings &settings, LogLevel level, const char *fmt,
               ...) {

    char buf[1024];
    char *cur = buf;
    const char *end = buf + sizeof(buf);

    const char *label = log_level_label(level);

    if (!settings.use_colors) {
        cur += std::snprintf(cur, end - cur, "[%-5s] ", label);
    } else {
        const char *color = log_level_color(level);
        cur += std::snprintf(buf, end - cur, "%s[%-5s]\x1b[0m ", color, label);
    }

    if (cur < end) {
        va_list ap;
        va_start(ap, fmt);
        cur +=
            std::vsnprintf(cur, end - cur, fmt,
                           ap); // NOLINT(clang-analyzer-valist.Uninitialized)
        va_end(ap);
    }

    if (cur < end) {
        std::snprintf(cur, end - cur, "%s", "\n");
    }

    buf[sizeof(buf) - 1] = '\n';
    settings.stream << buf;
}

static auto log_level_label(LogLevel level) -> const char * {
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

static auto log_level_color(LogLevel level) -> const char * {
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
