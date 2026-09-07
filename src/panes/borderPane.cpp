#include "borderPane.hpp"

// Includes from standard
#include <algorithm>
#include <memory>

// Includes from third party libraries


// Includes from personal libraries


// Includes from project


// Forward declarations


// Type aliases


NLUI::BorderPane::BorderPane(const bool horizontal, const glm::ivec2 &minSize, const glm::ivec2 &maxSize) : Pane(minSize, maxSize),
    horizontal(horizontal) {

}

NLUI::BorderPane::~BorderPane() {

}

std::shared_ptr<NLUI::BorderPane> NLUI::BorderPane::create(const bool horizontal, const glm::ivec2 &minSize, const glm::ivec2 &maxSize) {
    return std::shared_ptr<BorderPane>(new BorderPane(horizontal, minSize, maxSize));
}

std::shared_ptr<NLUI::Component> & NLUI::BorderPane::getComponent(const Position &pos) {
    return components[pos];
}

std::shared_ptr<NLUI::Component> & NLUI::BorderPane::centre() {
    return components[Position::CENTRE];
}

std::shared_ptr<NLUI::Component> & NLUI::BorderPane::north() {
    return components[Position::NORTH];
}

std::shared_ptr<NLUI::Component> & NLUI::BorderPane::south() {
    return components[Position::SOUTH];
}

std::shared_ptr<NLUI::Component> & NLUI::BorderPane::east() {
    return components[Position::EAST];
}

std::shared_ptr<NLUI::Component> & NLUI::BorderPane::west() {
    return components[Position::WEST];
}

void NLUI::BorderPane::draw() const {
    Pane::draw();

    for(const std::shared_ptr<const Component> &component : components) {
        if(component != nullptr) {
            component->draw();
        }
    }
}

void NLUI::BorderPane::getPrefSize(int &prefWidth, int &prefHeight) const {
    const glm::ivec2 centrePrefSize = getCentrePrefSize();
    const glm::ivec2 northPrefSize  = getNorthPrefSize();
    const glm::ivec2 southPrefSize  = getSouthPrefSize();
    const glm::ivec2 eastPrefSize   = getEastPrefSize();
    const glm::ivec2 westPrefSize   = getWestPrefSize();
    
    if(horizontal) {
        int greatestPrefWidth = 0;
        int sumPrefHeight     = 0;

        greatestPrefWidth = std::max(greatestPrefWidth, northPrefSize.x);
        greatestPrefWidth = std::max(greatestPrefWidth, southPrefSize.x);
        greatestPrefWidth = std::max(greatestPrefWidth, eastPrefSize.x + centrePrefSize.x + westPrefSize.x);

        sumPrefHeight += northPrefSize.y;
        sumPrefHeight += southPrefSize.y;
        sumPrefHeight += std::max(eastPrefSize.x, std::max(centrePrefSize.y, westPrefSize.y));

        prefWidth  = greatestPrefWidth;
        prefHeight = sumPrefHeight;
    } else {
        int sumPrefWidth       = 0;
        int greatestPrefHeight = 0;

        sumPrefWidth += eastPrefSize.x;
        sumPrefWidth += westPrefSize.x;
        sumPrefWidth += std::max(northPrefSize.x, std::max(centrePrefSize.x, southPrefSize.x));

        greatestPrefHeight = std::max(greatestPrefHeight, eastPrefSize.y);
        greatestPrefHeight = std::max(greatestPrefHeight, westPrefSize.y);
        greatestPrefHeight = std::max(greatestPrefHeight, northPrefSize.y + centrePrefSize.y + southPrefSize.y);

        prefWidth  = sumPrefWidth;
        prefHeight = greatestPrefHeight;
    }
}

