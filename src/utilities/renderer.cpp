
#include "../../include/glad/glad.h"
#include "../../include/utilities/renderer.hpp"
#include "../../include/utilities/object.h"


void Renderer::pollAndSwap(GLFWwindow * window) {
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void Renderer::drawScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.8f,0.8f,0.8f,1.0f);
}

void Renderer::drawArrays(Object &obj) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.8f,0.8f,0.8f,1.0f);

    glUseProgram(obj.programID);
    glBindVertexArray(obj.VertexArrayID);
    glDrawArrays(GL_TRIANGLES,0,3);

}