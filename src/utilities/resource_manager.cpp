


#include "../../include/GLFW/glfw3.h"
#include "../../include/utilities/window.h"


class ResourceManager {
    private:
    Window window;

    public:
    ResourceManager() : window(800,600,"title") {
        std::cout << "Resource manager created" << std::endl;
    }

};