
#include <iostream>
#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"
#include"../../include/utilities/window.h"

Window::Window(int width, int height, const char* title) {
        glfwInit();
        p_window_ptr = glfwCreateWindow(width,height,title,nullptr,nullptr);
        glfwMakeContextCurrent(p_window_ptr);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    }

GLFWwindow* Window::get_window_ptr() {
    return p_window_ptr;
}

bool Window::notClosed() {
    return !glfwWindowShouldClose(p_window_ptr);
}

