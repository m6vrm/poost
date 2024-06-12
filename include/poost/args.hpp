#pragma once

namespace poost {

namespace args {

// special Args::option() return values
// must be negative and fit in a signed char
inline constexpr char end = -1;
inline constexpr char not_an_option = -2;

template <typename T> auto convert(const char *val) -> T;

} // namespace args

class Args {
  public:
    Args(int argc, char *argv[]);

    auto option() -> char;
    auto value(char **val) -> bool;
    auto peek() const -> char *;

    template <typename T> auto value(T &val) -> bool;

  private:
    int argi_;
    int argc_;
    char **argv_;

    auto is_first_char() const -> bool;
    auto peek_char() const -> char;
    auto next_char() -> char;

    auto has_args() const -> bool;
    void skip_arg();
};

template <typename T> auto Args::value(T &val) -> bool {
    char *c_str;
    const bool result = value(&c_str);
    val = args::convert<T>(c_str);
    return result;
}

} // namespace poost
