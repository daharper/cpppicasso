#include "CreateCanvasCommand.h"

std::string CreateCanvasCommand::getName() const {
    return "C";
}

std::string CreateCanvasCommand::getDescription() const {
    return "C 10 4 - Creates a new canvas with a width of 10 and height of 4";
}

void CreateCanvasCommand::execute(Canvas& canvas, const std::vector<std::string>& params) {
    if (params.size() != 2) {
        throw std::invalid_argument("Invalid number of parameters.");
    }

    int width, height = 0;

    try {
        width = std::stoi(params[0]);
        height = std::stoi(params[1]);
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Invalid canvas dimensions.");
    }

    canvas.create(width, height);
}
