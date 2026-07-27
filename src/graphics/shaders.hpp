#pragma once

// Includes from standard


// Includes from third party libraries
#include <glm/glm.hpp>
using namespace glm;

// Includes from personal libraries
#include <NLUT/logger/logger.hpp>

// Includes from project


// Forward declarations


// Type aliases


namespace NLUI {
    namespace Graphics {
        bool initialiseShaders(NLUT::Logger &logger);
        bool shadersInitialised();

        bool initialiseSolidShader(NLUT::Logger &logger);
        bool solidShaderInitialised();

        // TODO add other shaders

        // TODO can remove or just make in cpp file only
        // void bindSolidShader(); 
        // void bindImageShader();
        // void bindTextShader();

        // Passing uniforms
        void passSolidMVP(const mat4 &mvp); // TODO Don't like this

        // Quadrilateral rendering
        void drawSolidQuad(const vec4 &colour, const vec2 &v1, const vec2 &v2, const vec2 &v3, const vec2 &v4);
        void drawSolidQuad(const vec4 &colour, const vec2 &pos, const vec2 &size);

        // void drawSolidQuads();

        // Triangle rendering
        void addSolidTri(const vec4 &colour, const vec2 &v1, const vec2 &v2, const vec2 &v3);

        // void drawSolidTris();



        // TODO add textured stuff
    };
};