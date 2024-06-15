#pragma once

#include <istream>
#include <sstream>
#include <string>
#include <unordered_map>

namespace poost {

class config {
  public:
    void load(std::istream &is);

    template <typename T>
    auto value(const std::string &key, const T &default_) -> T {
        const auto found = config_.find(key);
        if (found == config_.end()) {
            return default_;
        }

        if constexpr (std::is_same_v<T, std::string>) {
            return found->second;
        }

        T result;
        std::ostringstream oss{found->second};
        oss >> result;
        return result;
    }

  private:
    std::unordered_map<std::string, std::string> config_;
};

} // namespace poost
