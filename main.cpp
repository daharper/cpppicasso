#include <iostream>
#include <string>
#include "Core/Canvas.h"
#include "command/CommandInputParser.h"
#include "command/CommandObject.h"
#include "command/CommandManager.h"
#include "Core/Console.h"
#include "Core/Help.h"
#include "Core/PixelBuffer.h"

int main() {
    Canvas canvas;

    Console::clearScreen();
    const auto showCommand = Help::show();

    auto& manager = CommandManager::getInstance();

    while (true) {
        const auto text = Console::prompt();

        showCommand(text);

        if (text == "Q" || text == "q") break;

        const auto getInput = CommandInputParser::parse(text);
        if (getInput == std::nullopt) continue;

        try {
            const auto& cmd = getInput.value();
            const auto& op = manager.execute(canvas, cmd);

            switch (op.kind) {
                case OpKind::Nop:
                    continue;
                case OpKind::Mutation:
                    Console::execute(canvas);
                    break;
                default:
                    Console::execute(op);
                    break;
            }

            Console::dumpPixelBuffer();

        } catch (const std::exception& e) {
            auto error = "Synax Error: " + text + " (" + std::string(e.what()) + ")";
            auto msg = error.size() > 60 ? error.substr(0, 57) + "..." : error;
            showCommand(msg);
        }
    }

    Console::clearScreen();
    Console::writeLine("Thanks for playing!");

    return 0;
}
