#ifndef CPPPICASSO_PLOT_COMMAND_H
#define CPPPICASSO_PLOT_COMMAND_H

#include <string>
#include "Command.h"

class PlotCommand : public Command {
public:
    [[nodiscard]] std::string getName() const override;
    [[nodiscard]] std::string getDescription() const override;

    Operation& execute(Canvas& canvas, const CommandObject& command) override;
};


#endif //CPPPICASSO_PLOT_COMMAND_H