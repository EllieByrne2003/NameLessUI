#pragma once

// Includes from standard


// Includes from third party libraries
#include <glm/glm.hpp>

// Includes from personal libraries


// Includes from project


// Forward declarations


// Type aliases


namespace NLUI {
    namespace Graphics {
        struct SolidVertex {
            glm::vec2 pos;
            glm::vec4 colour;
        };

        struct ImageVertex {
            glm::vec2 pos;
            glm::vec2 uv;
        };

        // TODO add one for text
    };
};