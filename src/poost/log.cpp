#include "log.hpp"

#include <cstdarg>

namespace poost {

auto log_level_label(LogLevel level) -> const char *;
auto log_level_color(LogLevel level) -> const char *;

/// Public

namespace log {

LogSettings main{
    .stream = stderr,
    .log_level = LogLevel::Info,
    .print_file_line = true,
    .use_color = true,
};

} // namespace log

// todo: (c++20) use std::format
void log_print(const LogSettings &settings, LogLevel level, const char *file,
               int line, const char *fmt, ...) {

    const char *label = log_level_label(level);

    if (settings.use_color) {
        const char *color = log_level_color(level);
        if (settings.print_file_line) {
            std::fprintf(settings.stream,
                         "%s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ", color, label,
                         file, line);
        } else {
            std::fprintf(settings.stream, "%s%-5s\x1b[0m ", color, label);
        }
    } else {
        if (settings.print_file_line) {
            std::fprintf(settings.stream, "%-5s %s:%d: ", label, file, line);
        } else {
            std::fprintf(settings.stream, "%-5s ", label);
        }
    }

    va_list ap;
    va_start(ap, fmt);
    // todo: false positive (see
    // https://github.com/llvm/llvm-project/issues/40656)
    std::vfprintf(settings.stream, fmt,
                  ap); // NOLINT(clang-analyzer-valist.Uninitialized)
    va_end(ap);

    std::fprintf(settings.stream, "\n");
    std::fflush(settings.stream);
}

/// Private

auto log_level_label(LogLevel level) -> const char * {
    static const char *level_strings[] = {
        "",      "TRACE", "DEBUG", "INFO", "WARN",
        "ERROR", "FATAL", ""}; // first and last are for All and None metalevels
    return level_strings[static_cast<int>(level)];
}

auto log_level_color(LogLevel level) -> const char * {
    static const char *level_colors[] = {
        "",         "\x1b[34m", "\x1b[36m", "\x1b[32m", "\x1b[33m",
        "\x1b[31m", "\x1b[35m", ""}; // first and last are for All and None
                                     // metalevels
    return level_colors[static_cast<int>(level)];
}

} // namespace poost
