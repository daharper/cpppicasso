//
// Created by david on 23/1/2026.
//

#ifndef CPPPICASSO_UTILS_H
#define CPPPICASSO_UTILS_H

#include <string>
#include <algorithm>

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
    /**
     * @brief Removes leading and trailing whitespace from a string.
     */
    static std::string trim(const std::string& s) {
        const std::string WHITESPACE = " \n\r\t\f\v";

        const size_t start = s.find_first_not_of(WHITESPACE);
        if (start == std::string::npos) return "";

        const size_t end = s.find_last_not_of(WHITESPACE);

        return s.substr(start, end - start + 1);
    }
};

#endif //CPPPICASSO_UTILS_H