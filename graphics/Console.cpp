#include "Console.h"

#include <iostream>
#include <ostream>
#include <variant>

#include "PixelBuffer.h"

template<class... Ts>
struct overloads : Ts... { using Ts::operator()...; };

static auto visitor = overloads {
    [](const SetCanvas& op) { Console::createCanvas(op); },
    [](const SetPixel& op) { Console::drawPixel(op); }
};

void Console::execute(const Operation& operation) {
    for (auto& step: operation.steps) {
        std::visit(visitor, step);
    }
}

void Console::execute(const Canvas &canvas) {
    for (const auto&[opKind, op, steps]: canvas) {
        for (auto& step: steps) {
            std::visit(visitor, step);
        }
    }

    moveCursor(0, canvas.getHeight() + 4);
}

void Console::createCanvas(const SetCanvas& op) {
    PixelBuffer::getInstance().setSize(op.width, op.height);

    blankCanvasArea();
    drawBorder(op.width, op.height);
}

void Console::drawBorder(const int width, const int height) {
    const std::string xLine = '-' + std::string(width, '-') + '-';
    const std::string yLine = '|' + std::string(width, ' ') + '|';

    moveCursor(0, 3);

    std::cout << xLine << std::endl;

    for (int y = 0; y < height; y++) {
        std::cout << yLine << std::endl;
    }

    std::cout << xLine << std::endl;
}

void Console::drawPixel(const SetPixel& op) {
    PixelBuffer::getInstance().setPixel(op.x, op.y, op.pen);

    moveCursor(op.x + 1, op.y + 3);
    std::cout << op.text << std::flush;
}

void Console::writeLine(const std::string& text) {
    std::cout << text << std::endl << std::flush;
}
void Console::write(const std::string& text) {
    std::cout << text << std::flush;
}

void Console::writeAt(const std::string& text, const int x, const int y) {
    moveCursor(x, y);
    write(text);
}

void Console::writeLineAt(const std::string& text, const int x, const int y) {
    moveCursor(x, y);
    writeLine(text);
}

void Console::blankCanvasArea() {
    const auto blank = std::string(Canvas::MAX_WIDTH + 2, ' ');

    int y{2};

    for (int i = 0; i <= Canvas::MAX_HEIGHT; i++) {
        writeAt(blank, 0, ++y);
    }
}

void Console::clearScreen() {
    std::cout << "\033[2J\033[H" << std::flush;
}

void Console::moveCursor(const int x, const int y) {
    std::cout << "\033[" << y << ";" << x << "H" << std::flush;
}

void Console::dumpPixelBuffer() {
    const int width = PixelBuffer::getInstance().getWidth();
    const int height = PixelBuffer::getInstance().getHeight();

    moveCursor(120, 3);

    for (int y = 1; y <= height; y++) {
        std::string line;

        for (int x = 1; x <= width; x++) {
            line += PixelBuffer::getInstance().getPixel(x, y);
        }

        writeAt(line, 120, 2 + y);
    }
}

std::string Console::prompt() {
    std::string text;

    while (String::isBlank(text)) {
        writeAt("                                                     ", Canvas::MAX_WIDTH + 4, Canvas::MAX_HEIGHT + 9);
        writeAt("? ", Canvas::MAX_WIDTH + 4, Canvas::MAX_HEIGHT + 9);

        std::getline(std::cin, text);
        text = String::trim(text);
    }

    // shortcut for demos
    if (text == "1" || text == "2") {
        text = "o demo" + text + ".txt";
    }

    return text;
}