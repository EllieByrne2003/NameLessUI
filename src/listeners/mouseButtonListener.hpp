#pragma once

// Includes from standard


// Includes from third party libraries


// Includes from personal libraries


// Includes from projectl libraries


// Includes from project


// Forward declarations


// Type aliases


namespace NLUI {
    class MouseButtonListener {
    private:

    protected:

    public:
        virtual ~MouseButtonListener() = 0;

        virtual void mousePressed(const int key, const double xPos, const double yPos) = 0;
        virtual void mouseRepeated(const int key, const double xPos, const double yPos) = 0;
        virtual void mouseReleased(const int key, const double xPos, const double yPos) = 0;
    };
};