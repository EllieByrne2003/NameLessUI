#pragma once

// Includes from standard
#include <memory>

// Includes from third party libraries
#include <glm/glm.hpp>

// Includes from personal libraries


// Includes from project


// Forward declarations
namespace NLUI { class Component; };

// Type aliases


namespace NLUI {
    class Container {
    private:

    protected:

    public:

    /*----------  Functions  ----------*/
    private:

    protected:

    public:
        virtual ~Container() = 0;

        // Handle removal
        virtual void removeComponent(const std::shared_ptr<Component> &component) = 0;
        virtual void removeComponent(Component *const component) = 0;

        // // Handle children changing size
        // virtual void validate() = 0;


        // Layout components and get sizes
        virtual void doLayout() = 0;
        // virtual glm::ivec2 simulateLayout() const = 0; // TODO this is to get the size // TODO maybe make ones to return answer in different format
    };
};