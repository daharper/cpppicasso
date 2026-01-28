#ifndef CPPPICASSO_FILL_COMMAND_H
#define CPPPICASSO_FILL_COMMAND_H

#include <string>
#include "../command/Command.h"

class FillCommand : public Command {
public:
    [[nodiscard]] std::string getName() const override {
        return "B";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "bucket fill";
    }

    [[nodiscard]] std::string getExample() const override {
        return "B 4 4 @";
    }

    [[nodiscard]] std::string getFormat() const override {
        return "B x y [pen]";
    }

    Operation& execute(Canvas& canvas, const CommandObject& command) override {
        if (command.params.size() < 2 || command.params.size() > 3) {
            throw std::invalid_argument("Invalid number of parameters.");
        }

        char pen = canvas.getPen();

        const int width = std::stoi(command.params[0]);
        const int height = std::stoi(command.params[1]);

        if (command.params.size() > 2) {
            pen = command.params[2][0];
        }

        return canvas.fill(command.text, width, height, pen);
    }
};

#endif //CPPPICASSO_FILL_COMMAND_H