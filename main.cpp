#include <iostream>
#include <string>
#include <sstream>
#include "Graphics/Canvas.h"
#include "commands/CommandInputParser.h"
#include "commands/CommandObject.h"
#include "commands/UserCommandManager.h"

int main() {
    Canvas canvas;

    std::string input;

    while (true) {
        std::cout << "?" << " " << std::flush;
        std::getline(std::cin, input);

        input = String::trim(input);

        if (input == "Q" || input == "q") break;

        const auto command = CommandInputParser::parse(input);

        if (command == std::nullopt) {
            std::cout << "Unknown command" << std::endl;
            continue;
        }

        auto& manager = UserCommandManager::getInstance();

        if (auto result = manager.execute(canvas, command.value())) {
            std::cout << "rendering canvas" << std::endl;
        } else {
            std::cout <<  result.error() << std::endl;
        }

        for (const auto&[text, steps] : canvas) {
            std::cout << text << std::endl;
        }
    }

    std::cout << std::endl << "Thanks for playing!" << std::endl;

    return 0;
}