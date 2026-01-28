#ifndef CPPPICASSO_SET_COLORS_H
#define CPPPICASSO_SET_COLORS_H

#include <string>
#include "../command/Command.h"

class SetColorsCommand : public Command {
public:
    [[nodiscard]] std::string getName() const override {
        return "A";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "apply colors";
    }

    [[nodiscard]] std::string getExample() const override {
        return "A white black";
    }

    [[nodiscard]] std::string getFormat() const override {
        return "A color [bgcolor]";
    }

    Operation& execute(Canvas& canvas, const CommandObject& command) override {
        if (command.params.empty() || command.params.size() > 2) {
            throw std::invalid_argument("Invalid number of parameters.");
        }

        const std::string color = command.params[0];
        const std::string bgColor = command.params.size() == 2 ? command.params[1] : Canvas::DEFAULT_BG_COLOR;

        canvas.setColors(color, bgColor);

        return NOP;
    }
};

#endif //CPPPICASSO_SET_COLORS_H