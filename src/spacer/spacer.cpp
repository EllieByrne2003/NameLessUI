#include "spacer.hpp"

// Includes from standard


// Includes from third party libraries
#include <glm/glm.hpp>
using namespace glm;

// Includes from personal libraries


// Includes from project


// Forward declarations


// Type aliases


NLUI::Spacer::Spacer(const glm::ivec2 &prefSize, const glm::ivec2 &minSize, const glm::ivec2 &maxSize) : BaseComponent(minSize, maxSize),
    prefSize(prefSize) {

}

NLUI::Spacer::~Spacer() {

}

std::shared_ptr<NLUI::Spacer> NLUI::Spacer::create(const glm::ivec2 &prefSize, const glm::ivec2 &minSize, const glm::ivec2 &maxSize) {
    return std::shared_ptr<Spacer>(new Spacer(prefSize, minSize, maxSize));
}

void NLUI::Spacer::getPrefSize(int &prefWidth, int &prefHeight) const {
    prefWidth  = prefSize.x;
    prefHeight = prefSize.y; 
}

glm::ivec2 NLUI::Spacer::getPrefSize() const {
    return prefSize;
}

int NLUI::Spacer::getPrefWidth() const {
    return prefSize.x;
}

int NLUI::Spacer::getPrefHeight() const {
    return prefSize.y;
}

// TODO maybe give an empty one in component.cpp and remove this?
void NLUI::Spacer::onResize() {

}

void NLUI::Spacer::setPreferredSize(const int preferredWidth, const int preferredHeight) {
    prefSize.x = preferredWidth;
    prefSize.y = preferredHeight;
}

void NLUI::Spacer::setPreferredSize(const ivec2 &preferredSize) {
    this->prefSize = preferredSize;
}

void NLUI::Spacer::setPreferredWidth(const int preferredWidth) {
    prefSize.x = preferredWidth;
}

void NLUI::Spacer::setPreferredHeight(const int preferredHeight) {
    prefSize.y = preferredHeight;
}