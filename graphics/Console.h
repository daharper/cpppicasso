#ifndef CPPPICASSO_RENDERER_H
#define CPPPICASSO_RENDERER_H

#include "Canvas.h"

class Console {
public:
    static std::string prompt();
    static void clearScreen();
    static void blankCanvasArea();

    static void moveCursor(int x, int y);

    static void dumpPixelBuffer() ;

    static void write(const std::string& text);
    static void writeLine(const std::string& text);
    static void writeAt(const std::string& text, int x, int y);
    static void writeLineAt(const std::string& text, int x, int y);

    static void execute(const Canvas& canvas);
    static void execute(const Operation &operation);

    static void createCanvas(const SetCanvas& op);
    static void drawPixel(const SetPixel& op);

private:
    inline static void drawBorder(int width, int height);
};

#endif //CPPPICASSO_RENDERER_H