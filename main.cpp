#include <iostream>
#include <string>
#include "Core/Canvas.h"
#include "command/CommandInputParser.h"
#include "command/CommandObject.h"
#include "command/CommandManager.h"
#include "Core/Console.h"
#include "Core/Help.h"

int main() {
    Canvas canvas;

    Console::clearScreen();
    Help::show();

    while (true) {
        std::string text = Console::prompt();

        if (text == "Q" || text == "q") break;

        const auto getInput = CommandInputParser::parse(text);

        if (getInput == std::nullopt) continue;

        auto& manager = CommandManager::getInstance();

        try {
            auto operation = manager.execute(canvas, getInput.value());

            if (operation == NOP) continue;

            if (operation == UNDO) {
                Console::execute(canvas);
            } else {
                Console::execute(operation);
            }
        } catch (const std::invalid_argument& e) {
            // ignore for now...
        }
    }

    Console::writeLine("Thanks for playing!");

    return 0;
}