glm::ivec2 NLUI::BorderPane::getPrefSize() const {
    const glm::ivec2 centrePrefSize = getCentrePrefSize();
    const glm::ivec2 northPrefSize  = getNorthPrefSize();
    const glm::ivec2 southPrefSize  = getSouthPrefSize();
    const glm::ivec2 eastPrefSize   = getEastPrefSize();
    const glm::ivec2 westPrefSize   = getWestPrefSize();
    
    if(horizontal) {
        int greatestPrefWidth = 0;
        int sumPrefHeight     = 0;

        greatestPrefWidth = std::max(greatestPrefWidth, northPrefSize.x);
        greatestPrefWidth = std::max(greatestPrefWidth, southPrefSize.x);
        greatestPrefWidth = std::max(greatestPrefWidth, eastPrefSize.x + centrePrefSize.x + westPrefSize.x);

        sumPrefHeight += northPrefSize.y;
        sumPrefHeight += southPrefSize.y;
        sumPrefHeight += std::max(eastPrefSize.x, std::max(centrePrefSize.y, westPrefSize.y));

        return glm::ivec2(greatestPrefWidth, sumPrefHeight);
    } else {
        int sumPrefWidth       = 0;
        int greatestPrefHeight = 0;

        sumPrefWidth += eastPrefSize.x;
        sumPrefWidth += westPrefSize.x;
        sumPrefWidth += std::max(northPrefSize.x, std::max(centrePrefSize.x, southPrefSize.x));

        greatestPrefHeight = std::max(greatestPrefHeight, eastPrefSize.y);
        greatestPrefHeight = std::max(greatestPrefHeight, westPrefSize.y);
        greatestPrefHeight = std::max(greatestPrefHeight, northPrefSize.y + centrePrefSize.y + southPrefSize.y);

        return glm::ivec2(sumPrefWidth, greatestPrefHeight);
    }
}

int NLUI::BorderPane::getPrefWidth() const {
    if(horizontal) {
        int greatestPrefWidth = 0;

        greatestPrefWidth = std::max(greatestPrefWidth, getNorthPrefWidth());
        greatestPrefWidth = std::max(greatestPrefWidth, getSouthPrefWidth());
        greatestPrefWidth = std::max(greatestPrefWidth, getEastPrefWidth() + getCentrePrefWidth() + getWestPrefWidth());

        return greatestPrefWidth;
    } else {
        int sumPrefWidth = 0;

        sumPrefWidth += getEastPrefWidth();
        sumPrefWidth += getWestPrefWidth();
        sumPrefWidth += std::max(getNorthPrefWidth(), std::max(getCentrePrefWidth(), getSouthPrefWidth()));

        return sumPrefWidth;
    }
}

int NLUI::BorderPane::getPrefHeight() const {
    if(horizontal) {
        int sumPrefHeight = 0;

        sumPrefHeight += getNorthPrefHeight();
        sumPrefHeight += getSouthPrefHeight();
        sumPrefHeight += std::max(getEastPrefHeight(), std::max(getCentrePrefHeight(), getWestPrefHeight()));

        return sumPrefHeight;
    } else {
        int greatestPrefHeight = 0;

        greatestPrefHeight = std::max(greatestPrefHeight, getEastPrefHeight());
        greatestPrefHeight = std::max(greatestPrefHeight, getWestPrefHeight());
        greatestPrefHeight = std::max(greatestPrefHeight, getNorthPrefHeight() + getCentrePrefHeight() + getSouthPrefHeight());

        return greatestPrefHeight;
    }
}

void NLUI::BorderPane::getMinSize(int &minWidth, int &minHeight) const {
    const glm::ivec2 centreMinSize = getCentreMinSize();
    const glm::ivec2 northMinSize  = getNorthMinSize();
    const glm::ivec2 southMinSize  = getSouthMinSize();
    const glm::ivec2 eastMinSize   = getEastMinSize();
    const glm::ivec2 westMinSize   = getWestMinSize();
    
    if(horizontal) {
        int greatestMinWidth = 0;
        int sumMinHeight     = 0;

        greatestMinWidth = std::max(greatestMinWidth, northMinSize.x);
        greatestMinWidth = std::max(greatestMinWidth, southMinSize.x);
        greatestMinWidth = std::max(greatestMinWidth, eastMinSize.x + centreMinSize.x + westMinSize.x);

        sumMinHeight += northMinSize.y;
        sumMinHeight += southMinSize.y;
        sumMinHeight += std::max(eastMinSize.x, std::max(centreMinSize.y, westMinSize.y));

        minWidth  = std::max(minSize.x, greatestMinWidth);
        minHeight = std::max(minSize.y, sumMinHeight);
    } else {
        int sumMinWidth       = 0;
        int greatestMinHeight = 0;

        sumMinWidth += eastMinSize.x;
        sumMinWidth += westMinSize.x;
        sumMinWidth += std::max(northMinSize.x, std::max(centreMinSize.x, southMinSize.x));

        greatestMinHeight = std::max(greatestMinHeight, eastMinSize.y);
        greatestMinHeight = std::max(greatestMinHeight, westMinSize.y);
        greatestMinHeight = std::max(greatestMinHeight, northMinSize.y + centreMinSize.y + southMinSize.y);

        minWidth  = std::max(minSize.x, sumMinWidth);
        minHeight = std::max(minSize.y, greatestMinHeight);
    }
}

