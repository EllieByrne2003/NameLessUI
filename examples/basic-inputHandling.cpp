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

#include <NLUI/listeners/keyListener.hpp>
#include <NLUI/listeners/mouseButtonListener.hpp>
#include <NLUI/listeners/mouseMotionListener.hpp>
#include <NLUI/listeners/mouseScrollListener.hpp>
#include <NLUI/window/window.hpp>
#include <NLUI/panes/borderPane.hpp>
#include <NLUI/spacer/spacer.hpp>
using namespace NLUI;

// Includes from project


// Forward declarations


// Type aliases

int main() {
    class LocalKeyListener : public NLUI::KeyListener {
        void keyPressed(const int key)  { std::cout << "Key: " << key << " pressed" << std::endl; };
        void keyRepeated(const int key) { std::cout << "Key: " << key << " repeated" << std::endl; };
        void keyReleased(const int key) { std::cout << "Key: " << key << " released" << std::endl; };
    };

    class LocalMouseButtonListener : public NLUI::MouseButtonListener {
        void mousePressed(const int key, const double xPos, const double yPos)  { std::cout << "Mouse button: " << key << " pressed  at: " << xPos << ", " << yPos  << std::endl; }
        void mouseRepeated(const int key, const double xPos, const double yPos) { std::cout << "Mouse button: " << key << " repeated at: " << xPos << ", " << yPos  << std::endl; };
        void mouseReleased(const int key, const double xPos, const double yPos) { std::cout << "Mouse button: " << key << " released at: " << xPos << ", " << yPos  << std::endl; };
    };

    class LocalMouseMotionListener : public NLUI::MouseMotionListener {
        void mouseMoved(const double xPos, const double yPos, const double deltaX, const double deltaY) { std::cout << "Mouse moved: " << deltaX << ", " << deltaY << " to: " << xPos << ", " << yPos << std::endl; };
    };

    class LocalMouseScrollListener : public NLUI::MouseScrollListener {
        void mouseScrolled(const double deltaX, const double deltaY) { std::cout << "Scrolled: " << deltaX << ", " << deltaY << std::endl; };
    };

    std::cout << "Hello World!" << std::endl;

    Logger logger("example.log");

    Window *window = Window::createWindow(logger, "Basic gridPane example", false, 500, 370);
    if(window == nullptr) {
        logger.addError("Failed to create window.");
        return -1;
    }

    std::shared_ptr<BorderPane> mainPane = BorderPane::create(false);
    mainPane->setBackgroundColour(0.5, 0.5, 0.5);

    std::shared_ptr<Spacer> centre = Spacer::create(ivec2(100, 100), ivec2(50, 50));
    centre->setBackgroundColour(0.25, 0.0, 0.0);
    centre->addMouseButtonListener(new LocalMouseButtonListener);
    mainPane->setCentre(centre);

    std::shared_ptr<Spacer> north = Spacer::create(ivec2(50, 80), ivec2(50, 70), ivec2(125, 125));
    north->setBackgroundColour(0.0, 0.25, 0.0);
    north->addKeyListener(new LocalKeyListener);
    mainPane->setNorth(north);

    std::shared_ptr<Spacer> south = Spacer::create(ivec2(75, 50), ivec2(75, 50), ivec2(150, 150));
    south->setBackgroundColour(0.0, 0.0, 0.25);
    mainPane->setSouth(south);

    std::shared_ptr<Spacer> east = Spacer::create(ivec2(100, 50), ivec2(50, 50), ivec2(150, 150));
    east->setBackgroundColour(0.25, 0.25, 0.0);
    east->addMouseScrollListener(new LocalMouseScrollListener);
    mainPane->setEast(east);

    std::shared_ptr<Spacer> west = Spacer::create(ivec2(100, 50), ivec2(50, 50), ivec2(150, 150));
    west->setBackgroundColour(0.25, 0.0, 0.25);
    west->addMouseMotionListener(new LocalMouseMotionListener);
    mainPane->setWest(west);

    window->setComponent(mainPane);

    do {
        window->draw();
        glfwPollEvents();
    } while(!window->shouldClose());

    return 0;
}