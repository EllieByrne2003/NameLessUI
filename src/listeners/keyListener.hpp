#pragma once

// Includes from standard


// Includes from third party libraries


// Includes from personal libraries


// Includes from projectl libraries


// Includes from project


// Forward declarations


// Type aliases


namespace NLUI {
    class KeyListener {
    private:

    protected:

    public:
        virtual ~KeyListener() = 0;

        virtual void keyPressed(const int key) = 0;
        virtual void keyRepeated(const int key) = 0;
        virtual void keyReleased(const int key) = 0;
    };
};