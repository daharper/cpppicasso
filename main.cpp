#include <iostream>
#include <string>
#include <sstream>
#include "Canvas.h"

int main() {
    Canvas canvas;

    canvas.addCommand("C 10 10");
    canvas.create(10, 10);

    canvas.addCommand("D 5 5");
    canvas.setPixel(1, 1);

    for (const auto&[text, steps] : canvas) {
        std::cout << text << std::endl;
    }

    return 0;
}