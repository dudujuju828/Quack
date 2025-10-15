#include "../../include/utilities/Engine.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

Engine::Engine() : 
    window(800, 600, "title"),
    camera(glm::vec3(0.0f, 0.0f, 3.0f)),
    program("src/shaders/vertex_shader.glsl", "src/shaders/fragment_shader.glsl"),
    obj({-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f}, program.ID),
    firstMouse(true),
    lastX(400.0f), // Center of 800px width
    lastY(300.0f)  // Center of 600px height
{
    // Enable depth testing for 3D rendering
    glEnable(GL_DEPTH_TEST);

    // Set viewport
    glViewport(0, 0, 800, 600);

    // Initialize model matrix
    model = glm::mat4(1.0f);
    
    // Initialize projection matrix
    projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);

    // Set up mouse and scroll callbacks
    glfwSetWindowUserPointer(window.get_window_ptr(), this);
    glfwSetCursorPosCallback(window.get_window_ptr(), mouseCallback);
    glfwSetScrollCallback(window.get_window_ptr(), scrollCallback);

    // Capture mouse cursor for smooth rotation
    glfwSetInputMode(window.get_window_ptr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    std::cout << "Engine created" << std::endl;
}

void Engine::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    
    if (engine->firstMouse) {
        engine->lastX = static_cast<float>(xpos);
        engine->lastY = static_cast<float>(ypos);
        engine->firstMouse = false;
        return;
    }

    float xoffset = static_cast<float>(xpos) - engine->lastX;
    float yoffset = engine->lastY - static_cast<float>(ypos); // Reversed for natural pitch
    engine->lastX = static_cast<float>(xpos);
    engine->lastY = static_cast<float>(ypos);

    engine->camera.ProcessMouseMovement(xoffset, yoffset, true);
}

void Engine::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    engine->camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void Engine::processInput(float deltaTime) {
    GLFWwindow* windowPtr = window.get_window_ptr();
    
    // Exit on ESC
    if (glfwGetKey(windowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(windowPtr, true);
    
    // Keyboard input for camera movement
    if (glfwGetKey(windowPtr, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(windowPtr, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(windowPtr, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(windowPtr, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void Engine::run() {
    float lastFrame = 0.0f;
    
    while (window.notClosed()) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(deltaTime);

        renderer.clearScene();

        glUseProgram(program.ID);

        // Upload MVP matrices
        glm::mat4 view = camera.GetViewMatrix();
        GLint modelLoc = glGetUniformLocation(program.ID, "model");
        GLint viewLoc = glGetUniformLocation(program.ID, "view");
        GLint projLoc = glGetUniformLocation(program.ID, "projection");
        
        if (modelLoc == -1 || viewLoc == -1 || projLoc == -1) {
            std::cerr << "Error: Could not find MVP uniform locations" << std::endl;
        }

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);

        renderer.drawArrays(obj);

        renderer.pollAndSwap(window.get_window_ptr());
    }
}