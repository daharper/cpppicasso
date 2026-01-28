#ifndef CPPPICASSO_WRITE_TEXT_H
#define CPPPICASSO_WRITE_TEXT_H

#include <string>
#include "../command/Command.h"

class WriteCommand : public Command {
public:
    [[nodiscard]] std::string getName() const override {
        return "W";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "write text";
    }

    [[nodiscard]] std::string getExample() const override {
        return "W 1 1 Hello World!";
    }

    [[nodiscard]] std::string getFormat() const override {
        return "W x y text";
    }

    Operation& execute(Canvas& canvas, const CommandObject& command) override {
        if (command.params.size() < 3) {
            throw std::invalid_argument("Invalid number of parameters.");
        }

        std::string text;

        const int x1 = std::stoi(command.params[0]);
        const int y1 = std::stoi(command.params[1]);

        for (int i = 2; i < command.params.size(); ++i) {
            text += command.params[i] + " ";
        }

        text.pop_back();

        return canvas.write(command.text, x1, y1, text);
    }
};

#endif //CPPPICASSO_WRITE_TEXT_H