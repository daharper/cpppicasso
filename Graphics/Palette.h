//
// Created by david on 21/1/2026.
//

#ifndef CPPPICASSO_PALETTE_H
#define CPPPICASSO_PALETTE_H

#include <string>
#include <map>
#include <optional>
#include "../Utils.h"

class Palette {
public:
    Palette() = delete;

    static bool isSupported(const std::string& color) {
        return fgColors.contains(color);
    }

    static void validate(const std::string& color) {
        if (!fgColors.contains(color)) {
            throw std::invalid_argument("Unknown color: " + color);
        }
    }

    static std::optional<int> getForeground(const std::string& name) {
        const auto it = fgColors.find(name);
        return it != fgColors.end() ? std::optional(it->second) : std::nullopt;
    }

    static std::optional<int> getBackground(const std::string& name) {
        const auto it = bgColors.find(name);
        return it != bgColors.end() ? std::optional(it->second) : std::nullopt;
    }

private:
    inline static const std::map<std::string, int, CaseInsensitiveLess> fgColors = {
        {"black", 30}, {"red", 31}, {"green", 32}, {"yellow", 33},
        {"blue", 34}, {"magenta", 35}, {"cyan", 36}, {"white", 37}
    };

    inline static const std::map<std::string, int, CaseInsensitiveLess> bgColors = {
        {"black", 40}, {"red", 41}, {"green", 42}, {"yellow", 43},
        {"blue", 44}, {"magenta", 45}, {"cyan", 46}, {"white", 47}
    };
};

#endif //CPPPICASSO_PALETTE_H