#ifndef CPPPICASSO_UNDO_COMMAND_H
#define CPPPICASSO_UNDO_COMMAND_H

#include <string>
#include "../command/Command.h"

class UndoCommand : public Command {
public:
    [[nodiscard]] std::string getName() const override {
        return "U";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "undo command";
    }

    [[nodiscard]] std::string getExample() const override {
        return "U";
    }

    [[nodiscard]] std::string getFormat() const override {
        return "U";
    }

    Operation& execute(Canvas& canvas, const CommandObject& command) override {
        if (!command.params.empty()) {
            throw std::invalid_argument("Invalid number of parameters.");
        }

        return canvas.undo();
    }
};

#endif //CPPPICASSO_UNDO_COMMAND_H