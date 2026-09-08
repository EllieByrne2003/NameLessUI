#include "borderPane.hpp"

// Includes from standard
#include <algorithm>
#include <memory>

// Includes from third party libraries


// Includes from personal libraries


// Includes from project
#include "../component/nullComponent.hpp"

// Forward declarations


// Type aliases


NLUI::BorderPane::BorderPane(const bool horizontal, const glm::ivec2 &minSize, const glm::ivec2 &maxSize) : Pane(minSize, maxSize),
    horizontal(horizontal) {
    for(int i = 0; i < components.size(); i++) {
        components[i] = NullComponent::getInstance(); // TODO replace unneeded null checks
    }
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
        component->draw();
    }
}

void NLUI::BorderPane::getPrefSize(int &prefWidth, int &prefHeight) const {
    const glm::ivec2 centrePrefSize = centre()->getPrefSize();
    const glm::ivec2 northPrefSize  = north()->getPrefSize();
    const glm::ivec2 southPrefSize  = south()->getPrefSize();
    const glm::ivec2 eastPrefSize   = east()->getPrefSize();
    const glm::ivec2 westPrefSize   = west()->getPrefSize();
    
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
    const glm::ivec2 centrePrefSize = centre()->getPrefSize();
    const glm::ivec2 northPrefSize  = north()->getPrefSize();
    const glm::ivec2 southPrefSize  = south()->getPrefSize();
    const glm::ivec2 eastPrefSize   = east()->getPrefSize();
    const glm::ivec2 westPrefSize   = west()->getPrefSize();
    
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

        greatestPrefWidth = std::max(greatestPrefWidth, north()->getPrefWidth());
        greatestPrefWidth = std::max(greatestPrefWidth, south()->getPrefWidth());
        greatestPrefWidth = std::max(greatestPrefWidth, east()->getPrefWidth() + centre()->getPrefWidth() + west()->getPrefWidth());

        return greatestPrefWidth;
    } else {
        int sumPrefWidth = 0;

        sumPrefWidth += east()->getPrefWidth();
        sumPrefWidth += west()->getPrefWidth();
        sumPrefWidth += std::max(north()->getPrefWidth(), std::max(centre()->getPrefWidth(), south()->getPrefWidth()));

        return sumPrefWidth;
    }
}

int NLUI::BorderPane::getPrefHeight() const {
    if(horizontal) {
        int sumPrefHeight = 0;

        sumPrefHeight += north()->getPrefHeight();
        sumPrefHeight += south()->getPrefHeight();
        sumPrefHeight += std::max(east()->getPrefHeight(), std::max(centre()->getPrefHeight(), west()->getPrefHeight()));

        return sumPrefHeight;
    } else {
        int greatestPrefHeight = 0;

        greatestPrefHeight = std::max(greatestPrefHeight, east()->getPrefHeight());
        greatestPrefHeight = std::max(greatestPrefHeight, west()->getPrefHeight());
        greatestPrefHeight = std::max(greatestPrefHeight, north()->getPrefHeight() + centre()->getPrefHeight() + south()->getPrefHeight());

        return greatestPrefHeight;
    }
}

void NLUI::BorderPane::getMinSize(int &minWidth, int &minHeight) const {
    const glm::ivec2 centreMinSize = centre()->getMinSize();
    const glm::ivec2 northMinSize  = north()->getMinSize();
    const glm::ivec2 southMinSize  = south()->getMinSize();
    const glm::ivec2 eastMinSize   = east()->getMinSize();
    const glm::ivec2 westMinSize   = west()->getMinSize();
    
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
    const glm::ivec2 centreMinSize = centre()->getMinSize();
    const glm::ivec2 northMinSize  = north()->getMinSize();
    const glm::ivec2 southMinSize  = south()->getMinSize();
    const glm::ivec2 eastMinSize   = east()->getMinSize();
    const glm::ivec2 westMinSize   = west()->getMinSize();
    
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

        greatestMinWidth = std::max(greatestMinWidth, north()->getMinWidth());
        greatestMinWidth = std::max(greatestMinWidth, south()->getMinWidth());
        greatestMinWidth = std::max(greatestMinWidth, east()->getMinWidth() + centre()->getMinWidth() + west()->getMinWidth());

        return std::max(minSize.x, greatestMinWidth);
    } else {
        int sumMinWidth = 0;

        sumMinWidth += east()->getMinWidth();
        sumMinWidth += west()->getMinWidth();
        sumMinWidth += std::max(north()->getMinWidth(), std::max(centre()->getMinWidth(), south()->getMinWidth()));

        return std::max(minSize.x, sumMinWidth);
    }
}

