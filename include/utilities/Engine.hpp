#ifndef ENGINE_H
#define ENGINE_H

#include <glad/glad.h>
#include "../../include/utilities/window.h"
#include "../../include/utilities/renderer.hpp"
#include "../../include/utilities/object.h"
#include "../../include/utilities/shader.h"
#include "../../include/utilities/Camera.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Engine {
public:
    Engine();
    void run();

private:
    Window window;
    Renderer renderer;
    Camera camera;
    Shader program;
    Object obj;
    glm::mat4 model;
    glm::mat4 projection;
    bool firstMouse;
    float lastX, lastY;

    void processInput(float deltaTime);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif