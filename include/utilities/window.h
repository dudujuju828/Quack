

#ifndef WINDOW_H
#define WINDOW_H


#include <iostream>
#include "../../include/GLFW/glfw3.h"

class Window {
    private:
    GLFWwindow* p_window_ptr;


    public:
    Window(int width, int height, const char* title);
    GLFWwindow* get_window_ptr();
    bool notClosed();

};

#endif