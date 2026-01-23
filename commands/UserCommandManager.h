#ifndef CPPPICASSO_COMMAND_MANAGER_H
#define CPPPICASSO_COMMAND_MANAGER_H

#include <expected>
#include <map>
#include <memory>

#include "../Utils.h"
#include "UserCommand.h"
#include "CommandObject.h"

class UserCommandManager {
public:
    static UserCommandManager& getInstance() {
        static UserCommandManager instance;
        return instance;
    }

    UserCommandManager(const UserCommandManager&) = delete;
    UserCommandManager& operator=(const UserCommandManager&) = delete;

    std::expected<void, std::string> execute(Canvas& canvas, const CommandObject& command);

private:
    UserCommandManager();
    ~UserCommandManager() = default;

    template<std::derived_from<UserCommand> T>
    void add() {
        auto command = std::make_unique<T>();
        std::string name = command->getName();
        commands.emplace(std::move(name), std::move(command));
    }

    std::map<std::string, std::unique_ptr<UserCommand>, CaseInsensitiveLess> commands;
};

#endif //CPPPICASSO_COMMAND_MANAGER_H