glm::ivec2 NLUI::BorderPane::getMinSize() const {
    const glm::ivec2 centreMinSize = getCentreMinSize();
    const glm::ivec2 northMinSize  = getNorthMinSize();
    const glm::ivec2 southMinSize  = getSouthMinSize();
    const glm::ivec2 eastMinSize   = getEastMinSize();
    const glm::ivec2 westMinSize   = getWestMinSize();
    
    if(horizontal) {
        int greatestMinWidth = 0;
        int sumMinHeight     = 0;

        greatestMinWidth = std::max(greatestMinWidth, northMinSize.x);
        greatestMinWidth = std::max(greatestMinWidth, southMinSize.x);
        greatestMinWidth = std::max(greatestMinWidth, eastMinSize.x + centreMinSize.x + westMinSize.x);

        sumMinHeight += northMinSize.y;
        sumMinHeight += southMinSize.y;
        sumMinHeight += std::max(eastMinSize.x, std::max(centreMinSize.y, westMinSize.y));

        return glm::ivec2(std::max(minSize.x, greatestMinWidth), std::max(minSize.y, sumMinHeight));
    } else {
        int sumMinWidth       = 0;
        int greatestMinHeight = 0;

        sumMinWidth += eastMinSize.x;
        sumMinWidth += westMinSize.x;
        sumMinWidth += std::max(northMinSize.x, std::max(centreMinSize.x, southMinSize.x));

        greatestMinHeight = std::max(greatestMinHeight, eastMinSize.y);
        greatestMinHeight = std::max(greatestMinHeight, westMinSize.y);
        greatestMinHeight = std::max(greatestMinHeight, northMinSize.y + centreMinSize.y + southMinSize.y);

        return glm::ivec2(std::max(minSize.x, sumMinWidth), std::max(minSize.y, greatestMinHeight));
    }
}

int NLUI::BorderPane::getMinWidth() const {
    if(horizontal) {
        int greatestMinWidth = 0;

        greatestMinWidth = std::max(greatestMinWidth, getNorthMinWidth());
        greatestMinWidth = std::max(greatestMinWidth, getSouthMinWidth());
        greatestMinWidth = std::max(greatestMinWidth, getEastMinWidth() + getCentreMinWidth() + getWestMinWidth());

        return std::max(minSize.x, greatestMinWidth);
    } else {
        int sumMinWidth = 0;

        sumMinWidth += getEastMinWidth();
        sumMinWidth += getWestMinWidth();
        sumMinWidth += std::max(getNorthMinWidth(), std::max(getCentreMinWidth(), getSouthMinWidth()));

        return std::max(minSize.x, sumMinWidth);
    }
}

int NLUI::BorderPane::getMinHeight() const {
    if(horizontal) {
        int sumMinHeight = 0;

        sumMinHeight += getNorthMinHeight();
        sumMinHeight += getSouthMinHeight();
        sumMinHeight += std::max(getEastMinHeight(), std::max(getCentreMinHeight(), getWestMinHeight()));

        return std::max(minSize.y, sumMinHeight);
    } else {
        int greatestMinHeight = 0;

        greatestMinHeight = std::max(greatestMinHeight, getEastMinHeight());
        greatestMinHeight = std::max(greatestMinHeight, getWestMinHeight());
        greatestMinHeight = std::max(greatestMinHeight, getNorthMinHeight() + getCentreMinHeight() + getSouthMinHeight());

        return std::max(minSize.y, greatestMinHeight);
    }
}

void NLUI::BorderPane::getMaxSize(int &maxWidth, int &maxHeight) const {
    const glm::ivec2 centreMaxSize = getCentreMaxSize();
    const glm::ivec2 northMaxSize  = getNorthMaxSize();
    const glm::ivec2 southMaxSize  = getSouthMaxSize();
    const glm::ivec2 eastMaxSize   = getEastMaxSize();
    const glm::ivec2 westMaxSize   = getWestMaxSize();
    
    if(horizontal) {
        int greatestMaxWidth = 0;
        int sumMaxHeight     = 0;

        greatestMaxWidth = std::max(greatestMaxWidth, northMaxSize.x);
        greatestMaxWidth = std::max(greatestMaxWidth, southMaxSize.x);
        greatestMaxWidth = std::max(greatestMaxWidth, eastMaxSize.x + centreMaxSize.x + westMaxSize.x);

        sumMaxHeight += northMaxSize.y;
        sumMaxHeight += southMaxSize.y;
        sumMaxHeight += std::max(eastMaxSize.x, std::max(centreMaxSize.y, westMaxSize.y));

        maxWidth  = std::min(maxSize.x, greatestMaxWidth);
        maxHeight = std::min(maxSize.y, sumMaxHeight);
    } else {
        int sumMaxWidth       = 0;
        int greatestMaxHeight = 0;

        sumMaxWidth += eastMaxSize.x;
        sumMaxWidth += westMaxSize.x;
        sumMaxWidth += std::max(northMaxSize.x, std::max(centreMaxSize.x, southMaxSize.x));

        greatestMaxHeight = std::max(greatestMaxHeight, eastMaxSize.y);
        greatestMaxHeight = std::max(greatestMaxHeight, westMaxSize.y);
        greatestMaxHeight = std::max(greatestMaxHeight, northMaxSize.y + centreMaxSize.y + southMaxSize.y);

        maxWidth  = std::min(maxSize.x, sumMaxWidth);
        maxHeight = std::min(maxSize.y, greatestMaxHeight);
    }
}

