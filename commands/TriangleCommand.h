#ifndef CPPPICASSO_TRIANGLE_COMMAND_H
#define CPPPICASSO_TRIANGLE_COMMAND_H

#include <string>
#include "../command/Command.h"

class TriangleCommand: public Command {
public:
    [[nodiscard]] std::string getName() const override {
        return "T";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "draws a triangle";
    }

    [[nodiscard]] std::string getExample() const override {
        return "T 4 1 1 4 8 4 @";
    }

    [[nodiscard]] std::string getFormat() const override {
        return "T x1 y1 x2 y2 x3 y3 [pen]";
    }

    Operation& execute(Canvas& canvas, const CommandObject& command) override {
        if (command.params.size() < 6 || command.params.size() > 7) {
            throw std::invalid_argument("Invalid number of parameters.");
        }

        char pen = canvas.getPen();

        const int x1 = std::stoi(command.params[0]);
        const int y1 = std::stoi(command.params[1]);
        const int x2 = std::stoi(command.params[2]);
        const int y2 = std::stoi(command.params[3]);
        const int x3 = std::stoi(command.params[4]);
        const int y3 = std::stoi(command.params[5]);

        if (command.params.size() == 7) {
            pen = command.params[6][0];
        }

        return canvas.triangle(command.text, x1, y1, x2, y2, x3, y3, pen);
    }
};

#endif //CPPPICASSO_TRIANGLE_COMMAND_H