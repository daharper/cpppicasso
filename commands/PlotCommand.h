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
        return "plot a point";
    }

    [[nodiscard]] std::string getExample() const override {
        return "P 4 4 @";
    }

    [[nodiscard]] std::string getFormat() const override {
        return "P x y [pen]";
    }

    Operation& execute(Canvas& canvas, const CommandObject& command) override {
        if (command.params.size() < 2 || command.params.size() > 3) {
            throw std::invalid_argument("Invalid number of parameters.");
        }

        try {
            char pen = canvas.getPen();

            const int width = std::stoi(command.params[0]);
            const int height = std::stoi(command.params[1]);

            if (command.params.size() > 2) {
                pen = command.params[2][0];
            }

            return canvas.plot(command.text, width, height, pen);
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("Invalid canvas dimensions.");
        }
    }
};

#endif //CPPPICASSO_PLOT_COMMAND_H