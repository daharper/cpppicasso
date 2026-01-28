#include "CommandManager.h"

#include "../commands/CanvasCommand.h"
#include "../commands/FillCommand.h"
#include "../commands/PlotCommand.h"
#include "../commands/UndoCommand.h"
#include "../commands/SetPenCommand.h"
#include "../commands/SaveCommand.h"
#include "../commands/LoadCommand.h"
#include "../commands/LineCommand.h"
#include "../commands/RectangleCommand.h"
#include "../commands/TriangleCommand.h"
#include "../commands/WriteCommand.h"

CommandManager::CommandManager() {
    add<FillCommand>();
    add<CanvasCommand>();
    add<LineCommand>();
    add<LoadCommand>();
    add<PlotCommand>();
    add<RectangleCommand>();
    add<SaveCommand>();
    add<SetPenCommand>();
    add<TriangleCommand>();
    add<UndoCommand>();
    add<WriteCommand>();
}

Operation& CommandManager::execute(Canvas& canvas, const CommandObject& command) {
    const auto it = commands.find(command.name);

    if (it == commands.end())
        throw std::invalid_argument("Invalid command.");

    return it->second->execute(canvas, command);
}