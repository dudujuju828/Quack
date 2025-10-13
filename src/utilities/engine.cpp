
#include <iostream>
#include <vector>

#include "../../include/utilities/window.h"
#include "../../include/utilities/renderer.hpp"
#include "../../include/utilities/Engine.hpp"
#include "../../include/utilities/object.h"
#include "../../include/utilities/shader.h"

Engine::Engine() : window(800,600,"title") {
    std::cout << "created";
}

void Engine::run() {

    std::vector<float> v = {-0.5f,-0.5f,0.0f,
                           0.5f,-0.5f,0.0f,
                           0.0f, 0.5f,0.0f };
    Shader program("src/shaders/vertex_shader.glsl","src/shaders/fragment_shader.glsl");
    Object obj(v,program.ID);
    while (window.notClosed()) {
        renderer.drawArrays(obj);

        renderer.pollAndSwap(window.get_window_ptr());
    }
}

