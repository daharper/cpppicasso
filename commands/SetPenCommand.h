#ifndef CPPPICASSO_SET_PEN_COMMAND_H
#define CPPPICASSO_SET_PEN_COMMAND_H

#include <string>
#include "../command/Command.h"

class SetPenCommand : public Command {
public:
    [[nodiscard]] std::string getName() const override {
        return "P";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "set pen";
    }

    [[nodiscard]] std::string getExample() const override {
        return "P *";
    }

    [[nodiscard]] std::string getFormat() const override {
        return "P [pen]";
    }

    Operation& execute(Canvas& canvas, const CommandObject& command) override {
        if (command.params.size() != 1) {
            throw std::invalid_argument("Invalid number of parameters.");
        }

        const char pen = command.params[0][0];
        canvas.setPen(pen);
        return NOP;
    }
};

#endif //CPPPICASSO_SET_PEN_COMMAND_H