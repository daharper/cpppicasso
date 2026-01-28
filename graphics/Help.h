#ifndef CPPPICASSO_HELP_H
#define CPPPICASSO_HELP_H

#include <ranges>
#include "Console.h"
#include "../command/CommandManager.h"

class Help {
public:
    using ShowLastCommand = void (*)(const std::string&);

    static void showLastCommand(const std::string& command) {
        Console::writeAt(
            "                                                                                             ",
            m_lastCommandX,
            m_lastCommandY);

        Console::writeAt("> " + command, m_lastCommandX, m_lastCommandY);
    }

    static ShowLastCommand show() {
        const std::string minX = std::to_string(Canvas::MIN_WIDTH);
        const std::string maxX = std::to_string(Canvas::MAX_WIDTH);
        const std::string minY = std::to_string(Canvas::MIN_HEIGHT);
        const std::string maxY = std::to_string(Canvas::MAX_HEIGHT);

        int y{0};

        Console::writeAt("Canvas:", 0, 1);
        Console::writeAt("Canvas Commands:", Canvas::MAX_WIDTH + 4, ++y);
        ++y;
        Console::writeAt("---------------------------------------------------------------------------------------------", Canvas::MAX_WIDTH + 4, ++y);
        Console::writeAt("| # |     Description     |              Format                |           Example          |", Canvas::MAX_WIDTH + 4, ++y);
        Console::writeAt("---------------------------------------------------------------------------------------------", Canvas::MAX_WIDTH + 4, ++y);

        for (const auto &command: CommandManager::getInstance() | std::views::values) {
            Console::writeAt("| " + command->getName(), Canvas::MAX_WIDTH + 4, ++y);
            Console::writeAt("| " + command->getDescription(), Canvas::MAX_WIDTH + 8, y);
            Console::writeAt("| " + command->getFormat(), Canvas::MAX_WIDTH + 30, y);
            Console::writeAt("| " + command->getExample(), Canvas::MAX_WIDTH + 67, y);
            Console::writeAt("|", Canvas::MAX_WIDTH + 96, y);
        }

        Console::writeAt("---------------------------------------------------------------------------------------------", Canvas::MAX_WIDTH + 4, ++y);
        ++y;
        Console::writeAt("Constraints:", Canvas::MAX_WIDTH + 4, ++y);
        ++y;
        Console::writeAt("- Canvas: width (" + minX + "-" + maxX + "), height (" + minY + "-" + maxY + ")", Canvas::MAX_WIDTH + 4, ++y);
        Console::writeAt("- Colors: black, red, green, yellow, blue, magenta, cyan, white", Canvas::MAX_WIDTH + 4, ++y);
        ++y;
        Console::writeAt("Game Commands:", Canvas::MAX_WIDTH + 4, ++y);
        ++y;
        Console::writeAt("- Q to quit", Canvas::MAX_WIDTH + 4, ++y);
        ++y;
        Console::writeAt("Last Command:", Canvas::MAX_WIDTH + 4, ++y);
        ++y;
        ++y;

        m_lastCommandX = Canvas::MAX_WIDTH + 4;
        m_lastCommandY = y;

        showLastCommand("");

        return showLastCommand;
    }

private:
    inline static int m_lastCommandX;
    inline static int m_lastCommandY;
};

#endif //CPPPICASSO_HELP_H