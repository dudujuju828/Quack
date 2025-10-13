
#include "../../include/utilities/resource_manager.hpp"
#include "../../include/utilities/renderer.hpp"

class Engine {
    ResourceManager manager;
    Renderer renderer;

    public:
    void loop();
}