int NLUI::BorderPane::getMinHeight() const {
    if(horizontal) {
        int sumMinHeight = 0;

        sumMinHeight += north()->getMinHeight();
        sumMinHeight += south()->getMinHeight();
        sumMinHeight += std::max(east()->getMinHeight(), std::max(centre()->getMinHeight(), west()->getMinHeight()));

        return std::max(minSize.y, sumMinHeight);
    } else {
        int greatestMinHeight = 0;

        greatestMinHeight = std::max(greatestMinHeight, east()->getMinHeight());
        greatestMinHeight = std::max(greatestMinHeight, west()->getMinHeight());
        greatestMinHeight = std::max(greatestMinHeight, north()->getMinHeight() + centre()->getMinHeight() + south()->getMinHeight());

        return std::max(minSize.y, greatestMinHeight);
    }
}

void NLUI::BorderPane::getMaxSize(int &maxWidth, int &maxHeight) const {
    const glm::ivec2 centreMaxSize = centre()->getMaxSize();
    const glm::ivec2 northMaxSize  = north()->getMaxSize();
    const glm::ivec2 southMaxSize  = south()->getMaxSize();
    const glm::ivec2 eastMaxSize   = east()->getMaxSize();
    const glm::ivec2 westMaxSize   = west()->getMaxSize();
    
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
    const glm::ivec2 centreMaxSize = centre()->getMaxSize();
    const glm::ivec2 northMaxSize  = north()->getMaxSize();
    const glm::ivec2 southMaxSize  = south()->getMaxSize();
    const glm::ivec2 eastMaxSize   = east()->getMaxSize();
    const glm::ivec2 westMaxSize   = west()->getMaxSize();
    
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

        greatestMaxWidth = std::max(greatestMaxWidth, north()->getMaxWidth());
        greatestMaxWidth = std::max(greatestMaxWidth, south()->getMaxWidth());
        greatestMaxWidth = std::max(greatestMaxWidth, east()->getMaxWidth() + centre()->getMaxWidth() + west()->getMaxWidth());

        return std::min(maxSize.x, greatestMaxWidth);
    } else {
        int sumMaxWidth = 0;

        sumMaxWidth += east()->getMaxWidth();
        sumMaxWidth += west()->getMaxWidth();
        sumMaxWidth += std::max(north()->getMaxWidth(), std::max(centre()->getMaxWidth(), south()->getMaxWidth()));

        return std::min(maxSize.x, sumMaxWidth);
    }
}

