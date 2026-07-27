// Includes from standard
#include <iostream>

// Includes from third party libraries
#include <GLFW/glfw3.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// Includes from personal libraries
#include <NLUT/logger/logger.hpp>
using Logger = NLUT::Logger;

#include <NLUI/window/window.hpp>
#include <NLUI/panes/flowPane.hpp>
using namespace NLUI;

// Includes from project


// Forward declarations


// Type aliases


json jsonWindow = "{ \"title\": \"Testing :D\", \"width\": 640, \"height\": 640, \"fullscreen\": false }";

int main() {
    std::cout << "Hello World!" << std::endl;

    Logger logger("example.log");

    Window *window = Window::createWindow(logger, "Basic window example", false, 640, 640);
    if(window == nullptr) {
        logger.addError("Failed to create window.");
        return -1;
    }

    FlowPane *pane = new FlowPane();
    pane->setMinimumSize(200, 200);
    pane->setBackgroundColour(1.0, 0.0, 0.0);

    window->setComponent(pane);

    do {
        window->draw();
        glfwPollEvents();
    } while(!window->shouldClose());

    return 0;
}