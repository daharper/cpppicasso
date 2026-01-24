#include "Canvas.h"

void Canvas::blankCanvas() {
    if (width == 0 || height == 0) return;

    for (int y = 1; y <= height; y++) {
        for (int x = 1; x <= width; x++) {
            addStep(DrawPixel{x, y});
        }
    }
}