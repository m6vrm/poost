#ifndef POOST_ASSERT_HPP
#define POOST_ASSERT_HPP

#ifndef NDEBUG
#include "log.hpp"
#include <cstdlib>
#define POOST_ASSERT(cond, ...)                                                \
    do {                                                                       \
        if (!(cond)) {                                                         \
            poost::log_print(poost::log::main, poost::LogLevel::Fatal,         \
                             __FILE_NAME__, __LINE__,                          \
                             "assertion failure ( %s )", #cond);               \
            poost::log_print(poost::log::main, poost::LogLevel::Fatal,         \
                             __FILE_NAME__, __LINE__, __VA_ARGS__);            \
            std::abort();                                                      \
        }                                                                      \
    } while (false)
#else // ifndef NDEBUG
#define POOST_ASSERT(cond, ...)
#endif // ifndef NDEBUG

#define POOST_ASSERT_FAIL(...)                                                 \
    do {                                                                       \
        POOST_ASSERT(false, __VA_ARGS__);                                      \
        poost::unreachable();                                                  \
    } while (false)

namespace poost {

// todo: (c++23) use std::unreachable
[[noreturn]] inline void unreachable() {
    // Uses compiler specific extensions if possible.
    // Even if no extension is used, undefined behavior is still raised by
    // an empty function body and the noreturn attribute.
#ifdef __GNUC__ // GCC, Clang, ICC
    __builtin_unreachable();
#elif defined(_MSC_VER) // MSVC
    __assume(false);
#endif
}

} // namespace poost

#endif // ifndef POOST_ASSERT_HPP
