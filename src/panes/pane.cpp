#include "pane.hpp"

// Includes from standard


// Includes from third party libraries


// Includes from personal libraries


// Includes from project


// Forward declarations


// Type aliases



NLUI::Pane::Pane(const glm::ivec2 &minSize, const glm::ivec2 &maxSize) : BaseComponent(minSize, maxSize) {

}

NLUI::Pane::~Pane() = default;

void NLUI::Pane::layoutRoot() {
    if(parent != nullptr) {
        parent->layoutRoot();
    } else {
        doLayout();
    }
}

void NLUI::Pane::onResize() {
    doLayout();
}

void NLUI::Pane::processKeyPress(const int key) {
    BaseComponent::processKeyPress(key);

    clickFocus->processKeyPress(key);
}

void NLUI::Pane::processKeyRepeat(const int key) {
    BaseComponent::processKeyRepeat(key);

    clickFocus->processKeyRepeat(key);    
}

void NLUI::Pane::processKeyRelease(const int key) {
    BaseComponent::processKeyRelease(key);

    clickFocus->processKeyRelease(key);    
}

// void NLUI::Pane::processMousePress(const int key, const double xPos, const double yPos) {
//     BaseComponent::processMousePress(key, xPos, yPos);

//     hoverFocus->processMousePress(key, xPos, yPos);
// }

void NLUI::Pane::processMouseRepeat(const int key, const double xPos, const double yPos) {
    hoverFocus->processMouseRepeat(key, xPos, yPos);
}

void NLUI::Pane::processMouseRelease(const int key, const double xPos, const double yPos) {
    hoverFocus->processMouseRelease(key, xPos, yPos);
}
        
// void NLUI::Pane::processMouseMovement(const double xPos, const double yPos, const double deltaX, const double deltaY) {
    
// }

void NLUI::Pane::processMouseEnter() {
    
}

void NLUI::Pane::processMouseExit() {
    
}
        
void NLUI::Pane::processMouseScroll(const double deltaX, const double deltaY) {
    BaseComponent::processMouseScroll(deltaX, deltaY);

    hoverFocus->processMouseScroll(deltaX, deltaY);
}