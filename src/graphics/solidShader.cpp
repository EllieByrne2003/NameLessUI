#include "shaders.hpp"

// Includes from standard
#include <mutex>

// Includes from third party libraries
#include <GL/glew.h>
#include <GL/gl.h>

// Includes from personal libraries
#include <NLUT/logger/logger.hpp>
#include <NLUT/files/shaders.hpp>
#include <NLUT/gl/glew.hpp>

// Includes from project
#include "vertices.hpp"

// Forward declarations


// Type aliases


static const char *const vertexCode = R"(
    #version 330

    layout(location = 0) in vec2 aPos;
    layout(location = 1) in vec4 aColour;

    uniform mat4 mvp;

    out vec4 colour;

    void main() {
        colour = aColour;
        gl_Position = mvp * vec4(aPos, 0.0, 1.0);
    }
)";

static const char *const fragmentCode = R"(
    #version 330

    in  vec4 colour;
    out vec4 color;

    void main() {
        color = colour;
    }
)";

static GLuint programID;
static GLuint VAO;
static GLuint VBO;

static GLint mvpLoc;

static bool initialised = false;

bool NLUI::Graphics::initialiseSolidShader(NLUT::Logger &logger) {
    static std::mutex initMutex;
    std::unique_lock intiLock(initMutex);

    if(initialised) {
        return true;
    }

    if(!NLUT::GLEWInitialised()) {
        logger.addError("GLEW was never initialised. Cannot intialise solid shader.");
    } else {
        programID = NLUT::createShader(vertexCode, fragmentCode);
        if(programID == 0) {
            logger.addError("Failed to create solid shader.");
            return false;
        }

        mvpLoc = NLUT::getLoc(programID, "mvp");

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(SolidVertex), (void *)offsetof(SolidVertex, pos));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(SolidVertex), (void *)offsetof(SolidVertex, colour));
        glEnableVertexAttribArray(1);

        initialised = true;
    }

    return initialised;
}

bool NLUI::Graphics::solidShaderInitialised() {
    return initialised;
}

void NLUI::Graphics::passSolidMVP(const mat4 &mvp) {
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &mvp[0][0]);
}

void NLUI::Graphics::drawSolidQuad(const vec4 &colour, const vec2 &v1, const vec2 &v2, const vec2 &v3, const vec2 &v4) {
    glUseProgram(programID);

    // Make array and fill it
    SolidVertex vertices[6]; // Space for two triangles

    vertices[0] = SolidVertex{ v1, colour };
    vertices[1] = SolidVertex{ v2, colour };
    vertices[2] = SolidVertex{ v3, colour };
    vertices[3] = SolidVertex{ v1, colour };
    vertices[4] = SolidVertex{ v3, colour };
    vertices[5] = SolidVertex{ v4, colour };

    // Send array to gpu
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
        
void NLUI::Graphics::drawSolidQuad(const vec4 &colour, const vec2 &pos, const vec2 &size) {
    glUseProgram(programID);

    const vec2 v1 = vec2(pos.x,          pos.y);
    const vec2 v2 = vec2(pos.x + size.x, pos.y);
    const vec2 v3 = vec2(pos.x + size.x, pos.y + size.y);
    const vec2 v4 = vec2(pos.x,          pos.y + size.y);

    drawSolidQuad(colour, v1, v2, v3, v4);
}

void NLUI::Graphics::addSolidTri(const vec4 &colour, const vec2 &v1, const vec2 &v2, const vec2 &v3) {
    glUseProgram(programID);

    // Make array and fill it
    SolidVertex vertices[3]; // Space for two triangles

    vertices[0] = SolidVertex{ v1, colour };
    vertices[1] = SolidVertex{ v2, colour };
    vertices[2] = SolidVertex{ v3, colour };

    // Send array to gpu
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 3);
}