#include <iostream>
#include <string>
#include <sstream>
#include "Graphics/Canvas.h"
#include "commands/CommandInputParser.h"
#include "commands/CommandObject.h"
#include "commands/CommandManager.h"
#include "Graphics/Renderer.h"

int main() {
    Canvas canvas;

    std::string input;

    while (true) {
        std::cout << "?" << " " << std::flush;
        std::getline(std::cin, input);

        input = String::trim(input);

        if (input == "Q" || input == "q") break;

        const auto operation = CommandInputParser::parse(input);

        if (operation == std::nullopt) {
            std::cout << "Unknown command" << std::endl;
            continue;
        }

        auto& manager = CommandManager::getInstance();

        if (auto result = manager.execute(canvas, operation.value())) {
            Renderer::execute(canvas);
        } else {
            std::cout <<  result.error() << std::endl;
        }
    }

    std::cout << std::endl << "Thanks for playing!" << std::endl;

    return 0;
}
