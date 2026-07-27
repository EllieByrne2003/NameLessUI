#pragma once

// Includes from standard
#include <filesystem>
#include <vector>

// Includes from third party libraries
#include <glm/glm.hpp>
using namespace glm;

#include <nlohmann/json.hpp>
using json = nlohmann::json;

// Includes from personal libraries
#include <NLUT/logger/logger.hpp>
using Logger = NLUT::Logger;

// Includes from project
#include "../listeners/keyListener.hpp"
#include "../listeners/mouseListener.hpp"
#include "../listeners/mouseButtonListener.hpp"
#include "../listeners/mouseMotionListener.hpp"
#include "../listeners/mouseScrollListener.hpp"

#include "../component/component.hpp"
#include "../container/container.hpp"

// Forward declarations
struct GLFWwindow;

// Type aliases

// Mostly a wrapper for glfw
namespace NLUI {
    class Window final : public Container {
    private:
        GLFWwindow *const window;

        // Info needed to switch from fullscreen to windowed
        int windowedX;
        int windowedY;
        int windowedWidth;
        int windowedHeight;

        bool mouseInside = false;
        double mouseX, mouseY;

        // Event listeners
        std::vector<KeyListener *>         keyListeners;
        std::vector<MouseButtonListener *> mouseButtonListeners;
        std::vector<MouseMotionListener *> mouseMotionListeners;
        std::vector<MouseScrollListener *> mouseScrollListeners;

        // Given component
        Component *component = nullptr;

    protected:

    public:
        // TODO make this private
        Window(GLFWwindow *const window, const int windowedX, const int windowedY, const int windowedWidth, const int windowedHeight);
        ~Window();

        // TODO add one to not need json
        static Window * createWindow(Logger &logger, const std::string &title, const bool fullscreen, const int width, const int height);
        static Window * readWindow(Logger &logger, const json &jsonWindow, const std::filesystem::path &dirPath);
        static Window * readWindow(Logger &logger, const std::filesystem::path &path);

        // Needed for drawing // TODO move these two into private?
        void startDrawing();
        void finishDrawing();

        void draw();

        // void makeCurrentWindow();
        // void swapBuffers();

        void clear();
        void clear(const vec3 &colour);
        void clear(const vec4 &colour);

        // Input handling
        void keyPressed(const int key);
        void keyRepeated(const int key);
        void keyReleased(const int key);

        void mouseEntered();
        void mouseExited();

        void mouseMoved(const double xPos, const double yPos);
        void mousePressed(const int key);
        void mouseRepeated(const int key);
        void mouseReleased(const int key);
        void mouseScrolled(const double deltaX, const double deltaY);

        // Event listener handling 
        // TODO Add methods to remove them
        void addKeyListener(KeyListener *keyListener);

        void addMouseListener(MouseListener *mouseListener);
        void addMouseButtonListener(MouseButtonListener *mouseButtonListener);
        void addMouseMotionListener(MouseMotionListener *mouseMotionListener);
        void addMouseScrollListener(MouseScrollListener *mouseScrollListener);

        // Handling window size
        void setFullScreen();
        bool isFullScreen() const;
        void setWindowed();
        bool isWindowed() const;

        void  resize(const int width, const int height);
        void  getSize(int &width, int &height) const;
        ivec2 getSize() const;

        int getWidth() const;
        int getHeight() const;

        void  getFrameBufferSize(int &width, int &height) const;
        ivec2 getFrameBufferSize() const;

        int getFrameBufferWidth() const;
        int getFrameBufferHeight() const;

        // Handle closure
        bool shouldClose() const;

        // Setting component
        void setComponent(Component *component);

        // Override from Container
        virtual void removeComponent(Component *component) override;
    };
};