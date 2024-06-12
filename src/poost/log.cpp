#include <cstdarg>
#include <log.hpp>

namespace poost {

namespace log {

LogSettings global{
    .stream = stderr,
    .log_level = LogLevel::Info,
    .use_colors = true,
};

} // namespace log

auto log_level_label(LogLevel level) -> const char *;
auto log_level_color(LogLevel level) -> const char *;

void log_print(const LogSettings &settings, LogLevel level, const char *fmt,
               ...) {

    const char *label = log_level_label(level);

    if (!settings.use_colors) {
        std::fprintf(settings.stream, "[%-5s] ", label);
    } else {
        const char *color = log_level_color(level);
        std::fprintf(settings.stream, "%s[%-5s]\x1b[0m ", color, label);
    }

    va_list ap;
    va_start(ap, fmt);
    std::vfprintf(settings.stream, fmt,
                  ap); // NOLINT(clang-analyzer-valist.Uninitialized)
    va_end(ap);

    std::fprintf(settings.stream, "\n");
}

auto log_level_label(LogLevel level) -> const char * {
    static const char *level_strings[] = {"",     "TRACE", "DEBUG", "INFO",
                                          "WARN", "ERROR", "FATAL", ""};
    return level_strings[static_cast<int>(level)];
}

auto log_level_color(LogLevel level) -> const char * {
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
