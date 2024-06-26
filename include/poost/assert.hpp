#pragma once

#ifndef NDEBUG
#include <cstdlib>
#include <poost/log.hpp>
#define POOST_ASSERT(cond, ...)                                                \
    do {                                                                       \
        if (!(cond)) {                                                         \
            poost::log_print(poost::log::global, poost::LogLevel::Fatal,       \
                             "%s:%d: assertion failure ( %s )", __FILE__,      \
                             __LINE__, #cond);                                 \
            poost::log_print(poost::log::global, poost::LogLevel::Fatal,       \
                             __VA_ARGS__);                                     \
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
