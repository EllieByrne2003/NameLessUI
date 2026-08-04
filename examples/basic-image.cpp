// Includes from standard
#include <filesystem>
#include <iostream>
#include <memory>

// Includes from third party libraries
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <glm/glm.hpp>
using namespace glm;

// Includes from personal libraries
#include <NLUT/logger/logger.hpp>
using Logger = NLUT::Logger;

#include <NLUI/window/window.hpp>
#include <NLUI/image/image.hpp>
using namespace NLUI;

// Includes from project


// Forward declarations


// Type aliases

int main() {
    std::cout << "Hello World!" << std::endl;

    Logger logger("example.log");

    Window *window = Window::createWindow(logger, "Basic image example", false, 150, 200);
    if(window == nullptr) {
        logger.addError("Failed to create window.");
        return -1;
    }

    std::shared_ptr<Image> image = Image::create("data/moonnormal.jpg", 1, 16, false);
    if(image == nullptr) {
        std::cout << "Failed to load image" << std::endl;
    }

    window->setComponent(image);

    do {
        window->draw();
        glfwPollEvents();
    } while(!window->shouldClose());

    return 0;
}