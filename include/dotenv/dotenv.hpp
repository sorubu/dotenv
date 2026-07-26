#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <optional>

namespace sorubu::dotenv {
    class Env {
    public:
        explicit Env(std::string_view filepath = ".env");
        std::optional<std::string> get(std::string_view key) const;
    private:
        std::unordered_map<std::string, std::string> env_map;
    };
}