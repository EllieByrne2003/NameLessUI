#pragma once

// Includes from standard


// Includes from third party libraries


// Includes from personal libraries


// Includes from project


// Forward declarations


// Type aliases


namespace NLUI {
    class MouseMotionListener {
    private:

    protected:

    public:
        virtual ~MouseMotionListener() = 0;

        virtual void mouseMoved(const double xPos, const double yPos, const double deltaX, const double deltaY) = 0;
    };
};