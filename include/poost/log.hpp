#ifndef POOST_LOG_HPP
#define POOST_LOG_HPP

#include <cstdio>
#include <cstdlib>

#ifndef __FILE_NAME__
#define __FILE_NAME__ __FILE__
#endif // ifndef __FILE_NAME__

#define POOST_LOG(settings, level, ...)                                        \
    do {                                                                       \
        if (static_cast<int>(level) >= static_cast<int>(settings.log_level)) { \
            poost::log_print(settings, level, __FILE_NAME__, __LINE__,         \
                             __VA_ARGS__);                                     \
                                                                               \
            if (level == poost::LogLevel::Fatal) {                             \
                std::exit(EXIT_FAILURE);                                       \
            }                                                                  \
        }                                                                      \
    } while (false)

#define POOST_TRACE_EX(settings, ...)                                          \
    POOST_LOG(settings, poost::LogLevel::Trace, __VA_ARGS__)
#define POOST_DEBUG_EX(settings, ...)                                          \
    POOST_LOG(settings, poost::LogLevel::Debug, __VA_ARGS__)
#define POOST_INFO_EX(settings, ...)                                           \
    POOST_LOG(settings, poost::LogLevel::Info, __VA_ARGS__)
#define POOST_WARN_EX(settings, ...)                                           \
    POOST_LOG(settings, poost::LogLevel::Warn, __VA_ARGS__)
#define POOST_ERROR_EX(settings, ...)                                          \
    POOST_LOG(settings, poost::LogLevel::Error, __VA_ARGS__)
#define POOST_FATAL_EX(settings, ...)                                          \
    POOST_LOG(settings, poost::LogLevel::Fatal, __VA_ARGS__)

#define POOST_TRACE(...) POOST_TRACE_EX(poost::log::main, __VA_ARGS__)
#define POOST_DEBUG(...) POOST_DEBUG_EX(poost::log::main, __VA_ARGS__)
#define POOST_INFO(...) POOST_INFO_EX(poost::log::main, __VA_ARGS__)
#define POOST_WARN(...) POOST_WARN_EX(poost::log::main, __VA_ARGS__)
#define POOST_ERROR(...) POOST_ERROR_EX(poost::log::main, __VA_ARGS__)
#define POOST_FATAL(...) POOST_FATAL_EX(poost::log::main, __VA_ARGS__)

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
    std::FILE *stream;
    LogLevel log_level;
    bool print_file_line;
    bool use_color;
};

namespace log {

extern LogSettings main;

} // namespace log

void log_print(const LogSettings &settings, LogLevel level, const char *file,
               int line, const char *fmt, ...);

} // namespace poost

#endif // ifndef POOST_LOG_HPP
