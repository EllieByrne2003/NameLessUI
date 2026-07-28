#include "window.hpp"

// Includes from standard
#include <fstream>
#include <glm/ext/matrix_clip_space.hpp>
#include <mutex>

// Includes from third party libraries
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

// Includes from personal libraries
#include <NLUT/windows/glfw.hpp>
#include <NLUT/gl/glew.hpp>

#include <NLUT/logger/logger.hpp>
using Logger = NLUT::Logger;

#include <NLUT/files/paths.hpp>
constexpr static auto getPath = NLUT::getPath;

// Includes from project
#include "../graphics/shaders.hpp"

// Forward declarations
bool intialiseGLFW(Logger &logger);
bool initialiseGLEW(Logger &logger, GLFWwindow *window);

// User input callbacks
void cursor_pos_callback(GLFWwindow *window, const double xpos, const double ypos);
void cursor_enter_callback(GLFWwindow *window, const int entered);

void mouse_button_callback(GLFWwindow *window, const int button, const int action, const int mods);
void mouse_scroll_callback(GLFWwindow *window, const double xOffset, const double yOffset);

void key_callback(GLFWwindow *window, const int key, const int scancode, const int action, const int mods);

void window_size_callback(GLFWwindow* window, int width, int height);

// TODO handle dynamic resizes

// Type aliases

static std::mutex contextMutex;

NLUI::Window::Window(GLFWwindow *const window, const int windowedX, const int windowedY, const int windowedWidth, const int windowedHeight) : 
    window(window), windowedX(windowedX), windowedY(windowedY), windowedWidth(windowedWidth), windowedHeight(windowedHeight) {
    // Set window user pointer
    glfwSetWindowUserPointer(window, this);

    // Set callbacks
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetCursorEnterCallback(window, cursor_enter_callback);

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, mouse_scroll_callback);

    glfwSetInputMode(window, GLFW_LOCK_KEY_MODS, GLFW_TRUE); // Want to know if caps or num lock is set
    glfwSetKeyCallback(window, key_callback);

    glfwSetWindowSizeCallback(window, window_size_callback);
}

NLUI::Window::~Window() {
    glfwDestroyWindow(window);
}

NLUI::Window * NLUI::Window::createWindow(Logger &logger, const std::string &title, const bool fullscreen, const int width, const int height) {
    // Initialise GLFW
    if(!NLUT::intialiseGLFW(logger)) {
        return nullptr;
    }

    // Get monitor and modes
    GLFWmonitor       *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode    = glfwGetVideoMode(monitor);

    // Create glfwWindow
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(fullscreen ? mode->width : width, fullscreen ? mode->height : height, title.c_str(), fullscreen ? monitor : nullptr, nullptr);

    if(!window) {
        logger.addError("Failed to create GLFWwindow.");
    }

    // Initialise GLEW
    if(!NLUT::initialiseGLEW(logger, window)) {
        glfwDestroyWindow(window);
        return nullptr;
    }

    // Initialise shaders
    if(!Graphics::initialiseShaders(logger)) {
        glfwDestroyWindow(window);
        return nullptr;
    }

    // Return window
    return new Window(window, 0, 0, width, height);
}

NLUI::Window * NLUI::Window::readWindow(Logger &logger, const json &jsonWindow, const std::filesystem::path &dirPath) {
    // Check if it is a path, call proper function if so
    if(jsonWindow.is_string()) {
        return NLUI::Window::readWindow(logger, getPath(dirPath, jsonWindow.get<std::string>()));
    }

    try {
        // Get sub objects
        const json &jsonFullScreen = jsonWindow.at("fullscreen");
        const json &jsonWidth      = jsonWindow.at("width");
        const json &jsonHeight     = jsonWindow.at("height");

        const json &jsonTitle      = jsonWindow.at("title");

        // Check validity
        if(!jsonFullScreen.is_boolean()) {
            return nullptr;
        }

        if(!jsonWidth.is_number_unsigned()) {
            return nullptr;
        }

        if(!jsonHeight.is_number_unsigned()) {
            return nullptr;
        }

        if(!jsonTitle.is_string()) {
            return nullptr;
        }

        // Get size/fullscreen
        const bool         fullscreen = jsonFullScreen.get<bool>();
        const unsigned int width      = jsonWidth.get<unsigned int>();
        const unsigned int height     = jsonHeight.get<unsigned int>();

        // Get title
        const std::string &title = jsonTitle.get<std::string>();

        return createWindow(logger, title, fullscreen, width, height);
        // // Initialise GLFW
        // if(!intialiseGLFW(logger)) {
        //     return nullptr;
        // }

        // // Get monitor and modes
        // GLFWmonitor       *monitor = glfwGetPrimaryMonitor();
        // const GLFWvidmode *mode    = glfwGetVideoMode(monitor);

        // // Create glfwWindow
        // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        // GLFWwindow *window = glfwCreateWindow(fullscreen ? mode->width : width, fullscreen ? mode->height : height, title.c_str(), fullscreen ? monitor : nullptr, nullptr);

        // if(!window) {
        //     logger.addError("Failed to create GLFWwindow.");
        // }

        // // Initialise GLEW
        // if(!initialiseGLEW(logger, window)) {
        //     glfwDestroyWindow(window);
        //     return nullptr;
        // }

        // // Initialise shaders
        // if(!Graphics::initialiseShaders(logger)) {
        //     glfwDestroyWindow(window);
        //     return nullptr;
        // }

        // // Return window
        // return new Window(window, 0, 0, width, height);
    } catch(const json::exception& e) {
        logger.addConversionError(e, jsonWindow, "Failed to load window.");

        return nullptr;
    }
}

