#include "UserCommandManager.h"

#include "CreateCanvasUserCommand.h"

UserCommandManager::UserCommandManager() {
    add<CreateCanvasUserCommand>();
}

std::expected<void, std::string> UserCommandManager::execute(Canvas& canvas, const CommandObject& command) {
    const auto it = commands.find(command.name);

    if (it == commands.end()) {
        return std::unexpected("Unknown command");
    }

    canvas.addCommand(command.text);

    try {
        it->second->execute(canvas, command.params);
        return {};
    } catch (const std::exception& e) {
        canvas.undo();
        return std::unexpected(e.what());
    }
}