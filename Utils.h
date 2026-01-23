//
// Created by david on 23/1/2026.
//

#ifndef CPPPICASSO_UTILS_H
#define CPPPICASSO_UTILS_H

#include <string>

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

#endif //CPPPICASSO_UTILS_H