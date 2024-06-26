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

    char option();
    bool value(const char **val);
    const char *peek() const;

    template <typename T> bool value(T &val) {
        const char *c_str;

        const bool result = value(&c_str);
        if (result) {
            std::stringstream ss{c_str};
            ss >> val;
        }

        return result;
    }

  private:
    int argi_;
    int argc_;
    const char **argv_;

    bool is_first_char() const;
    char peek_char() const;
    char next_char();

    bool has_args() const;
    void skip_arg();
};

} // namespace poost
