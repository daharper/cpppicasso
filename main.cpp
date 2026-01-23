#include <iostream>
#include <string>
#include <sstream>
#include "Canvas.h"
#include "commands/CommandInputParser.h"
#include "commands/CommandObject.h"
#include "commands/UserCommandManager.h"

int main() {
    Canvas canvas;
    const auto command = CommandInputParser::parse("C 10 4");

    if (command == std::nullopt) {
        std::cout << "Invalid command" << std::endl;
        exit(1);
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

    return 0;
}
