#include "component.hpp"

// Includes from standard


// Includes from third party libraries
#include <glm/glm.hpp>
using namespace glm;

// Includes from personal libraries


// Includes from project
#include "../container/container.hpp"
#include "../graphics/shaders.hpp"

// Forward declarations


// Type aliases



NLUI::Component::Component(const glm::ivec2 &minSize, const glm::ivec2 &maxSize) :
    minSize(minSize), maxSize(maxSize) {

}

NLUI::Component::~Component() {

}

void NLUI::Component::setParent(Container *parent) {
    removeParent();

    this->parent = parent;
}

void NLUI::Component::removeParent() {
    Container *const oldParent = this->parent;
    this->parent = nullptr;    
    
    if(oldParent) {
        oldParent->removeComponent(this);
    }
}

void NLUI::Component::validateParent() {
    if(parent != nullptr) {
        parent->doLayout();
    }
}

void NLUI::Component::draw() const {
    // TODO implement, accumulate the vertices
    Graphics::drawSolidQuad(backgroundColour, pos, size);
}

void NLUI::Component::setSize(const int width, const int height) {
    size.x = width;
    size.y = height;

    onResize();
}

void NLUI::Component::setSize(const glm::ivec2 &size) {
    this->size = size;

    onResize();
}

void NLUI::Component::setWidth(const int width) {
    size.x = width;

    onResize();
}

void NLUI::Component::setHeight(const int height) {
    size.y = height;

    onResize();
}

void NLUI::Component::proposeSize(const int propWidth, const int propHeight) {
    const glm::ivec2 propSize = ivec2(propWidth, propHeight);

    const glm::ivec2 prefSize = getPrefSize();
    const glm::ivec2 minSize  = getMinSize();
    const glm::ivec2 maxSize  = getMaxSize();

    size = glm::min(prefSize, glm::min(maxSize, max(minSize, propSize)));

    onResize();
}

void NLUI::Component::proposeSize(const glm::ivec2 &propSize) {
    const glm::ivec2 prefSize = getPrefSize();
    const glm::ivec2 minSize  = getMinSize();
    const glm::ivec2 maxSize  = getMaxSize();

    size = glm::min(prefSize, glm::min(maxSize, glm::max(minSize, propSize)));

    onResize();
}

void NLUI::Component::proposeWidth(const int propWidth) {
    const int prefWidth = getPrefWidth();
    const int minWidth  = getMinWidth();
    const int maxWidth  = getMaxWidth();

    size.x = std::min(prefWidth, std::min(maxWidth, std::max(minWidth, propWidth)));

    onResize();
}

void NLUI::Component::proposeHeight(const int propHeight) {
    const int prefHeight = getPrefHeight();
    const int minHeight  = getMinHeight();
    const int maxHeight  = getMaxHeight();

    size.y = std::min(prefHeight, std::min(maxHeight, std::max(minHeight, propHeight)));

    onResize();
}

void NLUI::Component::shrinkSize(const int decWidth, const int decHeight) {
    size.x -= decWidth;
    size.y -= decHeight;

    onResize();
}

void NLUI::Component::shrinkSize(const glm::ivec2 &decSize) {
    size -= decSize;

    onResize();
}

void NLUI::Component::shrinkWidth(const int decWidth) {
    size.x -= decWidth;

    onResize();
}

void NLUI::Component::shrinkHeight(const int decHeight) {
    size.y -= decHeight;

    onResize();
}

void NLUI::Component::growSize(const int incWidth, const int incHeight) {
    const glm::ivec2 propSize = size + ivec2(incWidth, incHeight);
    const glm::ivec2 maxSize  = getMaxSize();

    size = glm::min(propSize, maxSize);

    onResize();
}

void NLUI::Component::growSize(const glm::ivec2 &incSize) {
    const glm::ivec2 propSize = size + incSize;
    const glm::ivec2 maxSize  = getMaxSize();

    size = glm::min(propSize, maxSize);

    onResize();
}

void NLUI::Component::growWidth(const int incWidth) {
    const int propWidth = size.x + incWidth;
    const int maxWidth  = getMaxWidth();

    size.x = std::min(propWidth, maxWidth);

    onResize();
}

void NLUI::Component::growHeight(const int incHeight) {
    const int propHeight = size.y + incHeight;
    const int maxHeight  = getMaxHeight();

    size.y = std::min(propHeight, maxHeight);

    onResize();
}

void NLUI::Component::setPos(const int xPos, const int yPos) {
    pos.x = xPos;
    pos.y = yPos;
}

void NLUI::Component::setPos(const glm::ivec2 &pos) {
    this->pos = pos;
}

void NLUI::Component::setXPos(const int xPos) {
    pos.x = xPos;
}

