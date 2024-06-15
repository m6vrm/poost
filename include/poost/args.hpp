#pragma once

#include <sstream>

namespace poost {

namespace args {

// special Args::option() return values
// must be negative and fit in a signed char
inline constexpr char end = -1;
inline constexpr char not_an_option = -2;

} // namespace args

class Args {
  public:
    Args(int argc, const char **argv)
        : argi_{0}, argc_{argc - 1}, argv_{&argv[1]} {}

    auto option() -> char;
    auto value(const char **val) -> bool;
    auto peek() const -> const char *;

    template <typename T> auto value(T &val) -> bool;

  private:
    int argi_;
    int argc_;
    const char **argv_;

    auto is_first_char() const -> bool;
    auto peek_char() const -> char;
    auto next_char() -> char;

    auto has_args() const -> bool;
    void skip_arg();
};

template <typename T> auto Args::value(T &val) -> bool {
    const char *c_str;

    const bool result = value(&c_str);
    if (result) {
        std::stringstream ss{c_str};
        ss >> val;
    }

    return result;
}

} // namespace poost
