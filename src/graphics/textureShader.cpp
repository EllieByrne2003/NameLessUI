#include "shaders.hpp"

// Includes from standard
#include <mutex>

// Includes from third party libraries
#include <glm/glm.hpp>
using namespace glm;

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
    layout(location = 1) in vec2 aUv;

    uniform mat4 mvp;

    out vec2 uv;

    void main() {
        uv = aUv;
        gl_Position = mvp * vec4(aPos, 0.0, 1.0);
    }
)";

static const char *const fragmentCode = R"(
    #version 330

    in vec2 uv;
    
    uniform sampler2D textureMap;
    
    out vec4 color;

    void main() {
        color = texture(textureMap, uv);
        // color = vec4(1.0, 0.0, 0.0, 0.0);
    }
)";

static GLuint programID;
static GLuint VAO;
static GLuint VBO;

static GLint mvpLoc;
static GLint textureLoc;

static bool initialised = false;

void bindTexture(const GLuint textureID);

bool NLUI::Graphics::initialiseTextureShader(NLUT::Logger &logger) {
    static std::mutex initMutex;
    std::unique_lock initLock(initMutex);

    if(initialised) {
        return true;
    }

    if(!NLUT::GLEWInitialised()) {
        logger.addError("GLEW was never initialised. Cannot intialise texture shader.");
    } else {
        programID = NLUT::createShader(vertexCode, fragmentCode);
        if(programID == 0) {
            logger.addError("Failed to create texture shader.");
            return false;
        }

        // TODO add check to verify success
        mvpLoc     = NLUT::getLoc(programID, "mvp");
        textureLoc = NLUT::getLoc(programID, "textureMap");

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(ImageVertex), (void *)offsetof(ImageVertex, pos));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ImageVertex), (void *)offsetof(ImageVertex, uv));
        glEnableVertexAttribArray(1);

        initialised = true;
    }

    return initialised;
}

bool NLUI::Graphics::textureShaderInitialised() {
    return initialised;
}

void NLUI::Graphics::passTextureMVP(const glm::mat4 &mvp) {
    glUseProgram(programID);
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &mvp[0][0]);
}

// TODO when writing docs or proper function, mention that v1 is taken as bottom left, v2 is bottom right, v3 is top right and v4 is top left
void NLUI::Graphics::drawTextureQuad(const GLuint textureID, const glm::vec2 &v1, const glm::vec2 &v2, const glm::vec2 &v3, const glm::vec2 &v4) {
    glUseProgram(programID);

    // Make array and fill it
    ImageVertex vertices[6]; // Space for two triangles

    vertices[0] = ImageVertex{ v1, vec2(0.0, 0.0) };
    vertices[1] = ImageVertex{ v2, vec2(1.0, 0.0) };
    vertices[2] = ImageVertex{ v3, vec2(1.0, 1.0) };
    vertices[3] = ImageVertex{ v1, vec2(0.0, 0.0) };
    vertices[4] = ImageVertex{ v3, vec2(1.0, 1.0) };
    vertices[5] = ImageVertex{ v4, vec2(0.0, 1.0) };

    // Send array to gpu
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

    // Bind texture
    bindTexture(textureID);

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void NLUI::Graphics::drawTextureQuad(const GLuint textureID, const glm::vec2 &pos, const glm::uvec2 &size) {
    glUseProgram(programID);

    const vec2 v1 = vec2(pos.x,          pos.y);
    const vec2 v2 = vec2(pos.x + size.x, pos.y);
    const vec2 v3 = vec2(pos.x + size.x, pos.y + size.y);
    const vec2 v4 = vec2(pos.x,          pos.y + size.y);

    drawTextureQuad(textureID, v1, v2, v3, v4);
}

void NLUI::Graphics::drawTextureTri(const GLuint textureID, const glm::vec2 &v1, const glm::vec2 &v2, const glm::vec2 &v3) {
    glUseProgram(programID);

    // Make array and fill it
    ImageVertex vertices[3]; // Space for two triangles

    vertices[0] = ImageVertex{ v1, vec2(0.0, 0.0) };
    vertices[1] = ImageVertex{ v2, vec2(1.0, 0.0) };
    vertices[2] = ImageVertex{ v3, vec2(1.0, 1.0) };

    // Send array to gpu
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

    // Bind texture
    bindTexture(textureID);

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void bindTexture(const GLuint textureID) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glUniform1i(textureLoc, 0);
}