#include "Renderer.h"

#include <iostream>
#include <ostream>
#include <variant>

template<class... Ts>
struct overloads : Ts... { using Ts::operator()...; };

void Renderer::execute(const Canvas &canvas) {
    for (const auto&[operation, steps]: canvas) {
        std::cout << operation << std::endl;

        const auto visitor = overloads {
              [](const SetCanvas& c) { drawBorder(c); },
              [](SetColor) { std::cout << "\tsetting color" << std::endl; },
              [](SetBgColor) { std::cout << "\tsetting bg color" << std::endl; },
              [](SetPen) { std::cout << "\tsetting pen" << std::endl; },
              [](SetBgPen) { std::cout << "\tsetting bg pen" << std::endl; },
              [](const SetPixel&) { std::cout << "\tsetting pixel" << std::endl; }
          };

        for (auto& step: steps) {
            std::visit(visitor, step);
        }
    }
}

void Renderer::drawBorder(const SetCanvas& op) {
    const std::string xLine = '~' + std::string(op.width, '~') + '~';
    const std::string yLine = '~' + std::string(op.width, ' ') + '~';

    std::cout << xLine << std::endl;

    for (int y = 0; y < op.height; y++) {
        std::cout << yLine << std::endl;
    }

    std::cout << xLine << std::endl;
}
