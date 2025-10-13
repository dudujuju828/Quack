
#include <iostream>
#include "../../include/GLFW/glfw3.h"
#include "../../include/glad/glad.h"

class Window {
    private:
    GLFWwindow* p_window_ptr;



    public:
    Window(int width, int height, const char* title) {
        glfwInit();
        p_window_ptr = glfwCreateWindow(width,height,title,nullptr,nullptr);
        glfwMakeContextCurrent(p_window_ptr);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    }

    GLFWwindow* get_window_ptr() {
        return p_window_ptr;
    }

};
