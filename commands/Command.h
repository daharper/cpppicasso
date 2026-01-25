#ifndef CPPPICASSO_COMMAND_H
#define CPPPICASSO_COMMAND_H

#include <string>
#include <vector>
#include "../Graphics/Canvas.h"

class Command {
public:
    virtual ~Command() = default;

    [[nodiscard]] virtual std::string getName() const = 0;
    [[nodiscard]] virtual std::string getDescription() const = 0;

    virtual void execute(Canvas& canvas, const std::vector<std::string>& params) = 0;
};


#endif //CPPPICASSO_COMMAND_H
