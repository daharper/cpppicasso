#ifndef CPPPICASSO_LINE_COMMAND_H
#define CPPPICASSO_LINE_COMMAND_H

#include <string>
#include "../command/Command.h"

class LineCommand : public Command {
public:
    [[nodiscard]] std::string getName() const override {
        return "L";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "draws a line";
    }

    [[nodiscard]] std::string getExample() const override {
        return "L 1 1 4 1 @";
    }

    [[nodiscard]] std::string getFormat() const override {
        return "L x1 y1 x2 y2 [pen]";
    }

    Operation& execute(Canvas& canvas, const CommandObject& command) override {
        if (command.params.size() < 4 || command.params.size() > 5) {
            throw std::invalid_argument("Invalid number of parameters.");
        }

        try {
            char pen = canvas.getPen();

            const int x1 = std::stoi(command.params[0]);
            const int y1 = std::stoi(command.params[1]);
            const int x2 = std::stoi(command.params[0]);
            const int y2 = std::stoi(command.params[1]);

            if (command.params.size() == 5) {
                pen = command.params[4][0];
            }

            if (x1 == x2 && y1 == y2) {
                return canvas.plot(command.text, x1, y1, pen);
            }

            return canvas.line(command.text, x1, y1, x2, y2, pen);
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("Invalid canvas dimensions.");
        }
    }
};

#endif //CPPPICASSO_LINE_COMMAND_H