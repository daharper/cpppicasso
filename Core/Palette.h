//
// Created by david on 21/1/2026.
//

#ifndef CPPPICASSO_PALETTE_H
#define CPPPICASSO_PALETTE_H

#include <string>
#include <map>
#include <optional>
#include <stdexcept>

#include "../Utils.h"

class Palette {
public:
    Palette() = delete;

    static bool isSupported(const std::string& color) {
        return fgColors.contains(color);
    }

    static void validateForeground(const std::string& color) {
        if (!fgColors.contains(color)) {
            throw std::invalid_argument("Unknown color: " + color);
        }
    }

    static void validateBackground(const std::string& color) {
        if (!bgColors.contains(color)) {
            throw std::invalid_argument("Unknown color: " + color);
        }
    }

    static int getForeground(const std::string& name) {
        validateForeground(name);
        return fgColors.at(name);
    }

    static int getBackground(const std::string& name) {
        validateBackground(name);
        return bgColors.at(name);
    }

    static std::string format(const int fgColor, const int bgColor, const std::string& text) {
        return "\033[" + std::to_string(bgColor) + "m" + "\033[" + std::to_string(fgColor) + "m" + text + "\033[0m";
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