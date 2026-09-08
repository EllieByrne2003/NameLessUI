// Includes from standard
#include <iostream>
#include <memory>

// Includes from third party libraries
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

// Includes from personal libraries
#include <NLUT/logger/logger.hpp>
using Logger = NLUT::Logger;

#include <NLUI/window/window.hpp>
#include <NLUI/panes/borderPane.hpp>
#include <NLUI/spacer/spacer.hpp>
using namespace NLUI;

// Includes from project


// Forward declarations


// Type aliases

int main() {
    std::cout << "Hello World!" << std::endl;

    Logger logger("example.log");

    Window *window = Window::createWindow(logger, "Basic borderPane example", false, 500, 370);
    if(window == nullptr) {
        logger.addError("Failed to create window.");
        return -1;
    }

    std::shared_ptr<BorderPane> mainPane = BorderPane::create(true);
    mainPane->setBackgroundColour(0.5, 0.5, 0.5);

    std::shared_ptr<Spacer> centre = Spacer::create(ivec2(100, 100), ivec2(50, 50));
    centre->setBackgroundColour(0.25, 0.0, 0.0);
    mainPane->setCentre(centre);

    std::shared_ptr<Spacer> north = Spacer::create(ivec2(50, 80), ivec2(50, 70), ivec2(125, 125));
    north->setBackgroundColour(0.0, 0.25, 0.0);
    mainPane->setNorth(north);

    // std::shared_ptr<Spacer> south = Spacer::create(ivec2(75, 50), ivec2(75, 50), ivec2(150, 150));
    // south->setBackgroundColour(0.0, 0.0, 0.25);
    // mainPane->setSouth(south);

    std::shared_ptr<Spacer> east = Spacer::create(ivec2(100, 50), ivec2(50, 50), ivec2(150, 150));
    east->setBackgroundColour(0.25, 0.25, 0.0);
    mainPane->setEast(east);

    // std::shared_ptr<Spacer> west = Spacer::create(ivec2(100, 50), ivec2(50, 50), ivec2(150, 150));
    // west->setBackgroundColour(0.25, 0.0, 0.25);
    // mainPane->setWest(west);


    window->setComponent(mainPane);

    do {
        window->draw();
        glfwPollEvents();
    } while(!window->shouldClose());

    return 0;
}