//
// Created by david on 23/1/2026.
//

#ifndef CPPPICASSO_UTILS_H
#define CPPPICASSO_UTILS_H

#include <string>
#include <algorithm>
#include <string_view>

/**
 * @brief Case insensitive comparison.
 */
struct CaseInsensitiveLess {
    bool operator()(const std::string& a, const std::string& b) const {
        return std::lexicographical_compare(
            a.begin(), a.end(),
            b.begin(), b.end(),
            [](const unsigned char c1, const unsigned char c2) {
                return std::tolower(c1) < std::tolower(c2);
            }
        );
    }
};

/**
 * @brief String utility functions.
 */
class String {
public:
    static std::string whiteSpace() {
        return " \n\r\t\f\v";
    }

    /**
     * @brief Removes leading and trailing whitespace from a string.
     */
    static std::string trim(const std::string& s) {
        static const std::string ws = whiteSpace();

        const size_t start = s.find_first_not_of(ws);
        if (start == std::string::npos) return "";

        const size_t end = s.find_last_not_of(ws);

        return s.substr(start, end - start + 1);
    }

    /**
     * @brief determines whether the string is blank - empty or only whitespace characters.
     * @return Returns true if the string is blank.
     */
    static bool isBlank(const std::string& s) {
        static const std::string ws = whiteSpace();

        return s.empty() || s.find_first_not_of(ws) == std::string::npos;
    }

    /**
     * @brief Determines if two strings are equal, ignoring case and whitespace.
     * @return Returns true if the strings are equal, ignoring case and whitespace.
     */
    static bool isSame(const std::string& a, const std::string& b) {
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); ++i) {
            const auto ca = static_cast<unsigned char>(a[i]);
            const auto cb = static_cast<unsigned char>(b[i]);

            if (std::tolower(ca) != std::tolower(cb)) return false;
        }

        return true;
    }
};

#endif //CPPPICASSO_UTILS_H