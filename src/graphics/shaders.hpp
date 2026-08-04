#pragma once

// Includes from standard


// Includes from third party libraries
#include <glm/glm.hpp>

// Includes from personal libraries
#include <NLUT/logger/logger.hpp>

// Includes from project


// Forward declarations


// Type aliases
typedef unsigned int GLuint;
typedef int GLint;

// TODO sizes should all be uvec2 types

namespace NLUI {
    namespace Graphics {
        bool initialiseShaders(NLUT::Logger &logger);
        bool shadersInitialised();

        bool initialiseSolidShader(NLUT::Logger &logger);
        bool solidShaderInitialised();

        bool initialiseTextureShader(NLUT::Logger &logger);
        bool textureShaderInitialised();

        // TODO add other shaders

        // TODO can remove or just make in cpp file only
        // void bindSolidShader(); 
        // void bindImageShader();
        // void bindTextShader();

        // Passing uniforms
        void passSolidMVP(const glm::mat4 &mvp); // TODO Don't like this
        void passTextureMVP(const glm::mat4 &mvp); // TODO or this

        // Quadrilateral rendering
        void drawSolidQuad(const glm::vec4 &colour, const glm::vec2 &v1, const glm::vec2 &v2, const glm::vec2 &v3, const glm::vec2 &v4);
        void drawSolidQuad(const glm::vec4 &colour, const glm::vec2 &pos, const glm::vec2 &size);

        // TODO need versions to have separate UVs
        void drawTextureQuad(const GLuint textureID, const glm::vec2 &v1, const glm::vec2 &v2, const glm::vec2 &v3, const glm::vec2 &v4);
        void drawTextureQuad(const GLuint textureID, const glm::vec2 &pos, const glm::uvec2 &size);

        // void drawSolidQuads();

        // Triangle rendering
        void addSolidTri(const glm::vec4 &colour, const glm::vec2 &v1, const glm::vec2 &v2, const glm::vec2 &v3);

        void drawTextureTri(const GLuint textureID, const glm::vec2 &v1, const glm::vec2 &v2, const glm::vec2 &v3);

        // void drawSolidTris();



        // TODO add textured stuff

        
    };
};