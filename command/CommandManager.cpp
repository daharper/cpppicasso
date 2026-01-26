#include "CommandManager.h"

#include "../commands/CanvasCommand.h"
#include "../commands/PlotCommand.h"
#include "../commands/UndoCommand.h"
#include "../commands/SetPenCommand.h"
#include "../commands/SaveCommand.h"
#include "../commands/LoadCommand.h"
#include "../commands/LineCommand.h"

CommandManager::CommandManager() {
    add<CanvasCommand>();
    add<LineCommand>();
    add<LoadCommand>();
    add<PlotCommand>();
    add<UndoCommand>();
    add<SetPenCommand>();
    add<SaveCommand>();
}

Operation& CommandManager::execute(Canvas& canvas, const CommandObject& command) {
    const auto it = commands.find(command.name);

    if (it == commands.end())
        throw std::invalid_argument("Invalid command.");

    return it->second->execute(canvas, command);
}