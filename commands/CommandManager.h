#ifndef CPPPICASSO_COMMAND_MANAGER_H
#define CPPPICASSO_COMMAND_MANAGER_H

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

    Operation& execute(Canvas& canvas, const CommandObject& command);

    /**
     * @brief Returns an iterator to the beginning of the command history.
     */
    [[nodiscard]] auto begin() { return commands.begin(); }
    [[nodiscard]] auto begin() const { return commands.begin(); }
    [[nodiscard]] auto cbegin() const { return commands.cbegin(); }

    /**
     * @brief Returns an iterator to the end of the command history.
     */
    [[nodiscard]] auto end() { return commands.end(); }
    [[nodiscard]] auto end() const { return commands.end(); }
    [[nodiscard]] auto cend() const { return commands.cend(); }

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