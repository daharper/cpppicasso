#ifndef CPPPICASSO_COMMAND_H
#define CPPPICASSO_COMMAND_H

#include <string>
#include "CommandObject.h"
#include "../Core/Canvas.h"

class Command {
public:
    virtual ~Command() = default;

    [[nodiscard]] virtual std::string getName() const = 0;
    [[nodiscard]] virtual std::string getDescription() const = 0;
    [[nodiscard]] virtual std::string getFormat() const = 0;
    [[nodiscard]] virtual std::string getExample() const = 0;

    virtual Operation& execute(Canvas& canvas, const CommandObject& command) = 0;
};


#endif //CPPPICASSO_COMMAND_H