glm::ivec2 NLUI::BorderPane::getMaxSize() const {
    const glm::ivec2 centreMaxSize = getCentreMaxSize();
    const glm::ivec2 northMaxSize  = getNorthMaxSize();
    const glm::ivec2 southMaxSize  = getSouthMaxSize();
    const glm::ivec2 eastMaxSize   = getEastMaxSize();
    const glm::ivec2 westMaxSize   = getWestMaxSize();
    
    if(horizontal) {
        int greatestMaxWidth = 0;
        int sumMaxHeight     = 0;

        greatestMaxWidth = std::max(greatestMaxWidth, northMaxSize.x);
        greatestMaxWidth = std::max(greatestMaxWidth, southMaxSize.x);
        greatestMaxWidth = std::max(greatestMaxWidth, eastMaxSize.x + centreMaxSize.x + westMaxSize.x);

        sumMaxHeight += northMaxSize.y;
        sumMaxHeight += southMaxSize.y;
        sumMaxHeight += std::max(eastMaxSize.x, std::max(centreMaxSize.y, westMaxSize.y));

        return glm::ivec2(std::min(maxSize.x, greatestMaxWidth), std::min(maxSize.y, sumMaxHeight));
    } else {
        int sumMaxWidth       = 0;
        int greatestMaxHeight = 0;

        sumMaxWidth += eastMaxSize.x;
        sumMaxWidth += westMaxSize.x;
        sumMaxWidth += std::max(northMaxSize.x, std::max(centreMaxSize.x, southMaxSize.x));

        greatestMaxHeight = std::max(greatestMaxHeight, eastMaxSize.y);
        greatestMaxHeight = std::max(greatestMaxHeight, westMaxSize.y);
        greatestMaxHeight = std::max(greatestMaxHeight, northMaxSize.y + centreMaxSize.y + southMaxSize.y);

        return glm::ivec2(std::min(maxSize.x, sumMaxWidth), std::min(maxSize.y, greatestMaxHeight));
    }
}

int NLUI::BorderPane::getMaxWidth() const {
    if(horizontal) {
        int greatestMaxWidth = 0;

        greatestMaxWidth = std::max(greatestMaxWidth, getNorthMaxWidth());
        greatestMaxWidth = std::max(greatestMaxWidth, getSouthMaxWidth());
        greatestMaxWidth = std::max(greatestMaxWidth, getEastMaxWidth() + getCentreMaxWidth() + getWestMaxWidth());

        return std::min(maxSize.x, greatestMaxWidth);
    } else {
        int sumMaxWidth = 0;

        sumMaxWidth += getEastMaxWidth();
        sumMaxWidth += getWestMaxWidth();
        sumMaxWidth += std::max(getNorthMaxWidth(), std::max(getCentreMaxWidth(), getSouthMaxWidth()));

        return std::min(maxSize.x, sumMaxWidth);
    }
}

int NLUI::BorderPane::getMaxHeight() const {
    if(horizontal) {
        int sumMaxHeight = 0;

        sumMaxHeight += getNorthMaxHeight();
        sumMaxHeight += getSouthMaxHeight();
        sumMaxHeight += std::max(getEastMaxHeight(), std::max(getCentreMaxHeight(), getWestMaxHeight()));

        return std::min(maxSize.y, sumMaxHeight);
    } else {
        int greatestMaxHeight = 0;

        greatestMaxHeight = std::max(greatestMaxHeight, getEastMaxHeight());
        greatestMaxHeight = std::max(greatestMaxHeight, getWestMaxHeight());
        greatestMaxHeight = std::max(greatestMaxHeight, getNorthMaxHeight() + getCentreMaxHeight() + getSouthMaxHeight());

        return std::min(maxSize.y, greatestMaxHeight);
    }
}    

