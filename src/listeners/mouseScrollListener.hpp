#pragma once

// Includes from standard


// Includes from third party libraries


// Includes from personal libraries


// Includes from project


// Forward declarations


// Type aliases


namespace NLUI {
    class MouseScrollListener {
    private:

    protected:

    public:
        virtual ~MouseScrollListener() = 0;

        virtual void mouseScrolled(const double deltaX, const double deltaY, const double xPos, const double yPos) = 0;
    };
};