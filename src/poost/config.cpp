#include <config.hpp>

namespace poost {

void config::load(std::istream &is) {
    std::string line;
    while (std::getline(is, line)) {
        std::size_t found = line.find("#");
        if (found != std::string::npos) {
            line.erase(found);
        }

        std::istringstream iss{line};
        std::string key;
        std::string value;

        if (iss >> key >> value) {
            config_.emplace(key, value);
        }
    }
}

} // namespace poost
