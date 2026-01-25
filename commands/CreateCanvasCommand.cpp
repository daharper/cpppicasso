#include "CreateCanvasCommand.h"

std::string CreateCanvasCommand::getName() const {
    return "C";
}

std::string CreateCanvasCommand::getDescription() const {
    return "C width height [color backcolor]- creates a new canvas: C 10 4 white black";
}

Operation& CreateCanvasCommand::execute(Canvas& canvas, const CommandObject& command) {
    if (command.params.size() < 2 || command.params.size() > 4) {
        throw std::invalid_argument("Invalid number of parameters.");
    }

    int width, height = 0;

    std::string color = Canvas::DEFAULT_COLOR;
    std::string bgColor = Canvas::DEFAULT_BG_COLOR;

    try {
        width = std::stoi(command.params[0]);
        height = std::stoi(command.params[1]);

        if (command.params.size() > 2) {
            color = command.params[2];

            if (command.params.size() > 3) {
                bgColor = command.params[3];
            }
        }
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Invalid canvas dimensions.");
    }

    return canvas.create(command.text, width, height, color, bgColor);
}
