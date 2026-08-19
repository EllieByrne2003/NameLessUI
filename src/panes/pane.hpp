#pragma once

// Includes from standard
#include <memory>

// Includes from third party libraries


// Includes from personal libraries


// Includes from project
#include "../component/component.hpp"
#include "../container/container.hpp"

// Forward declarations


// Type aliases


namespace NLUI {
    class Pane : public Component, public Container {
    private:

    protected:
        std::shared_ptr<Component> focus = nullptr;

    public:

    /*----------  Functions  ----------*/
    private:

    protected:
        Pane(const glm::ivec2 &minSize, const glm::ivec2 &maxSize);

    public:
        virtual ~Pane() = 0;

        // Overridden from Component
        virtual void onResize() override;

        // Override from Container
    };
};