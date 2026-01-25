#ifndef CPPPICASSO_RENDERER_H
#define CPPPICASSO_RENDERER_H

#include "Canvas.h"

class Renderer {
public:
    static void execute(const Canvas& canvas);
private:
    static void drawBorder(const SetCanvas& op);
};


#endif //CPPPICASSO_RENDERER_H