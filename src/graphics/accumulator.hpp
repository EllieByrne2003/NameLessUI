#pragma once

// Includes from standard
#include <vector>

// Includes from third party libraries
#include <glm/glm.hpp>
using namespace glm;

// Includes from personal libraries


// Includes from project
#include "vertices.hpp"

// Forward declarations


// Type aliases
typedef unsigned int GLuint;

namespace NLUI {
    namespace Graphics {
        class Accumulator final {
        private:
            std::vector<SolidVertex> solidVertices;
            GLuint solidVAO;
            GLuint solidVBO;

            std::vector<ImageVertex> imageVertices;

        protected:

        public:
            Accumulator();
            ~Accumulator();

            // Solid colour primitives
            void addSolidQuad(const vec4 &colour, const vec2 &v1, const vec2 &v2, const vec2 &v3, const vec2 &v4);
            void addSolidQuad(const vec4 &colour, const vec2 &pos, const vec2 &size);

            void addSolidTri(const vec4 &colour, const vec2 &v1, const vec2 &v2, const vec2 &v3);

            // Image primitives
            // TODO implement these

            // Text primitives
            // TODO implement these

            // Process accumulated vertices
            void draw(const int width, const int height);
            void clear();
        };
    };
};