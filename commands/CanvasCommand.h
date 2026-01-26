#ifndef CPPPICASSO_CREATE_CANVAS_COMMAND_H
#define CPPPICASSO_CREATE_CANVAS_COMMAND_H

#include "../command/Command.h"

class CanvasCommand : public Command{
public:
    [[nodiscard]] std::string getName() const override {
        return "C";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "create canvas";
    }

    [[nodiscard]] std::string getExample() const override {
        return "C 10 4 white black";
    }

    [[nodiscard]] std::string getFormat() const override {
        return "C width height [color backcolor]";
    }

    Operation& execute(Canvas& canvas, const CommandObject& command) override  {
        if (command.params.size() < 2 || command.params.size() > 4) {
            throw std::invalid_argument("Invalid number of parameters.");
        }

        try {
            std::string color = Canvas::DEFAULT_COLOR;
            std::string bgColor = Canvas::DEFAULT_BG_COLOR;

            const int width = std::stoi(command.params[0]);
            const int height = std::stoi(command.params[1]);

            if (command.params.size() > 2) {
                color = command.params[2];

                if (command.params.size() > 3) {
                    bgColor = command.params[3];
                }
            }

            return canvas.create(command.text, width, height, color, bgColor);
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("Invalid canvas dimensions.");
        }
    }
};

#endif //CPPPICASSO_CREATE_CANVAS_COMMAND_H
