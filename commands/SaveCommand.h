#ifndef CPPPICASSO_SAVE_COMMAND_H
#define CPPPICASSO_SAVE_COMMAND_H

#include <fstream>
#include <string>
#include "../command/Command.h"

class SaveCommand : public Command {
public:
    [[nodiscard]] std::string getName() const override {
        return "S";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "save to file";
    }

    [[nodiscard]] std::string getExample() const override {
        return "S hello.txt";
    }

    [[nodiscard]] std::string getFormat() const override {
        return "S file";
    }

    Operation& execute(Canvas& canvas, const CommandObject& command) override {
        if (command.params.size() != 1) {
            throw std::invalid_argument("Invalid number of parameters.");
        }

        auto& path = command.params[0];

        std::ofstream out(path);
        if (!out) throw std::invalid_argument("Cannot open file.");

        for (auto& op: canvas) {
            out << op.text << "\n";
        }

        return NOP;
    }
};

#endif //CPPPICASSO_SAVE_COMMAND_H