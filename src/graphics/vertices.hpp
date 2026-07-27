#pragma once

// Includes from standard


// Includes from third party libraries
#include <glm/glm.hpp>
using namespace glm;

// Includes from personal libraries


// Includes from project


// Forward declarations


// Type aliases


namespace NLUI {
    namespace Graphics {
        struct SolidVertex {
            vec2 pos;
            vec4 colour;
        };

        struct ImageVertex {
            vec2 pos;
            vec2 uv;
        };

        // TODO add one for text
    };
};