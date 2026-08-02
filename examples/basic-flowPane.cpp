// Includes from standard
#include <iostream>
#include <memory>

// Includes from third party libraries
#include <GLFW/glfw3.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <glm/glm.hpp>
using namespace glm;

// Includes from personal libraries
#include <NLUT/logger/logger.hpp>
using Logger = NLUT::Logger;

#include <NLUI/window/window.hpp>
#include <NLUI/panes/flowPane.hpp>
#include <NLUI/spacer/spacer.hpp>
using namespace NLUI;

// Includes from project


// Forward declarations


// Type aliases

int main() {
    std::cout << "Hello World!" << std::endl;

    Logger logger("example.log");

    Window *window = Window::createWindow(logger, "Basic flowPane example", false, 150, 200);
    if(window == nullptr) {
        logger.addError("Failed to create window.");
        return -1;
    }

    std::shared_ptr<FlowPane> mainPane = FlowPane::create();
    mainPane->setBackgroundColour(0.5, 0.5, 0.5);

    std::shared_ptr<Spacer> spacer1 = Spacer::create(ivec2(150, 50), ivec2(100, 50));
    spacer1->setBackgroundColour(0.25, 0.0, 0.0);
    mainPane->addComponent(spacer1);

    std::shared_ptr<Spacer> spacer2 = Spacer::create(ivec2(50, 80), ivec2(50, 70));
    spacer2->setBackgroundColour(0.0, 0.25, 0.0);
    mainPane->addComponent(spacer2);

    std::shared_ptr<Spacer> spacer3 = Spacer::create(ivec2(75, 50), ivec2(75, 50));
    spacer3->setBackgroundColour(0.0, 0.0, 0.25);
    mainPane->addComponent(spacer3);

    std::shared_ptr<Spacer> spacer4 = Spacer::create(ivec2(50, 50), ivec2(50, 50));
    spacer4->setBackgroundColour(0.25, 0.25, 0.0);
    mainPane->addComponent(spacer4);

    window->setComponent(mainPane);

    do {
        window->draw();
        glfwPollEvents();
    } while(!window->shouldClose());

    return 0;
}