void NLUI::Component::setYPos(const int yPos) {
    pos.y = yPos;
}

void NLUI::Component::setMinSize(const int minWidth, const int minHeight) {
    minSize.x = minWidth;
    minSize.y = minHeight;
}

void NLUI::Component::setMinSize(const glm::ivec2 &minSize) {
    this->minSize = minSize;
}

void NLUI::Component::setMinWidth(const int minWidth) {
    minSize.x = minWidth;
}

void NLUI::Component::setMinHeight(const int minHeight) {
    minSize.y = minHeight;
}

void NLUI::Component::setMaxSize(const int maxWidth, const int maxHeight) {
    maxSize.x = maxWidth;
    maxSize.y = maxHeight;
}

void NLUI::Component::setMaxSize(const glm::ivec2 &maxSize) {
    this->maxSize = maxSize;
}

void NLUI::Component::setMaxWidth(const int maxWidth) {
    maxSize.x = maxWidth;
}

void NLUI::Component::setMaxHeight(const int maxHeight) {
    maxSize.y = maxHeight;
}

void NLUI::Component::getSize(int &width, int &height) const {
    width  = size.x;
    height = size.y;
}

ivec2 NLUI::Component::getSize() const {
    return size;
}

int NLUI::Component::getWidth() const {
    return size.x;
}

int NLUI::Component::getHeight() const {
    return size.y;
}

void NLUI::Component::getMinSize(int &minWidth, int &minHeight) const {
    minWidth  = minSize.x;
    minHeight = minSize.y;
}

glm::ivec2 NLUI::Component::getMinSize() const {
    return minSize;
}

int NLUI::Component::getMinWidth() const {
    return minSize.x;
}

int NLUI::Component::getMinHeight() const {
    return minSize.y;
}

void NLUI::Component::getMaxSize(int &maxWidth, int &maxHeight) const {
    maxWidth  = maxSize.x;
    maxHeight = maxSize.y;
}

glm::ivec2 NLUI::Component::getMaxSize() const {
    return maxSize;
}

int NLUI::Component::getMaxWidth() const {
    return maxSize.x;
}

int NLUI::Component::getMaxHeight() const {
    return maxSize.y;
}

void NLUI::Component::getExtraSize(int &extraWidth, int &extraHeight) const {
    const glm::ivec2 minSize = getMinSize();
    
    extraWidth  = size.x - minSize.x;
    extraHeight = size.y - minSize.y;
}

glm::ivec2 NLUI::Component::getExtraSize() const {
    const glm::ivec2 minSize = getMinSize();

    return size - minSize;
}

int NLUI::Component::getExtraWidth() const {
    const int minWidth = getMinWidth();

    return size.x - minWidth;
}

int NLUI::Component::getExtraHeight() const {
    const int minHeight = getMinHeight();

    return size.y - minHeight;
}

void NLUI::Component::getGrowthSize(int &growthWidth, int &growthHeight) const {
    const glm::ivec2 maxSize = getMaxSize();

    growthWidth  = maxSize.x - size.x;
    growthHeight = maxSize.y - size.y;
}

glm::ivec2 NLUI::Component::getGrowthSize() const {
    const glm::ivec2 maxSize = getMaxSize();

    return maxSize - size;
}

int NLUI::Component::getGrowthWidth() const {
    const int maxWidth = getMaxWidth();

    return maxWidth - size.x;
}

int NLUI::Component::getGrowthHeight() const {
    const int maxHeight = getMaxHeight();

    return maxHeight - size.y;
}

void NLUI::Component::getPos(int &xPos, int &yPos) const {
    xPos = pos.x;
    yPos = pos.y;
}

ivec2 NLUI::Component::getPos() const {
    return pos;
}

int NLUI::Component::getXPos() const {
    return pos.x;
}

int NLUI::Component::getYPos() const {
    return pos.y;
}

bool NLUI::Component::mouseInside(const double xPos, const double yPos) {
    // Check minimum
    if(xPos < pos.x || yPos < pos.y) {
        return false;
    }

    // Check maximum
    if(xPos >= pos.x + size.x || yPos >= pos.y + size.y) {
        return false;
    }

    return true;
}

vec4 NLUI::Component::getBackgroundColour() const {
    return backgroundColour;
}

void NLUI::Component::setBackgroundColour(const float r, const float g, const float b, const float a) {
    backgroundColour.r = r;
    backgroundColour.g = g;
    backgroundColour.b = b;
    backgroundColour.a = a;
}

void NLUI::Component::setBackgroundColour(const float r, const float g, const float b) {
    backgroundColour.r = r;
    backgroundColour.g = g;
    backgroundColour.b = b;
}

void NLUI::Component::setBackgroundColour(const vec4 &backgroundColour) {
    this->backgroundColour = backgroundColour;
}
