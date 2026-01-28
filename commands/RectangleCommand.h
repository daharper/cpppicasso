#ifndef CPPPICASSO_RECTANGLE_COMMAND_H
#define CPPPICASSO_RECTANGLE_COMMAND_H

#include <string>
#include "../command/Command.h"

class RectangleCommand: public Command {
public:
    [[nodiscard]] std::string getName() const override {
        return "R";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "draws a rectangle";
    }

    [[nodiscard]] std::string getExample() const override {
        return "R 1 1 4 4 @";
    }

    [[nodiscard]] std::string getFormat() const override {
        return "R x1 y1 x2 y2 [pen]";
    }

    Operation& execute(Canvas& canvas, const CommandObject& command) override {
        if (command.params.size() < 4 || command.params.size() > 5) {
            throw std::invalid_argument("Invalid number of parameters.");
        }

        char pen = canvas.getPen();

        int x1 = std::stoi(command.params[0]);
        int y1 = std::stoi(command.params[1]);
        int x2 = std::stoi(command.params[2]);
        int y2 = std::stoi(command.params[3]);

        if (command.params.size() == 5) {
            pen = command.params[4][0];
        }

        if (x2 < x1 || y2 < y1) {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }

        const int w = x2 - x1 + 1;
        const int h = y2 - y1 + 1;

        if (w == 1 && h == 1) {
            return canvas.plot(command.text, x1, y1, pen);
        }

        if (w == 1 || h == 1) {
            return canvas.line(command.text, x1, y1, x2, y2, pen);
        }

        if (w < 1 || h < 1) {
            throw std::invalid_argument("Invalid rectangle dimensions.");
        }

        return canvas.rectangle(command.text, x1, y1, w, h, pen);
    }
};

#endif //CPPPICASSO_RECTANGLE_COMMAND_H