#ifndef CPPPICASSO_SAVE_COMMAND_H
#define CPPPICASSO_SAVE_COMMAND_H

#include <fstream>
#include <string>
#include "../command/Command.h"

class SaveCommand : public Command {
public:
    [[nodiscard]] std::string getName() const override {
        return "W";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "write to file";
    }

    [[nodiscard]] std::string getExample() const override {
        return "W hello.txt";
    }

    [[nodiscard]] std::string getFormat() const override {
        return "W file";
    }

    Operation& execute(Canvas& canvas, const CommandObject& command) override {
        if (command.params.size() != 1) {
            throw std::invalid_argument("Invalid number of parameters.");
        }

        auto& path = command.params[0];

        try {
            std::ofstream out(path);
            if (!out) throw std::invalid_argument("Cannot open file.");

            for (auto& op: canvas) {
                out << op.text << "\n";
            }

            return NOP;
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("Invalid canvas dimensions.");
        }
    }
};

#endif //CPPPICASSO_SAVE_COMMAND_H