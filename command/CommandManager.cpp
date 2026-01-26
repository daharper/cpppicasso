#include "CommandManager.h"

#include "../commands/CreateCanvasCommand.h"
#include "../commands/PlotCommand.h"

CommandManager::CommandManager() {
    add<CreateCanvasCommand>();
    add<PlotCommand>();
}

Operation& CommandManager::execute(Canvas& canvas, const CommandObject& command) {
    const auto it = commands.find(command.name);

    if (it == commands.end())
        throw std::invalid_argument("Invalid command.");

    return it->second->execute(canvas, command);
}