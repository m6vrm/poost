#include "args.hpp"

#include <algorithm>

// todo: write tests

namespace poost {

/// Converters

namespace args {

template <> auto convert(const char *val) -> std::string { return val; }

} // namespace args

/// Public

Args::Args(int argc, char *argv[]) : m_argi{0}, m_argc{argc - 1}, m_argv{&argv[1]} {}

auto Args::option() -> char {
    while (has_args()) {
        const bool is_first = is_first_char();
        const char c = next_char();

        if (is_first) {
            if (c == '-') {
                // option group start
                // move to the next char
                continue;
            } else {
                // not an option group
                // return with error
                return args::not_an_option;
            }
        }

        if (c == '\0') {
            // option group end
            // move to the next arg
            skip_arg();
            continue;
        }

        // return parsed option
        return c;
    }

    // arg list end
    return args::end;
}

auto Args::value(char **val) -> bool {
    if (!is_first_char()) {
        // inside option group
        if (peek_char() == '\0') {
            // option group end
            // move to the next arg
            skip_arg();
        } else {
            // not option group end
            // forbid value parsing
            return false;
        }
    }

    if (!has_args() || peek_char() == '-') {
        // arg list end or option group start
        // forbid value parsing
        return false;
    }

    // parse value and move to the next arg
    *val = *m_argv;
    skip_arg();
    return true;
}

auto Args::peek() const -> char * { return *m_argv; }

/// Private

auto Args::is_first_char() const -> bool { return m_argi == 0; }
auto Args::peek_char() const -> char { return (*m_argv)[m_argi]; }
auto Args::next_char() -> char { return (*m_argv)[m_argi++]; }

auto Args::has_args() const -> bool { return m_argc > 0; }

void Args::skip_arg() {
    m_argi = 0;
    --m_argc;
    ++m_argv;
}

} // namespace poost
