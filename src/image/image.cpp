#include "image.hpp"

// Includes from standard

// Includes from third party libraries


// Includes from personal libraries
#include <NLUT/files/textures.hpp>

// Includes from project
#include "../graphics/shaders.hpp"

// Forward declarations


// Type aliases



NLUI::Image::Image(const GLuint imageID, const glm::uvec2 &imageSize, const unsigned int magLimit, const unsigned int minLimit, const bool keepRatio) : Component(imageSize / minLimit, imageSize * magLimit),
    imageID(imageID), imageSize(imageSize), magLimit(magLimit), minLimit(minLimit), keepRatio(keepRatio) {

}

NLUI::Image::~Image() {
    // TODO delete image
}

std::shared_ptr<NLUI::Image> NLUI::Image::create(const std::filesystem::path &path, const unsigned int magLimit, const unsigned int minLimit, const bool keepRatio) {
    int width, height, nChannels;
    GLuint imageID = NLUT::loadTexture2D(path, width, height, nChannels); // TODO want this to accept nullptr to ignore (or just lack nChannels)

    // TODO could have some kinda fallback? Like CSGOs pink and black?
    // Image generation failed
    if(imageID == 0) {
        return nullptr;
    }

    // TODO check if this is all I need
    glBindTexture(GL_TEXTURE_2D, imageID);
    glGenerateMipmap(GL_TEXTURE_2D);

    // TODO check what are the best opetions for 2D images
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return std::shared_ptr<Image>(new Image(imageID, uvec2(width, height), magLimit, minLimit, keepRatio));
}

void NLUI::Image::draw() const {
    // TODO add a check for transparency (use nChannels from above)
    Component::draw(); // Image might have transparency, so draw background colour

    Graphics::drawTextureQuad(imageID, pos, size);
}

void NLUI::Image::getPrefSize(int &prefWidth, int &prefHeight) const {
    prefWidth  = imageSize.x;
    prefHeight = imageSize.y; 
}

glm::ivec2 NLUI::Image::getPrefSize() const {
    return imageSize;
}

int NLUI::Image::getPrefWidth() const {
    return imageSize.x;
}

int NLUI::Image::getPrefHeight() const {
    return imageSize.y;
}

// TODO maybe give an empty one in component.cpp and remove this?
void NLUI::Image::onResize() {

}