#include "accumulator.hpp"

// Includes from standard


// Includes from third party libraries
#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/gtc/matrix_transform.hpp>

// Includes from personal libraries


// Includes from project
#include "shaders.hpp"

// Forward declarations


// Type aliases



NLUI::Graphics::Accumulator::Accumulator() {
    // TODO move this elsewhere, should have fails allowed 

    glGenVertexArrays(1, &solidVAO);
    glGenBuffers(1, &solidVBO);

    glBindVertexArray(solidVAO);

    glBindBuffer(GL_ARRAY_BUFFER, solidVBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SolidVertex), (void *)offsetof(SolidVertex, pos));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SolidVertex), (void *)offsetof(SolidVertex, colour));
    glEnableVertexAttribArray(1);
}

NLUI::Graphics::Accumulator::~Accumulator() {

}

void NLUI::Graphics::Accumulator::addSolidQuad(const vec4 &colour, const vec2 &v1, const vec2 &v2, const vec2 &v3, const vec2 &v4) {
    addSolidTri(colour, v1, v2, v3);
    addSolidTri(colour, v1, v3, v4);
}

void NLUI::Graphics::Accumulator::addSolidQuad(const vec4 &colour, const vec2 &pos, const vec2 &size) {
    const vec2 v1 = vec2(pos.x,          pos.y);
    const vec2 v2 = vec2(pos.x + size.x, pos.y);
    const vec2 v3 = vec2(pos.x + size.x, pos.y + size.y);
    const vec2 v4 = vec2(pos.x,          pos.y + size.y);

    addSolidTri(colour, v1, v2, v3);
    addSolidTri(colour, v1, v3, v4);
}

void NLUI::Graphics::Accumulator::addSolidTri(const vec4 &colour, const vec2 &v1, const vec2 &v2, const vec2 &v3) {
    solidVertices.push_back(SolidVertex { v1, colour });
    solidVertices.push_back(SolidVertex { v2, colour });
    solidVertices.push_back(SolidVertex { v3, colour });
}

void NLUI::Graphics::Accumulator::draw(const int width, const int height) {
    // TODO implement

    // Bind program for solid
    bindSolidShader();
    glBindVertexArray(solidVAO);

    // Send matrix
    // TODO get matrix and loc
    const mat4 proj = glm::ortho(
         0.0f, (float) width,
         0.0f, (float) height,
        -2.0f, 1.0f
    );

    const mat4 view  = mat4(1.0f);
    const mat4 model = mat4(1.0f);
    const mat4 mvp = proj * view * model;
    passSolidMVP(mvp);

    glBindBuffer(GL_ARRAY_BUFFER, solidVBO);
    glBufferData(GL_ARRAY_BUFFER, solidVertices.size() * sizeof(SolidVertex), solidVertices.data(), GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, solidVertices.size());


    // TODO implement for other types
}

void NLUI::Graphics::Accumulator::clear() {
    solidVertices.clear();
    imageVertices.clear();
}