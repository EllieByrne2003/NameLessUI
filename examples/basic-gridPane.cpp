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
#include <NLUI/panes/gridPane.hpp>
#include <NLUI/spacer/spacer.hpp>
using namespace NLUI;

// Includes from project


// Forward declarations


// Type aliases

int main() {
    std::cout << "Hello World!" << std::endl;

    Logger logger("example.log");

    Window *window = Window::createWindow(logger, "Basic gridPane example", false, 50, 50);
    if(window == nullptr) {
        logger.addError("Failed to create window.");
        return -1;
    }

    GridPane *mainPane = new GridPane(2, 3);
    // mainPane->setMinimumSize(200, 200);
    mainPane->setBackgroundColour(0.5, 0.5, 0.5);

    Spacer *spacer1 = new Spacer();
    spacer1->setMinimumSize(150, 150);
    spacer1->setPreferredSize(150, 150);
    spacer1->setBackgroundColour(0.25, 0.0, 0.0);
    mainPane->addComponent(spacer1, 1, 0);

    Spacer *spacer2 = new Spacer();
    spacer2->setMinimumSize(50, 70);
    spacer2->setPreferredSize(50, 80);
    spacer2->setBackgroundColour(0.0, 0.25, 0.0);
    mainPane->addComponent(spacer2, 1, 1);

    Spacer *spacer3 = new Spacer();
    spacer3->setMinimumSize(75, 50);
    spacer3->setPreferredSize(75, 50);
    spacer3->setBackgroundColour(0.0, 0.0, 0.25);
    mainPane->addComponent(spacer3, 0, 1);

    Spacer *spacer4 = new Spacer();
    spacer4->setMinimumSize(100, 50);
    spacer4->setPreferredSize(100, 50);
    spacer4->setBackgroundColour(0.25, 0.25, 0.0);
    mainPane->addComponent(spacer4, 0, 2);

    // Spacer *spacer4 = new Spacer();
    // spacer4->setMinimumSize(50, 50);
    // spacer4->setPreferredSize(50, 50);
    // spacer4->setBackgroundColour(0.25, 0.25, 0.0);
    // mainPane->addComponent(spacer4, 0, 2);

    window->setComponent(mainPane);
    // mainPane->resize(); // TODO should be called automatically on pane resizes

    do {
        window->draw();
        glfwPollEvents();
    } while(!window->shouldClose());

    return 0;
}