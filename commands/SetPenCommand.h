#ifndef CPPPICASSO_SET_PEN_COMMAND_H
#define CPPPICASSO_SET_PEN_COMMAND_H

#include <string>
#include "../command/Command.h"

class SetPenCommand : public Command {
public:
    [[nodiscard]] std::string getName() const override {
        return "@";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "set pen command";
    }

    [[nodiscard]] std::string getExample() const override {
        return "@ *";
    }

    [[nodiscard]] std::string getFormat() const override {
        return "@ [pen]";
    }

    Operation& execute(Canvas& canvas, const CommandObject& command) override {
        if (command.params.size() != 1) {
            throw std::invalid_argument("Invalid number of parameters.");
        }

        try {
            const char pen = command.params[0][0];
            canvas.setPen(pen);
            return NOP;
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("Invalid canvas dimensions.");
        }
    }
};

#endif //CPPPICASSO_SET_PEN_COMMAND_H