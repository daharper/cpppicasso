#include "PlotCommand.h"

struct CommandObject;

std::string PlotCommand::getName() const {
    return "P";
}

std::string PlotCommand::getDescription() const {
    return "P x y [pen]- plots on the canvas: P 4 4 @";
}

Operation& PlotCommand::execute(Canvas& canvas, const CommandObject& command) {
    if (command.params.size() < 2 || command.params.size() > 3) {
        throw std::invalid_argument("Invalid number of parameters.");
    }

    int width, height = 0;
    char pen = canvas.getPen();

    try {
        width = std::stoi(command.params[0]);
        height = std::stoi(command.params[1]);

        if (command.params.size() > 2) {
            pen = command.params[2][0];
        }
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Invalid canvas dimensions.");
    }

    return canvas.plot(command.text, width, height, pen);
}