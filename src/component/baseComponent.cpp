#include "baseComponent.hpp"

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



NLUI::BaseComponent::BaseComponent(const glm::ivec2 &minSize, const glm::ivec2 &maxSize) : Component(),
    minSize(minSize), maxSize(maxSize) {

}

NLUI::BaseComponent::~BaseComponent() {

}

void NLUI::BaseComponent::setParent(Container *parent) {
    removeParent();

    this->parent = parent;
}

void NLUI::BaseComponent::removeParent() {
    Container *const oldParent = this->parent;
    this->parent = nullptr;    
    
    if(oldParent) {
        oldParent->removeComponent(this);
    }
}

void NLUI::BaseComponent::layoutRoot() {
    if(parent != nullptr) {
        parent->layoutRoot();
    }
}

void NLUI::BaseComponent::draw() const {
    // TODO implement, accumulate the vertices
    Graphics::drawSolidQuad(backgroundColour, pos, size);
}

void NLUI::BaseComponent::setSize(const int width, const int height) {
    size.x = width;
    size.y = height;

    onResize();
}

void NLUI::BaseComponent::setSize(const glm::ivec2 &size) {
    this->size = size;

    onResize();
}

void NLUI::BaseComponent::setWidth(const int width) {
    size.x = width;

    onResize();
}

void NLUI::BaseComponent::setHeight(const int height) {
    size.y = height;

    onResize();
}

void NLUI::BaseComponent::proposeSize(const int propWidth, const int propHeight) {
    const glm::ivec2 propSize = glm::ivec2(propWidth, propHeight);

    const glm::ivec2 prefSize = getPrefSize();
    const glm::ivec2 minSize  = getMinSize();
    const glm::ivec2 maxSize  = getMaxSize();

    size = glm::min(prefSize, glm::min(maxSize, max(minSize, propSize)));

    onResize();
}

void NLUI::BaseComponent::proposeSize(const glm::ivec2 &propSize) {
    const glm::ivec2 prefSize = getPrefSize();
    const glm::ivec2 minSize  = getMinSize();
    const glm::ivec2 maxSize  = getMaxSize();

    size = glm::min(prefSize, glm::min(maxSize, glm::max(minSize, propSize)));

    onResize();
}

void NLUI::BaseComponent::proposeWidth(const int propWidth) {
    const int prefWidth = getPrefWidth();
    const int minWidth  = getMinWidth();
    const int maxWidth  = getMaxWidth();

    size.x = std::min(prefWidth, std::min(maxWidth, std::max(minWidth, propWidth)));

    onResize();
}

void NLUI::BaseComponent::proposeHeight(const int propHeight) {
    const int prefHeight = getPrefHeight();
    const int minHeight  = getMinHeight();
    const int maxHeight  = getMaxHeight();

    size.y = std::min(prefHeight, std::min(maxHeight, std::max(minHeight, propHeight)));

    onResize();
}

void NLUI::BaseComponent::shrinkSize(const int decWidth, const int decHeight) {
    size.x -= decWidth;
    size.y -= decHeight;

    onResize();
}

void NLUI::BaseComponent::shrinkSize(const glm::ivec2 &decSize) {
    size -= decSize;

    onResize();
}

void NLUI::BaseComponent::shrinkWidth(const int decWidth) {
    size.x -= decWidth;

    onResize();
}

void NLUI::BaseComponent::shrinkHeight(const int decHeight) {
    size.y -= decHeight;

    onResize();
}

void NLUI::BaseComponent::shrinkToSize(const int propWidth, const int propHeight) {
    size.x = propWidth;
    size.y = propHeight;

    onResize();
}

void NLUI::BaseComponent::shrinkToSize(const glm::ivec2 &propSize) {
    size = propSize;

    onResize();
}

void NLUI::BaseComponent::shrinkToWidth(const int propWidth) {
    size.x = propWidth;

    onResize();
}

void NLUI::BaseComponent::shrinkToHeight(const int propHeight) {
    size.y = propHeight;

    onResize();
}

void NLUI::BaseComponent::growSize(const int incWidth, const int incHeight) {
    const glm::ivec2 propSize = size + glm::ivec2(incWidth, incHeight);
    const glm::ivec2 maxSize  = getMaxSize();

    size = glm::min(propSize, maxSize);

    onResize();
}

void NLUI::BaseComponent::growSize(const glm::ivec2 &incSize) {
    const glm::ivec2 propSize = size + incSize;
    const glm::ivec2 maxSize  = getMaxSize();

    size = glm::min(propSize, maxSize);

    onResize();
}

void NLUI::BaseComponent::growWidth(const int incWidth) {
    const int propWidth = size.x + incWidth;
    const int maxWidth  = getMaxWidth();

    size.x = std::min(propWidth, maxWidth);

    onResize();
}

void NLUI::BaseComponent::growHeight(const int incHeight) {
    const int propHeight = size.y + incHeight;
    const int maxHeight  = getMaxHeight();

    size.y = std::min(propHeight, maxHeight);

    onResize();
}

void NLUI::BaseComponent::growToSize(const int propWidth, const int propHeight) {
    const glm::ivec2 propSize = glm::ivec2(propWidth, propHeight);
    const glm::ivec2 maxSize  = getMaxSize();

    size = glm::min(propSize, maxSize);

    onResize();
}

void NLUI::BaseComponent::growToSize(const glm::ivec2 &propSize) {
    const glm::ivec2 maxSize = getMaxSize();

    size = glm::min(propSize, maxSize);

    onResize();
}