NLUI::Window * NLUI::Window::readWindow(Logger &logger, const std::filesystem::path &path) {
    std::ifstream window(path);
    if(!window.is_open()) {
        logger.addFileReadError(path, "Failed to load window.");

        return nullptr;
    }

    try {
        const json jsonWindow = json::parse(window);

        return NLUI::Window::readWindow(logger, jsonWindow, path.parent_path());
    } catch(const json::exception &e) {
        logger.addJsonParseError(e, path, "Failed to load window.");

        return nullptr;
    }
}
 
void NLUI::Window::startDrawing() {
    // Only one context, need to wait our turn
    contextMutex.lock();

    glfwMakeContextCurrent(window);

    // Set opengl options
    glDisable(GL_DEPTH_TEST);

    // Properly size viewport (handles resizing of window and viewport)
    ivec2 frameBufferSize = getFrameBufferSize();
    glViewport(0, 0, frameBufferSize.x, frameBufferSize.y);

    // TODO pass matrices for other shaders too
    // Pass uniforms for all
    mat4 mvp = glm::ortho(0.0f, (float) frameBufferSize.x, 0.0f, (float) frameBufferSize.y, -1.0f, 1.0f);
    Graphics::passSolidMVP(mvp);
}

void NLUI::Window::finishDrawing() {
    glfwSwapBuffers(window);

    // Left others claim the context now that we're done
    contextMutex.unlock();
}

void NLUI::Window::draw() {
    startDrawing();
    clear(); // TODO only do this sometimes

    if(component != nullptr) {
        component->draw();
    }

    finishDrawing();
}

// void NLUI::Window::makeCurrentWindow() {
//     glfwMakeContextCurrent(window);
// }

// void NLUI::Window::swapBuffers() {
//     glfwSwapBuffers(window);
// }

// TODO have clear colour
void NLUI::Window::clear() {
    clear(vec3(0.3f, 0.1f, 0.5f));
}

void NLUI::Window::clear(const vec3 &colour) {
    clear(vec4(colour, 1.0f));
}