int NLUI::BorderPane::getMaxHeight() const {
    if(horizontal) {
        int sumMaxHeight = 0;

        sumMaxHeight += north()->getMaxHeight();
        sumMaxHeight += south()->getMaxHeight();
        sumMaxHeight += std::max(east()->getMaxHeight(), std::max(centre()->getMaxHeight(), west()->getMaxHeight()));

        return std::min(maxSize.y, sumMaxHeight);
    } else {
        int greatestMaxHeight = 0;

        greatestMaxHeight = std::max(greatestMaxHeight, east()->getMaxHeight());
        greatestMaxHeight = std::max(greatestMaxHeight, west()->getMaxHeight());
        greatestMaxHeight = std::max(greatestMaxHeight, north()->getMaxHeight() + centre()->getMaxHeight() + south()->getMaxHeight());

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
#include <iostream>
void NLUI::BorderPane::doLayout() {
    // // Propose current size to each
    // for(std::shared_ptr<Component> &comp : components) {
    //     comp->proposeSize(size);
    // }

    for(std::shared_ptr<Component> &comp : components) {
        comp->shrinkToSize(0, 0);
    }

    std::cout << "w: " << size.x << ", h: " << size.y << std::endl;

    if(horizontal) {
        north()->growToWidth(size.x);
        south()->growToWidth(size.x);
    
        for(std::shared_ptr<Component> &comp : components) {
            comp->proposeHeight(size.y);
        }

        int rowHeight   = std::max(east()->getHeight(), std::max(centre()->getHeight(), west()->getHeight()));
        int totalHeight = north()->getHeight() + south()->getHeight() + rowHeight;

        int rowMinHeight   = std::max(east()->getMinHeight(), std::max(centre()->getMinHeight(), west()->getMinHeight()));
        int totalMinHeight = north()->getMinHeight() + south()->getMinHeight() + rowMinHeight;

        int rowExtraHeight   = std::max(0, rowHeight - rowMinHeight);
        int totalExtraHeight = std::max(0, totalHeight - totalMinHeight);

        if(totalHeight < size.y) {
            // TODO optimise the below, no energy for this rn
            // Expand height of row and components
            centre()->growToHeight((size.y - totalHeight) + rowHeight);
            east()->growToHeight(  (size.y - totalHeight) + rowHeight);
            west()->growToHeight(  (size.y - totalHeight) + rowHeight);

            rowHeight = std::max(east()->getHeight(), std::max(centre()->getHeight(), west()->getHeight()));
            totalHeight = north()->getHeight() + south()->getHeight() + rowHeight;

            // Give (extra + 1) / 2 to north
            north()->growHeight(((size.y - totalHeight) + 1) / 2); // Give extra height to north, if rounding error happens
            totalHeight = north()->getHeight() + south()->getHeight() + rowHeight;

            // Give extra to south
            south()->growHeight(size.y - totalHeight);
            totalHeight = north()->getHeight() + south()->getHeight() + rowHeight;

            // Give remaining to north
            north()->growHeight(size.y - totalHeight); // Give extra height to north, if rounding error happens
            totalHeight = north()->getHeight() + south()->getHeight() + rowHeight;
        } else if(totalHeight > size.y) {
            if(totalHeight - totalExtraHeight <= size.y) {
                // Remove proporitonally
                const int reduction = totalHeight - size.y;

                north()->shrinkHeight(reduction * (float(north()->getExtraHeight() / float(totalExtraHeight))));
                south()->shrinkHeight(reduction * (float(south()->getExtraHeight() / float(totalExtraHeight))));

                centre()->shrinkToHeight(rowHeight - (reduction * (float(rowExtraHeight) / float(totalExtraHeight))));
                east()->shrinkToHeight(  rowHeight - (reduction * (float(rowExtraHeight)   / float(totalExtraHeight))));
                west()->shrinkToHeight(  rowHeight - (reduction * (float(rowExtraHeight)   / float(totalExtraHeight))));

                rowHeight   = std::max(east()->getHeight(), std::max(centre()->getHeight(), west()->getHeight()));
                totalHeight = north()->getHeight() + south()->getHeight() + rowHeight;

                // TODO optimise and neaten this
                if(totalHeight - size.y == 2) {
                    if(north()->getHeight() > 0) {
                        north()->shrinkHeight(1);
                        totalHeight--;

                        if(south()->getHeight() > 0) {
                            south()->shrinkHeight(1);
                            totalHeight--;
                        } else if(centre()->getHeight() > 0) {
                            centre()->shrinkToHeight(rowHeight - 1);
                            east()->shrinkToHeight(  rowHeight - 1);
                            west()->shrinkToHeight(  rowHeight - 1);
                            totalHeight--;
                            rowHeight--;
                        } else {
                            north()->shrinkHeight(1);
                            totalHeight--;
                        }
                    } else if(south()->getHeight() > 0) {
                        south()->shrinkHeight(1);
                        totalHeight--;

                        if(centre()->getHeight() > 0) {
                            centre()->shrinkToHeight(rowHeight - 1);
                            east()->shrinkToHeight(  rowHeight - 1);
                            west()->shrinkToHeight(  rowHeight - 1);
                            totalHeight--;
                            rowHeight--;
                        }
                    } else {
                        centre()->shrinkToHeight(rowHeight - 2);
                        east()->shrinkToHeight(  rowHeight - 2);
                        west()->shrinkToHeight(  rowHeight - 2);
                        totalHeight -= 2;
                        rowHeight   -= 2;
                    }
                } else if(totalHeight - size.y == 1) {
                    if(north()->getHeight() > 0) {
                        north()->shrinkHeight(1);
                        totalHeight--;
                    } else if(south()->getHeight() > 0) {
                        south()->shrinkHeight(1);
                        totalHeight--;
                    } else {
                        centre()->shrinkToHeight(rowHeight - 1);
                        east()->shrinkToHeight(  rowHeight - 1);
                        west()->shrinkToHeight(  rowHeight - 1);
                        totalHeight--;
                        rowHeight--;
                    }
                }
            } else {
                // Set to mins // TODO should have function to minimise component heights
                north()->shrinkToHeight(north()->getMinHeight());
                south()->shrinkToHeight(south()->getMinHeight());

                centre()->shrinkToHeight(rowMinHeight);
                east()->shrinkToHeight(  rowMinHeight);
                west()->shrinkToHeight(  rowMinHeight);

                // Set to below mins (proportionally)
                rowHeight   = std::max(east()->getHeight(), std::max(centre()->getHeight(), west()->getHeight()));
                totalHeight = north()->getHeight() + south()->getHeight() + rowHeight;

                const int reduction = totalHeight - size.y;

                north()->shrinkHeight(reduction * (float(north()->getHeight() / float(totalHeight))));
                south()->shrinkHeight(reduction * (float(south()->getHeight() / float(totalHeight))));

                centre()->shrinkToHeight(rowHeight - (reduction * (float(centre()->getHeight()) / float(totalHeight))));
                east()->shrinkToHeight(  rowHeight - (reduction * (float(east()->getHeight())   / float(totalHeight))));
                west()->shrinkToHeight(  rowHeight - (reduction * (float(west()->getHeight())   / float(totalHeight))));

                rowHeight   = std::max(east()->getHeight(), std::max(centre()->getHeight(), west()->getHeight()));
                totalHeight = north()->getHeight() + south()->getHeight() + rowHeight;
            }
        }

        centre()->proposeWidth(size.x);
        east()->proposeWidth(  size.x);
        west()->proposeWidth(  size.x);

        int rowWidth      = east()->getWidth() + centre()->getWidth() + west()->getWidth();
        int rowMinWidth   = east()->getMinWidth() + centre()->getMinWidth() + west()->getMinWidth();
        int rowExtraWidth = std::max(0, rowWidth - rowMinWidth);

        if(rowWidth < size.x) {
            // TODO properly comment this later
            // TODO optimise this, no energy rn
            // Expand the width of centre and east/west
            centre()->growToWidth(size.x - east()->getWidth() - west()->getWidth());
            rowWidth = east()->getWidth() + centre()->getWidth() + west()->getWidth();

            east()->growWidth(((size.x - rowWidth) + 1) / 2);
            rowWidth = east()->getWidth() + centre()->getWidth() + west()->getWidth();

            west()->growWidth(size.x - rowWidth);
            rowWidth = east()->getWidth() + centre()->getWidth() + west()->getWidth();

            east()->growWidth(size.x - rowWidth);
            rowWidth = east()->getWidth() + centre()->getWidth() + west()->getWidth();
        } else if(rowWidth > size.x) {
            if(rowWidth - rowExtraWidth > size.x) {
                // Remove proportionally
                // TODO implement this
            } else {
                // Set to mins

                // Reduce below mins (proportionally)

                // TODO implement this

            }
        }

        north()->setXPos(pos.x + ((size.x - north()->getWidth()) / 2));
        north()->setYPos((pos.y + size.y) - north()->getHeight());

        south()->setXPos(pos.x + ((size.x - south()->getWidth()) / 2));
        south()->setYPos(pos.y);

        east()->setXPos(pos.x + size.x - east()->getWidth());
        east()->setYPos(pos.y + south()->getHeight() + ((rowHeight - east()->getHeight()) / 2));

        west()->setXPos(pos.x);
        west()->setYPos(pos.y + south()->getHeight() + ((rowHeight - west()->getHeight()) / 2));

        centre()->setXPos(pos.x + west()->getWidth() + ((rowWidth - east()->getWidth() - west()->getWidth() - centre()->getWidth()) / 2));
        centre()->setYPos(pos.y + south()->getHeight() + ((rowHeight - centre()->getHeight()) / 2));
    } else {
        // TODO implement this
    }
}

void NLUI::BorderPane::setComponent(const Position &pos, const std::shared_ptr<Component> &component) {
    if(component == nullptr) {
        setComponent(pos, NullComponent::getInstance());
    } else {
        const std::shared_ptr<Component> copy = components[pos];

        if(focus == copy) {
            focus = nullptr;
        }

        component->setParent(this);
        components[pos] = component;
        copy->removeParent();

        layoutRoot();
    }
}

void NLUI::BorderPane::setCentre(const std::shared_ptr<Component> &component) {
    setComponent(Position::CENTRE, component);
}

void NLUI::BorderPane::setNorth(const std::shared_ptr<Component> &component) {
    setComponent(Position::NORTH, component);
}

void NLUI::BorderPane::setSouth(const std::shared_ptr<Component> &component) {
    setComponent(Position::SOUTH, component);
}

void NLUI::BorderPane::setEast(const std::shared_ptr<Component> &component) {
    setComponent(Position::EAST, component);
}

void NLUI::BorderPane::setWest(const std::shared_ptr<Component> &component) {
    setComponent(Position::WEST, component);
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