void NLUI::BaseComponent::growToWidth(const int propWidth) {
    const int maxWidth = getMaxWidth();

    size.x = std::min(propWidth, maxWidth);

    onResize();
}

void NLUI::BaseComponent::growToHeight(const int propHeight) {
    const int maxHeight = getMaxHeight();

    size.y = std::min(propHeight, maxHeight);

    onResize();
}

void NLUI::BaseComponent::setPos(const int xPos, const int yPos) {
    pos.x = xPos;
    pos.y = yPos;
}

void NLUI::BaseComponent::setPos(const glm::ivec2 &pos) {
    this->pos = pos;
}

void NLUI::BaseComponent::setXPos(const int xPos) {
    pos.x = xPos;
}

void NLUI::BaseComponent::setYPos(const int yPos) {
    pos.y = yPos;
}

void NLUI::BaseComponent::setMinSize(const int minWidth, const int minHeight) {
    minSize.x = minWidth;
    minSize.y = minHeight;
}

void NLUI::BaseComponent::setMinSize(const glm::ivec2 &minSize) {
    this->minSize = minSize;
}

void NLUI::BaseComponent::setMinWidth(const int minWidth) {
    minSize.x = minWidth;
}

void NLUI::BaseComponent::setMinHeight(const int minHeight) {
    minSize.y = minHeight;
}

void NLUI::BaseComponent::setMaxSize(const int maxWidth, const int maxHeight) {
    maxSize.x = maxWidth;
    maxSize.y = maxHeight;
}

void NLUI::BaseComponent::setMaxSize(const glm::ivec2 &maxSize) {
    this->maxSize = maxSize;
}

void NLUI::BaseComponent::setMaxWidth(const int maxWidth) {
    maxSize.x = maxWidth;
}

void NLUI::BaseComponent::setMaxHeight(const int maxHeight) {
    maxSize.y = maxHeight;
}

void NLUI::BaseComponent::getSize(int &width, int &height) const {
    width  = size.x;
    height = size.y;
}

ivec2 NLUI::BaseComponent::getSize() const {
    return size;
}

int NLUI::BaseComponent::getWidth() const {
    return size.x;
}

int NLUI::BaseComponent::getHeight() const {
    return size.y;
}

void NLUI::BaseComponent::getMinSize(int &minWidth, int &minHeight) const {
    minWidth  = minSize.x;
    minHeight = minSize.y;
}

glm::ivec2 NLUI::BaseComponent::getMinSize() const {
    return minSize;
}

int NLUI::BaseComponent::getMinWidth() const {
    return minSize.x;
}

int NLUI::BaseComponent::getMinHeight() const {
    return minSize.y;
}

void NLUI::BaseComponent::getMaxSize(int &maxWidth, int &maxHeight) const {
    maxWidth  = maxSize.x;
    maxHeight = maxSize.y;
}

glm::ivec2 NLUI::BaseComponent::getMaxSize() const {
    return maxSize;
}

int NLUI::BaseComponent::getMaxWidth() const {
    return maxSize.x;
}

int NLUI::BaseComponent::getMaxHeight() const {
    return maxSize.y;
}

void NLUI::BaseComponent::getExtraSize(int &extraWidth, int &extraHeight) const {
    const glm::ivec2 minSize = getMinSize();
    
    extraWidth  = size.x - minSize.x;
    extraHeight = size.y - minSize.y;
}

glm::ivec2 NLUI::BaseComponent::getExtraSize() const {
    const glm::ivec2 minSize = getMinSize();

    return size - minSize;
}

int NLUI::BaseComponent::getExtraWidth() const {
    const int minWidth = getMinWidth();

    return size.x - minWidth;
}

int NLUI::BaseComponent::getExtraHeight() const {
    const int minHeight = getMinHeight();

    return size.y - minHeight;
}

void NLUI::BaseComponent::getGrowthSize(int &growthWidth, int &growthHeight) const {
    const glm::ivec2 maxSize = getMaxSize();

    growthWidth  = maxSize.x - size.x;
    growthHeight = maxSize.y - size.y;
}

glm::ivec2 NLUI::BaseComponent::getGrowthSize() const {
    const glm::ivec2 maxSize = getMaxSize();

    return maxSize - size;
}

int NLUI::BaseComponent::getGrowthWidth() const {
    const int maxWidth = getMaxWidth();

    return maxWidth - size.x;
}

int NLUI::BaseComponent::getGrowthHeight() const {
    const int maxHeight = getMaxHeight();

    return maxHeight - size.y;
}

void NLUI::BaseComponent::getPos(int &xPos, int &yPos) const {
    xPos = pos.x;
    yPos = pos.y;
}

ivec2 NLUI::BaseComponent::getPos() const {
    return pos;
}

int NLUI::BaseComponent::getXPos() const {
    return pos.x;
}

int NLUI::BaseComponent::getYPos() const {
    return pos.y;
}

bool NLUI::BaseComponent::mouseInside(const double xPos, const double yPos) {
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

vec4 NLUI::BaseComponent::getBackgroundColour() const {
    return backgroundColour;
}

void NLUI::BaseComponent::setBackgroundColour(const float r, const float g, const float b, const float a) {
    backgroundColour.r = r;
    backgroundColour.g = g;
    backgroundColour.b = b;
    backgroundColour.a = a;
}

void NLUI::BaseComponent::setBackgroundColour(const float r, const float g, const float b) {
    backgroundColour.r = r;
    backgroundColour.g = g;
    backgroundColour.b = b;
}

void NLUI::BaseComponent::setBackgroundColour(const vec4 &backgroundColour) {
    this->backgroundColour = backgroundColour;
}
