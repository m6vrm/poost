#include <algorithm>
#include <args.hpp>
#include <string>

namespace poost {

namespace args {

template <> auto convert(const char *val) -> std::string { return val; }

} // namespace args

Args::Args(int argc, char *argv[])
    : argi_{0}, argc_{argc - 1}, argv_{&argv[1]} {}

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
    *val = *argv_;
    skip_arg();
    return true;
}

auto Args::peek() const -> char * { return *argv_; }

auto Args::is_first_char() const -> bool { return argi_ == 0; }
auto Args::peek_char() const -> char { return (*argv_)[argi_]; }
auto Args::next_char() -> char { return (*argv_)[argi_++]; }

auto Args::has_args() const -> bool { return argc_ > 0; }

void Args::skip_arg() {
    argi_ = 0;
    --argc_;
    ++argv_;
}

} // namespace poost
