#ifndef CPPPICASSO_PLOT_COMMAND_H
#define CPPPICASSO_PLOT_COMMAND_H

#include <string>
#include "../command/Command.h"

class PlotCommand : public Command {
public:
    [[nodiscard]] std::string getName() const override {
        return "P";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "plot on the canvas - P x y [pen]                      - P 4 4 @";
    }

    Operation& execute(Canvas& canvas, const CommandObject& command) override {
        if (command.params.size() < 2 || command.params.size() > 3) {
            throw std::invalid_argument("Invalid number of parameters.");
        }

        int width, height = 0;
        char pen = canvas.getPen();

        try {
            width = std::stoi(command.params[0]);
            height = std::stoi(command.params[1]);

            if (command.params.size() > 2) {
                pen = command.params[2][0];
            }
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("Invalid canvas dimensions.");
        }

        return canvas.plot(command.text, width, height, pen);
    }
};


#endif //CPPPICASSO_PLOT_COMMAND_H