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



NLUI::Component::Component() {

}

NLUI::Component::~Component() {

}

void NLUI::Component::setParent(Container *parent) {
    Container *const oldParent = this->parent;
    this->parent = nullptr;

    if(oldParent != nullptr) {
        oldParent->removeComponent(this);
    }

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
        parent->validate();
    }
}

void NLUI::Component::draw() const {
    // TODO implement, accumulate the vertices
    Graphics::drawSolidQuad(backgroundColour, pos, size);
}

void NLUI::Component::getMinimumSize(int &minimumWidth, int &minimumHeight) const {
    minimumWidth  = minimumSize.x;
    minimumHeight = minimumSize.y;
}

ivec2 NLUI::Component::getMinimumSize() const {
    return ivec2(getMinimumWidth(), getMinimumHeight());
}

int NLUI::Component::getMinimumWidth() const {
    return minimumSize.x;
}

int NLUI::Component::getMinimumHeight() const {
    return minimumSize.y;
}

void NLUI::Component::setMinimumSize(const int minimumWidth, const int minimumHeight) {
    minimumSize.x = minimumWidth;
    minimumSize.y = minimumHeight;

    // Validate parent can fit with new minimums
    validateParent();
}

void NLUI::Component::setMinimumSize(const ivec2 &minimumSize) {
    this->minimumSize = minimumSize;

    // Validate parent can fit with new minimums
    validateParent();
}

void NLUI::Component::setMinimumWidth(const int minimumWidth) {
    minimumSize.x = minimumWidth;

    // Validate parent can fit with new minimums
    validateParent();
}
        
void NLUI::Component::setMinimumHeight(const int minimumHeight) {
    minimumSize.y = minimumHeight;

    // Validate parent can fit with new minimums
    validateParent();
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

void NLUI::Component::setSize(const int width, const int height) {
    size.x = width;
    size.y = height;
}

void NLUI::Component::setSize(const ivec2 &size) {
    this->size = size;
}
        
void NLUI::Component::setWidth(const int width) {
    size.x = width;
}

void NLUI::Component::setHeight(const int height) {
    size.y = height;
}

void NLUI::Component::setPos(const int xPos, const int yPos) {
    pos.x = xPos;
    pos.y = yPos;
}

void NLUI::Component::setPos(const ivec2 &pos) {
    this->pos = pos;
}

void NLUI::Component::setXPos(const int xPos) {
    this->pos.x = xPos;
}

void NLUI::Component::setYPos(const int yPos) {
    this->pos.y = yPos;
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
