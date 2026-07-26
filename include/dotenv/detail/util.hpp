#pragma once

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace sorubu::util {
    inline std::string& ltrim(std::string& str, std::string_view trim_chars = " \t\n\r\f\v") {
        str.erase(0, str.find_first_not_of(trim_chars));
        return str;
    }

    inline std::string& rtrim(std::string& str, std::string_view trim_chars = " \t\n\r\f\v") {
        str.erase(str.find_last_not_of(trim_chars) + 1);
        return str;
    }

    inline std::string& trim(std::string& str, std::string_view trim_chars = " \t\n\r\f\v") {
        return ltrim(rtrim(str, trim_chars));
    }

    inline std::vector<std::string> split(std::string_view str, std::string_view separator = " ") {
        std::vector<std::string> result;

        std::size_t start = 0;
        std::size_t end;

        while ((end=str.find(separator, start)) != std::string_view::npos) {
            result.emplace_back(str.substr(start, end - start));

            start = end + separator.size();
        }

        if (start < str.size()) {
            result.emplace_back(str.substr(start));
        }

        return result;
    }
}