bool NLUI::BorderPane::mouseInside(const double xPos, const double yPos) {
    if(Pane::mouseInside(xPos, yPos)) {
        for(const std::shared_ptr<Component> &component : components) {
            if(component->mouseInside(xPos, yPos)) {
                focus = component;
                break; // Canm only be one anyways
            }
        }

        return true;
    } else {
        return false;
    }
}

void NLUI::BorderPane::removeComponent(const std::shared_ptr<Component> &component) {
    if(component == nullptr) {
        return;
    }

    // Find its position (if it has one)
    std::shared_ptr<Component> *pos = std::find(std::begin(components), std::end(components), component);

    // If present remove it
    if(pos != std::end(components)) {
        std::shared_ptr<Component> copy = *pos; // Stops delete from being called on component

        if(focus == copy) {
            focus = nullptr;
        }
    
        *pos = nullptr;
        copy->removeParent();

        layoutRoot();
    }
}

void NLUI::BorderPane::removeComponent(Component *const component) {
    if(component == nullptr) {
        return;
    }
    
    // Find its position (if it has one)
    std::shared_ptr<Component> *pos = std::find_if(std::begin(components), std::end(components), 
        [component](const std::shared_ptr<Component> &ptr) { return ptr.get() == component; }
    );

    // If present remove it
    if(pos != std::end(components)) {
        std::shared_ptr<Component> copy = *pos; // Stops delete from being called on component

        if(focus == copy) {
            focus = nullptr;
        }
    
        *pos = nullptr;
        copy->removeParent();

        layoutRoot();
    } 
}

void NLUI::BorderPane::doLayout() {
    // Propose current size to each
    for(std::shared_ptr<Component> &comp : components) {
        if(comp != nullptr) {
            comp->proposeSize(size);
        }
    }

    if(horizontal) {
        if(north() != nullptr)


    } else {

    }
}

void NLUI::BorderPane::setCentre(const std::shared_ptr<Component> &component) {
    if(centre() != nullptr) {
        const std::shared_ptr<Component> copy = centre();

        if(focus == copy) {
            focus = nullptr;
        }

        centre() = nullptr;
        copy->removeParent();
    }

    centre() = component;

    layoutRoot();
}

void NLUI::BorderPane::setNorth(const std::shared_ptr<Component> &component) {
    if(north() != nullptr) {
        const std::shared_ptr<Component> copy = north();

        if(focus == copy) {
            focus = nullptr;
        }

        north() = nullptr;
        copy->removeParent();
    }

    north() = component;

    layoutRoot();
}

void NLUI::BorderPane::setSouth(const std::shared_ptr<Component> &component) {
    if(south() != nullptr) {
        const std::shared_ptr<Component> copy = south();

        if(focus == copy) {
            focus = nullptr;
        }

        south() = nullptr;
        copy->removeParent();
    }

    south() = component;

    layoutRoot();
}

void NLUI::BorderPane::setEast(const std::shared_ptr<Component> &component) {
    if(east() != nullptr) {
        const std::shared_ptr<Component> copy = east();

        if(focus == copy) {
            focus = nullptr;
        }

        east() = nullptr;
        copy->removeParent();
    }

    east() = component;

    layoutRoot();
}

void NLUI::BorderPane::setWest(const std::shared_ptr<Component> &component) {
    if(west() != nullptr) {
        const std::shared_ptr<Component> copy = west();

        if(focus == copy) {
            focus = nullptr;
        }

        west() = nullptr;
        copy->removeParent();
    }

    west() = component;

    layoutRoot();
}

const std::shared_ptr<NLUI::Component> & NLUI::BorderPane::getComponent(const Position &pos) const {
    return components[pos];
}

const std::shared_ptr<NLUI::Component> & NLUI::BorderPane::centre() const {
    return components[Position::CENTRE];
}

const std::shared_ptr<NLUI::Component> & NLUI::BorderPane::north() const {
    return components[Position::NORTH];
}

const std::shared_ptr<NLUI::Component> & NLUI::BorderPane::south() const {
    return components[Position::SOUTH];
}

const std::shared_ptr<NLUI::Component> & NLUI::BorderPane::east() const {
    return components[Position::EAST];
}

const std::shared_ptr<NLUI::Component> & NLUI::BorderPane::west() const {
    return components[Position::WEST];
}