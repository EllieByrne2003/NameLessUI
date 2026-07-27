#include "shaders.hpp"

// Includes from standard


// Includes from third party libraries
#include <GL/glew.h>
#include <GL/gl.h>

// Includes from personal libraries
#include <NLUT/logger/logger.hpp>
#include <NLUT/files/shaders.hpp>

// Includes from project


// Forward declarations


// Type aliases


bool NLUI::Graphics::initialiseShaders(NLUT::Logger &logger) {
    if(!initialiseSolidShader(logger)) {
        logger.addError("Failed to initialise solid shader or location.");
        return false;
    }

    return true;
}

bool NLUI::Graphics::shadersInitialised() {
    if(!solidShaderInitialised()) {
        return false;
    }

    return true;
}
    
