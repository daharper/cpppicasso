#ifndef CPPPICASSO_CREATE_CANVAS_COMMAND_H
#define CPPPICASSO_CREATE_CANVAS_COMMAND_H

#include "Command.h"

class CreateCanvasCommand : public Command{
public:
    [[nodiscard]] std::string getName() const override;
    [[nodiscard]] std::string getDescription() const override;

    void execute(Canvas& canvas, const std::vector<std::string>& params) override;
};

#endif //CPPPICASSO_CREATE_CANVAS_COMMAND_H
