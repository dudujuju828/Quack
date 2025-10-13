
#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"
#include "../../include/utilities/renderer.hpp"


void Renderer::pollAndSwap(GLFWwindow * window) {
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void Renderer::drawScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.8f,0.8f,0.8f,1.0f);
}