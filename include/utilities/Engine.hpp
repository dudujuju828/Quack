
#ifndef ENGINE_H
#define ENGINE_H

#include "../../include/utilities/renderer.hpp"
#include "../../include/utilities/window.h"


class Engine {
    Renderer renderer;
    Window window;

    public:
    Engine();

    void run();
};

#endif 