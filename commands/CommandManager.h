#ifndef CPPPICASSO_COMMAND_MANAGER_H
#define CPPPICASSO_COMMAND_MANAGER_H

#include <expected>
#include <map>
#include <memory>

#include "../Utils.h"
#include "Command.h"
#include "CommandObject.h"

class CommandManager {
public:
    static CommandManager& getInstance() {
        static CommandManager instance;
        return instance;
    }

    CommandManager(const CommandManager&) = delete;
    CommandManager& operator=(const CommandManager&) = delete;

    std::expected<void, std::string> execute(Canvas& canvas, const CommandObject& command);

private:
    CommandManager();
    ~CommandManager() = default;

    template<std::derived_from<Command> T>
    void add() {
        auto command = std::make_unique<T>();
        std::string name = command->getName();
        commands.emplace(std::move(name), std::move(command));
    }

    std::map<std::string, std::unique_ptr<Command>, CaseInsensitiveLess> commands;
};

#endif //CPPPICASSO_COMMAND_MANAGER_H