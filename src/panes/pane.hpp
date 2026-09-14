#pragma once

// Includes from standard
#include <memory>

// Includes from third party libraries


// Includes from personal libraries


// Includes from project
#include "../component/baseComponent.hpp"
#include "../container/container.hpp"

// Forward declarations


// Type aliases


namespace NLUI {
    class Pane : public BaseComponent, public Container {
    private:

    protected:
        std::shared_ptr<Component> hoverFocus = nullptr;
        std::shared_ptr<Component> clickFocus = nullptr;

    public:

    /*----------  Functions  ----------*/
    private:

    protected:
        Pane(const glm::ivec2 &minSize, const glm::ivec2 &maxSize);

    public:
        virtual ~Pane() = 0;

        // Overridden from Component and Container
        virtual void layoutRoot() override final;

        // Overridden from Component
        virtual void onResize() override;

        // Key events handling
        virtual void processKeyPress(const int key) final;
        virtual void processKeyRepeat(const int key) final;
        virtual void processKeyRelease(const int key) final;

        // Mouse button events handling
        virtual void processMouseRepeat(const int key, const double xPos, const double yPos) final;
        virtual void processMouseRelease(const int key, const double xPos, const double yPos) final;
        
        // Mouse motion events handling
        virtual void processMouseEnter() final;
        virtual void processMouseExit() final;
        
        // Mouse scroll events handling
        virtual void processMouseScroll(const double deltaX, const double deltaY) override;

        // Override from Container
    };
};