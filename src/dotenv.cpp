#include <fstream>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <cstdlib>

#include <dotenv/dotenv.hpp>
#include <dotenv/detail/util.hpp>

namespace sorubu::dotenv {
    Env::Env(std::string_view filepath) {
        std::ifstream file{std::string(filepath)};
        if (!file.is_open()) {
            throw std::runtime_error(std::string("Failed to open ").append(filepath).append(" file"));
        }

        std::string line;
        while (std::getline(file, line)) {
            sorubu::util::trim(line);

            if (line.empty() || line.starts_with('#')) {
                continue;
            }

            auto separator_pos = line.find('=');

            if (separator_pos == std::string::npos) {
                continue;
            }

            auto key = line.substr(0, separator_pos);
            auto value = line.substr(separator_pos + 1);
            
            sorubu::util::trim(key);
            sorubu::util::trim(value);

            if (value.size() >= 2 && value.front() == '"' && value.back() == '"') {
                value = value.substr(1, value.size() - 2);
            }

            env_map.insert_or_assign(key, value);
        }
    }

    std::optional<std::string> Env::get(std::string_view key) const {
        auto it = env_map.find(std::string(key));

        if (it != env_map.end()) {
            return it->second;
        }
        else if (const char* env = std::getenv(std::string(key).c_str())) {
            return env;
        }

        return std::nullopt;
    }
}