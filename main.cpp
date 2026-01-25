#include <iostream>
#include <ranges>
#include <string>
#include <sstream>
#include "Core/Canvas.h"
#include "commands/CommandInputParser.h"
#include "commands/CommandObject.h"
#include "commands/CommandManager.h"
#include "Core/Console.h"

int main() {
    Canvas canvas;

    Console::clearScreen();

    int y = 0;

    for (const auto &command: CommandManager::getInstance() | std::views::values) {
        Console::writeAt(" - " + command->getDescription(), Canvas::MAX_WIDTH + 4, ++y);
    }

    std::string text;

    while (true) {
        Console::writeAt("                                                     ", 0, Canvas::MAX_HEIGHT + 4);
        Console::writeAt("? ", 0, Canvas::MAX_HEIGHT + 4);

        std::getline(std::cin, text);

        text = String::trim(text);

        if (text == "Q" || text == "q") break;

        const auto getInput = CommandInputParser::parse(text);
        if (getInput == std::nullopt) continue;

        auto& manager = CommandManager::getInstance();

        try {
            auto operation = manager.execute(canvas, getInput.value());

            Console::execute(operation);
            //   Console::execute(canvas);
        } catch (const std::invalid_argument& e) {
            // ignore for now...
        }
    }

    Console::writeLine("Thanks for playing!");

    return 0;
}
