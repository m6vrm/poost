#pragma once

#include <cstdlib>
#include <format>
#include <ostream>

#define POOST_TRACE(...) POOST_TRACE_EX(poost::log::global, __VA_ARGS__)
#define POOST_DEBUG(...) POOST_DEBUG_EX(poost::log::global, __VA_ARGS__)
#define POOST_INFO(...) POOST_INFO_EX(poost::log::global, __VA_ARGS__)
#define POOST_WARN(...) POOST_WARN_EX(poost::log::global, __VA_ARGS__)
#define POOST_ERROR(...) POOST_ERROR_EX(poost::log::global, __VA_ARGS__)
#define POOST_FATAL(...) POOST_FATAL_EX(poost::log::global, __VA_ARGS__)

#define POOST_LOG(...) POOST_LOG_EX(poost::log::global, __VA_ARGS__)

#define POOST_TRACE_EX(settings, ...)                                          \
    POOST_LOG_EX(settings, poost::LogLevel::Trace, __VA_ARGS__)
#define POOST_DEBUG_EX(settings, ...)                                          \
    POOST_LOG_EX(settings, poost::LogLevel::Debug, __VA_ARGS__)
#define POOST_INFO_EX(settings, ...)                                           \
    POOST_LOG_EX(settings, poost::LogLevel::Info, __VA_ARGS__)
#define POOST_WARN_EX(settings, ...)                                           \
    POOST_LOG_EX(settings, poost::LogLevel::Warn, __VA_ARGS__)
#define POOST_ERROR_EX(settings, ...)                                          \
    POOST_LOG_EX(settings, poost::LogLevel::Error, __VA_ARGS__)
#define POOST_FATAL_EX(settings, ...)                                          \
    POOST_LOG_EX(settings, poost::LogLevel::Fatal, __VA_ARGS__)

#define POOST_LOG_EX(settings, level, ...)                                     \
    do {                                                                       \
        if ((level) >= (settings).log_level) {                                 \
            poost::log_print((settings), (level), __VA_ARGS__);                \
                                                                               \
            if ((level) == poost::LogLevel::Fatal) {                           \
                std::abort();                                                  \
            }                                                                  \
        }                                                                      \
    } while (false)

namespace poost {

enum class LogLevel {
    All,
    Trace,
    Debug,
    Info,
    Warn,
    Error,
    Fatal,
    None,
};

struct LogSettings {
    std::ostream *stream;
    LogLevel log_level;
    bool use_colors;
};

namespace log {

extern LogSettings global;

} // namespace log

const char *log_level_label(LogLevel level);
const char *log_level_color(LogLevel level);

template <typename... Args>
void log_print(const LogSettings &settings, LogLevel level,
               std::format_string<Args...> format, Args &&...args) {

    const char *label = log_level_label(level);

    if (!settings.use_colors) {
        *settings.stream << std::format("[{:<5}] ", label);
    } else {
        const char *color = log_level_color(level);
        *settings.stream << std::format("{}[{:<5}]\x1b[0m ", color, label);
    }

    *settings.stream << std::format(format, std::forward<Args>(args)...)
                     << "\n";
}

} // namespace poost
