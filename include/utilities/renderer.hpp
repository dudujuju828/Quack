
#ifndef RENDERER_H
#define RENDERER_H

#include "../../include/GLFW/glfw3.h"
#include "../../include/utilities/object.h"


class Renderer {
    private:

    public:
    void pollAndSwap(GLFWwindow* window);
    void clearScene();
    void drawArrays(Object &obj);
};

#endif 