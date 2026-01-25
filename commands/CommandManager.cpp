#include "CommandManager.h"

#include "CreateCanvasCommand.h"

CommandManager::CommandManager() {
    add<CreateCanvasCommand>();
}

std::expected<void, std::string> CommandManager::execute(Canvas& canvas, const CommandObject& command) {
    const auto it = commands.find(command.name);

    if (it == commands.end()) {
        return std::unexpected("Unknown command");
    }

    canvas.addOperation(command.text);

    try {
        it->second->execute(canvas, command.params);
        return {};
    } catch (const std::exception& e) {
        canvas.undoOperation();
        return std::unexpected(e.what());
    }
}