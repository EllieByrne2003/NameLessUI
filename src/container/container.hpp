#pragma once

// Includes from standard


// Includes from third party libraries


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
        virtual ~Container() = 0;

        virtual void removeComponent(Component *component) = 0;
    };
};