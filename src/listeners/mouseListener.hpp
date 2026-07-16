#pragma once

// Includes from standard


// Includes from third party libraries


// Includes from personal libraries


// Includes from project
#include "mouseButtonListener.hpp"
#include "mouseMotionListener.hpp"
#include "mouseScrollListener.hpp"

// Forward declarations


// Type aliases


namespace NLUI {
    class MouseListener : public MouseButtonListener, public MouseMotionListener, public MouseScrollListener {
    private:

    protected:

    public:
        virtual ~MouseListener() = 0;
    };
};