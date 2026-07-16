#pragma once

// Includes from standard


// Includes from third party libraries


// Includes from personal libraries


// Includes from project
#include "../component/component.hpp"

#include "../listeners/mouseButtonListener.hpp";

// Forward declarations


// Type aliases


namespace NLUI {
    class Button : public Component, public MouseButtonListener {
    private:

    protected:

    public:
        Button();
        ~Button();

        void mousePressed(const int key, const double xPos, const double yPos);
        void mouseRepeated(const int key, const double xPos, const double yPos);
        void mouseReleased(const int key, const double xPos, const double yPos);
    };
};