#include "spacer.hpp"

// Includes from standard


// Includes from third party libraries
#include <glm/glm.hpp>
using namespace glm;

// Includes from personal libraries


// Includes from project


// Forward declarations


// Type aliases


NLUI::Spacer::Spacer(const glm::ivec2 &prefSize, const glm::ivec2 &minSize, const glm::ivec2 &maxSize) : Component(minSize, maxSize),
    preferredSize(prefSize) {

}

NLUI::Spacer::~Spacer() {

}

std::shared_ptr<NLUI::Spacer> NLUI::Spacer::create(const glm::ivec2 &prefSize, const glm::ivec2 &minSize, const glm::ivec2 &maxSize) {
    return std::shared_ptr<Spacer>(new Spacer(prefSize, minSize, maxSize));
}

void NLUI::Spacer::getPreferredSize(int &preferredWidth, int &preferredHeight) const {
    preferredWidth  = preferredSize.x;
    preferredHeight = preferredSize.y;
}

ivec2 NLUI::Spacer::getPreferredSize() const {
    return preferredSize;
}

int NLUI::Spacer::getPreferredWidth() const {
    return preferredSize.x;
}

int NLUI::Spacer::getPreferredHeight() const {
    return preferredSize.y;
}

void NLUI::Spacer::resize() {

}

void NLUI::Spacer::setPreferredSize(const int preferredWidth, const int preferredHeight) {
    preferredSize.x = preferredWidth;
    preferredSize.y = preferredHeight;
}

void NLUI::Spacer::setPreferredSize(const ivec2 &preferredSize) {
    this->preferredSize = preferredSize;
}

void NLUI::Spacer::setPreferredWidth(const int preferredWidth) {
    preferredSize.x = preferredWidth;
}

void NLUI::Spacer::setPreferredHeight(const int preferredHeight) {
    preferredSize.y = preferredHeight;
}