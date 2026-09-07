#include "nullComponent.hpp"

// Includes from standard


// Includes from third party libraries


// Includes from personal libraries


// Includes from project


// Forward declarations


// Type aliases


NLUI::NullComponent::NullComponent() : Component() {
}

NLUI::NullComponent::~NullComponent() {

};

std::shared_ptr<NLUI::NullComponent> & NLUI::NullComponent::getInstance() {
    static std::shared_ptr<NullComponent> instance(new NullComponent);

    return instance;
}

void NLUI::NullComponent::setParent(Container *parent) {
    return;
}

void NLUI::NullComponent::removeParent() {
    return;
}
void NLUI::NullComponent::layoutRoot() {
    return;
}

void NLUI::NullComponent::draw() const {
    return;
}

void NLUI::NullComponent::setSize(const int width, const int height) {
    return;
}

void NLUI::NullComponent::setSize(const glm::ivec2 &size) {
    return;
}

void NLUI::NullComponent::setWidth(const int width) {
    return;
}

void NLUI::NullComponent::setHeight(const int height) {
    return;
}

void NLUI::NullComponent::proposeSize(const int propWidth, const int propHeight) {
    return;
}

void NLUI::NullComponent::proposeSize(const glm::ivec2 &propSize) {
    return;
}

void NLUI::NullComponent::proposeWidth(const int propWidth) {
    return;
}

void NLUI::NullComponent::proposeHeight(const int propHeight) {
    return;
}

void NLUI::NullComponent::shrinkSize(const int decWidth, const int decHeight) {
    return;
}

void NLUI::NullComponent::shrinkSize(const glm::ivec2 &decSize) {
    return;
}

void NLUI::NullComponent::shrinkWidth(const int decWidth) {
    return;
}

void NLUI::NullComponent::shrinkHeight(const int decHeight) {
    return;
}

void NLUI::NullComponent::shrinkToSize(const int propWidth, const int propHeight) {
    return;
}

void NLUI::NullComponent::shrinkToSize(const glm::ivec2 &propSize) {
    return;
}

void NLUI::NullComponent::shrinkToWidth(const int propWidth) {
    return;
}

void NLUI::NullComponent::shrinkToHeight(const int propHeight) {
    return;
}

void NLUI::NullComponent::growSize(const int incWidth, const int incHeight) {
    return;
}

void NLUI::NullComponent::growSize(const glm::ivec2 &incSize) {
    return;
}

void NLUI::NullComponent::growWidth(const int incWidth) {
    return;
}

void NLUI::NullComponent::growHeight(const int incHeight) {
    return;
}

void NLUI::NullComponent::growToSize(const int propWidth, const int propHeight) {
    return;
}

void NLUI::NullComponent::growToSize(const glm::ivec2 &propSize) {
    return;
}

void NLUI::NullComponent::growToWidth(const int propWidth) {
    return;
}

void NLUI::NullComponent::growToHeight(const int propHeight) {
    return;
}

void NLUI::NullComponent::setPos(const int xPos, const int yPos) {
    return;
}

void NLUI::NullComponent::setPos(const glm::ivec2 &pos) {
    return;
}

void NLUI::NullComponent::setXPos(const int xPos) {
    return;
}

void NLUI::NullComponent::setYPos(const int yPos) {
    return;
}

void NLUI::NullComponent::setMinSize(const int minWidth, const int minHeight) {
    return;
}

void NLUI::NullComponent::setMinSize(const glm::ivec2 &minSize) {
    return;
}

void NLUI::NullComponent::setMinWidth(const int minWidth) {
    return;
}

void NLUI::NullComponent::setMinHeight(const int minHeight) {
    return;
}

void NLUI::NullComponent::setMaxSize(const int maxWidth, const int maxHeight) {
    return;
}

void NLUI::NullComponent::setMaxSize(const glm::ivec2 &maxSize) {
    return;
}

void NLUI::NullComponent::setMaxWidth(const int maxWidth) {
    return;
}

void NLUI::NullComponent::setMaxHeight(const int maxHeight) {
    return;
}

void NLUI::NullComponent::getSize(int &width, int &height) const {
    width  = 0;
    height = 0;

    return;
}

glm::ivec2 NLUI::NullComponent::getSize() const {
    return glm::ivec2(0, 0);
}

int NLUI::NullComponent::getWidth() const {
    return 0;
}

int NLUI::NullComponent::getHeight() const {
    return 0;
}

void NLUI::NullComponent::getPrefSize(int &prefWidth, int &prefHeight) const {
    return;
}

glm::ivec2 NLUI::NullComponent::getPrefSize() const {
    return glm::ivec2(0, 0);
}

int NLUI::NullComponent::getPrefWidth() const {
    return 0;
}

int NLUI::NullComponent::getPrefHeight() const {
    return 0;
}

void NLUI::NullComponent::getMinSize(int &minWidth, int &minHeight) const {
    minWidth  = 0;
    minHeight = 0;

    return;
}

glm::ivec2 NLUI::NullComponent::getMinSize() const {
    return glm::ivec2(0, 0);
}

int NLUI::NullComponent::getMinWidth() const {
    return 0;
}

int NLUI::NullComponent::getMinHeight() const {
    return 0;
}

void NLUI::NullComponent::getMaxSize(int &maxWidth, int &maxHeight) const {
    maxWidth  = 0;
    maxHeight = 0;

    return;
}

glm::ivec2 NLUI::NullComponent::getMaxSize() const {
    return glm::ivec2(0, 0);
}

int NLUI::NullComponent::getMaxWidth() const {
    return 0;
}

int NLUI::NullComponent::getMaxHeight() const {
    return 0;
}

void NLUI::NullComponent::getExtraSize(int &extraWidth, int &extraHeight) const {
    extraWidth  = 0;
    extraHeight = 0;

    return;
}

glm::ivec2 NLUI::NullComponent::getExtraSize() const {
    return glm::ivec2(0, 0);
}

int NLUI::NullComponent::getExtraWidth() const {
    return 0;
}

int NLUI::NullComponent::getExtraHeight() const {
    return 0;
}

void NLUI::NullComponent::getGrowthSize(int &growthWidth, int &growthHeight) const {
    growthWidth  = 0;
    growthHeight = 0;

    return;
}

glm::ivec2 NLUI::NullComponent::getGrowthSize() const {
    return glm::ivec2(0, 0);
}

int NLUI::NullComponent::getGrowthWidth() const {
    return 0;
}

int NLUI::NullComponent::getGrowthHeight() const {
    return 0;
}

void NLUI::NullComponent::getPos(int &xPos, int &yPos) const {
    xPos = 0;
    yPos = 0;

    return;
}

glm::ivec2 NLUI::NullComponent::getPos() const {
    return glm::ivec2(0, 0);
}

int NLUI::NullComponent::getXPos() const {
    return 0;
}

int NLUI::NullComponent::getYPos() const {
    return 0;
}

void NLUI::NullComponent::onResize() {
    return;
}

bool NLUI::NullComponent::mouseInside(const double xPos, const double yPos) {
    return false;
}

glm::vec4 NLUI::NullComponent::getBackgroundColour() const {
    return glm::vec4(0.0f);
}

void NLUI::NullComponent::setBackgroundColour(const float r, const float g, const float b, const float a) {
    return;
}

void NLUI::NullComponent::setBackgroundColour(const float r, const float g, const float b) {
    return;
}

void NLUI::NullComponent::setBackgroundColour(const glm::vec4 &backgroundColour) {
    return;
}