void NLUI::Window::clear(const vec4 &colour) {
    glClearColor(colour.r, colour.g, colour.b, colour.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void NLUI::Window::keyPressed(const int key) {
    // Reserved keys: F10

    if(key == GLFW_KEY_F10) {
        if(isFullScreen()) {
            setWindowed();
        } else {
            setFullScreen();
        }
    } else {
        const std::vector<KeyListener *> listenersCopy = keyListeners;
        for(KeyListener *keyListener : listenersCopy) {
            keyListener->keyPressed(key);
        }
    }
}

void NLUI::Window::keyRepeated(const int key) {
    const std::vector<KeyListener *> listenersCopy = keyListeners;
    for(KeyListener *keyListener : listenersCopy) {
        keyListener->keyRepeated(key);
    }
}

void NLUI::Window::keyReleased(const int key) {
    const std::vector<KeyListener *> listenersCopy = keyListeners;
    for(KeyListener *keyListener : listenersCopy) {
        keyListener->keyReleased(key);
    }
}

void NLUI::Window::mouseEntered() {
    glfwGetCursorPos(window, &mouseX, &mouseY);

    mouseInside = true;
}

void NLUI::Window::mouseExited() {
    mouseInside = false;
}

void NLUI::Window::mouseMoved(const double xPos, const double yPos) {
    const float deltaX = xPos - mouseX;
    const float deltaY = yPos - mouseY;

    mouseX = xPos;
    mouseY = yPos;

    const std::vector<MouseMotionListener *> listenersCopy = mouseMotionListeners;
    for(MouseMotionListener *mouseMotionListener : listenersCopy) {
        mouseMotionListener->mouseMoved(xPos, yPos, deltaX, deltaY);
    }
}

void NLUI::Window::mousePressed(const int key) {
    const std::vector<MouseButtonListener *> listenersCopy = mouseButtonListeners;
    for(MouseButtonListener *mouseButtonListener : listenersCopy) {
        mouseButtonListener->mousePressed(key, mouseX, mouseY);
    }
}

void NLUI::Window::mouseRepeated(const int key) {
    const std::vector<MouseButtonListener *> listenersCopy = mouseButtonListeners;
    for(MouseButtonListener *mouseButtonListener : listenersCopy) {
        mouseButtonListener->mouseRepeated(key, mouseX, mouseY);
    }
}

void NLUI::Window::mouseReleased(const int key) {
    const std::vector<MouseButtonListener *> listenersCopy = mouseButtonListeners;
    for(MouseButtonListener *mouseButtonListener : listenersCopy) {
        mouseButtonListener->mouseReleased(key, mouseX, mouseY);
    }
}

void NLUI::Window::mouseScrolled(const double deltaX, const double deltaY) {
    const std::vector<MouseScrollListener *> listenersCopy = mouseScrollListeners;
    for(MouseScrollListener *mouseScrollListener : listenersCopy) {
        mouseScrollListener->mouseScrolled(deltaX, deltaY, mouseX, mouseY);
    }
}

void NLUI::Window::windowResized(const int width, const int height) {
    if(component != nullptr) {
        component->setSize(width, height);
        component->resize();
    }
}

void NLUI::Window::addKeyListener(KeyListener *keyListener) {
    keyListeners.push_back(keyListener);
}

void NLUI::Window::addMouseListener(MouseListener *mouseListener) {
    addMouseButtonListener(mouseListener);
    addMouseMotionListener(mouseListener);
    addMouseScrollListener(mouseListener);
}

void NLUI::Window::addMouseButtonListener(MouseButtonListener *mouseButtonListener) {
    mouseButtonListeners.push_back(mouseButtonListener);
}

void NLUI::Window::addMouseMotionListener(MouseMotionListener *mouseMotionListener) {
    mouseMotionListeners.push_back(mouseMotionListener);
}

void NLUI::Window::addMouseScrollListener(MouseScrollListener *mouseScrollListener) {
    mouseScrollListeners.push_back(mouseScrollListener);
}

void NLUI::Window::setFullScreen() {
    if(isFullScreen()) {
        return;
    }

    // Save size to become windowed again
    glfwGetWindowPos(window, &windowedX, &windowedY);
    glfwGetWindowSize(window, &windowedWidth, &windowedHeight);

    GLFWmonitor       *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode    = glfwGetVideoMode(monitor);

    glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
}

bool NLUI::Window::isFullScreen() const {
    // When fullscreen, the window will have a monitor associated with it
    return glfwGetWindowMonitor(window) != nullptr;
}

void NLUI::Window::setWindowed() {
    if(isWindowed()) {
        return;
    }

    glfwSetWindowMonitor(window, nullptr, windowedX, windowedY, windowedWidth, windowedHeight, GLFW_DONT_CARE);
}

bool NLUI::Window::isWindowed() const {
    // When fullscreen, the window will not have a monitor associated with it
    return glfwGetWindowMonitor(window) == nullptr;
}

void NLUI::Window::resize(const int width, const int height) {
    glfwSetWindowMonitor(window, nullptr, 0, 0, width, height, 0);
}

// TODO remove this maybe?
void NLUI::Window::getSize(int &width, int &height) const {
    glfwGetWindowSize(window, &width, &height);
}

ivec2 NLUI::Window::getSize() const {
    ivec2 size;

    glfwGetWindowSize(window, &size.x, &size.y);

    return size;
}

int NLUI::Window::getWidth() const {
    int width;

    glfwGetWindowSize(window, &width, nullptr);

    return width;
}

int NLUI::Window::getHeight() const {
    int height;

    glfwGetWindowSize(window, nullptr, &height);

    return height;
}

void NLUI::Window::getFrameBufferSize(int &width, int &height) const {
    glfwGetFramebufferSize(window, &width, &height);
}
    
ivec2 NLUI::Window::getFrameBufferSize() const {
    ivec2 frameBufferSize;

    glfwGetFramebufferSize(window, &frameBufferSize.x, &frameBufferSize.y);

    return frameBufferSize;
}

int NLUI::Window::getFrameBufferWidth() const {
    int width;

    glfwGetFramebufferSize(window, &width, nullptr);

    return width;
}
    
int NLUI::Window::getFrameBufferHeight() const {
    int height;

    glfwGetFramebufferSize(window, nullptr, &height);

    return height;
}

bool NLUI::Window::shouldClose() const {
    return glfwWindowShouldClose(window);
}

// TODO should this delete the current content or not?
void NLUI::Window::setComponent(Component *component) {
    if(this->component != nullptr) {
        this->component->removeParent();
    }

    if(component == nullptr) {
        this->component = component;
        return;
    }

    component->setParent(this);
    this->component = component;

    // TODO handle minimum sizes
    const ivec2 minimumSize = component->getMinimumSize();
    glfwSetWindowSizeLimits(window, minimumSize.x, minimumSize.y, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetWindowSize(window, minimumSize.x, minimumSize.y);

    component->setPos(0, 0);
    component->setSize(this->getFrameBufferSize());
    component->resize();
}

void NLUI::Window::removeComponent(Component *component) {
    if(component != nullptr && this->component == component) {
        this->component = nullptr;
        component->removeParent();
    }
}

void NLUI::Window::validate() {
    if(component != nullptr) {
        const ivec2 minimumSize = component->getMinimumSize();

        // Ensure the component can fit in the space provided
        glfwSetWindowSizeLimits(window, minimumSize.x, minimumSize.y, GLFW_DONT_CARE, GLFW_DONT_CARE);

        // Call Give it the space it has and call resize
        component->setSize(getFrameBufferSize());
        component->resize();
    }
}

bool intialiseGLFW(Logger &logger) {
    static bool initialised = false;

    if(initialised) {
        return true;
    }

    if(!glfwInit()) {
        logger.addError("Failed to initialise GLFW.");

        return false;
    } else {
        return true;
    }
}

bool initialiseGLEW(Logger &logger, GLFWwindow *window) {
    static bool initialised = false;

    if(initialised) {
        return true;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        logger.addError("Failed to initialise GLEW.");

        return false;
    } else {
        return true;
    }
}

// TODO implement
void cursor_pos_callback(GLFWwindow *window, const double xpos, const double ypos) {
   NLUI:: Window *w = (NLUI::Window *) glfwGetWindowUserPointer(window);

    w->mouseMoved(xpos, ypos);
}

void cursor_enter_callback(GLFWwindow *window, const int entered) {
    NLUI::Window *w = (NLUI::Window *) glfwGetWindowUserPointer(window);

    if(entered) {
        w->mouseEntered();
    } else {
        w->mouseExited();
    }
}

void mouse_button_callback(GLFWwindow *window, const int button, const int action, const int mods) {
   NLUI:: Window *w = (NLUI::Window *) glfwGetWindowUserPointer(window);

    // TODO consider sending mods too
    if(action == GLFW_PRESS) {
        w->mousePressed(button);
    } else if(action == GLFW_REPEAT) {
        w->mouseRepeated(button);
    } else if(action == GLFW_RELEASE) {
        w->mouseReleased(button);
    }
}

void mouse_scroll_callback(GLFWwindow *window, const double xOffset, const double yOffset) {
    NLUI::Window *w = (NLUI::Window *) glfwGetWindowUserPointer(window);

    w->mouseScrolled(xOffset, yOffset);
}

void key_callback(GLFWwindow *window, const int key, const int scancode, const int action, const int mods) {
    NLUI::Window *w = (NLUI::Window *) glfwGetWindowUserPointer(window);

    // TODO consider sending mods too
    if(action == GLFW_PRESS) {
        w->keyPressed(key);
    } else if(action == GLFW_REPEAT) {
        w->keyRepeated(key);
    } else if(action == GLFW_RELEASE) {
        w->keyReleased(key);
    }
}

void window_size_callback(GLFWwindow* window, int width, int height) {
    NLUI::Window *w = (NLUI::Window *) glfwGetWindowUserPointer(window);

    w->windowResized(width, height);
}