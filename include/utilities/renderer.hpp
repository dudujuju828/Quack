
#ifndef RENDERER_H
#define RENDERER_H

#include "../../include/GLFW/glfw3.h"

class Renderer {
    private:

    public:
    void pollAndSwap(GLFWwindow* window);
    void drawScene();
};

#endif 