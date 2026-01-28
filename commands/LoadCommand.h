#ifndef CPPPICASSO_LOAD_COMMAND_H
#define CPPPICASSO_LOAD_COMMAND_H

#include <fstream>
#include <iostream>
#include <string>
#include "../command/Command.h"
#include "../command/CommandInputParser.h"
#include "../command/CommandManager.h"
#include "../graphics/Console.h"

class LoadCommand : public Command {
public:
    [[nodiscard]] std::string getName() const override {
        return "O";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "open file";
    }

    [[nodiscard]] std::string getExample() const override {
        return "O hello.txt";
    }

    [[nodiscard]] std::string getFormat() const override {
        return "O file";
    }

    Operation& execute(Canvas& canvas, const CommandObject& command) override {
        if (command.params.size() != 1) {
            throw std::invalid_argument("Invalid number of parameters.");
        }

        auto& path = command.params[0];

        std::string text;

        try {
            std::ifstream in(path);
            if (!in) throw std::invalid_argument("Cannot open file.");

            canvas.removeOperations();

            auto& manager = CommandManager::getInstance();

            while (std::getline(in, text)) {
                const auto getInput = CommandInputParser::parse(text);

                if (getInput != std::nullopt) {
                    const auto& cmd = getInput.value();
                    const auto& op = manager.execute(canvas, cmd);

                    if (op != NOP) {
                        Console::execute(op);
                    }
                }
            }

            return NOP;
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("Error importing file: " + text);
        }
    }
};

#endif //CPPPICASSO_LOAD_COMMAND_H