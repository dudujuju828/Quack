
#include <iostream>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"
#include "../../include/utilities/window.h"
#include "../../include/utilities/renderer.hpp"
#include "../../include/utilities/Engine.hpp"

Engine::Engine() : window(800,600,"title") {
    std::cout << "created";
}

void Engine::run() {
    while (window.notClosed()) {
        renderer.drawScene();

        renderer.pollAndSwap(window.get_window_ptr());
    }
}

