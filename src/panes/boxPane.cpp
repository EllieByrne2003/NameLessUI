#include "boxPane.hpp"

// Includes from standard
#include <memory>

// Includes from third party libraries


// Includes from personal libraries


// Includes from project


// Forward declarations


// Type aliases


NLUI::BoxPane::BoxPane(const bool horizontal, const glm::ivec2 &minSize, const glm::ivec2 &maxSize) : Pane(minSize, maxSize),
    horizontal(horizontal) {

}

NLUI::BoxPane::~BoxPane() {
}

std::shared_ptr<NLUI::BoxPane> NLUI::BoxPane::create(const bool horizontal, const glm::ivec2 &minSize, const glm::ivec2 &maxSize) {
    return std::shared_ptr<BoxPane>(new BoxPane(horizontal, minSize, maxSize));
}

void NLUI::BoxPane::draw() const {
    Pane::draw();

    for(const std::shared_ptr<const Component> &component : components) {
        component->draw();
    }
}

void NLUI::BoxPane::getPrefSize(int &prefWidth, int &prefHeight) const {
    if(horizontal) {
        int sumPrefWidth       = 0;
        int greatestPrefHeight = 0;
        for(const std::shared_ptr<Component> &comp : components) {
            const glm::ivec2 compPrefSize = comp->getPrefSize();

            sumPrefWidth       += compPrefSize.x;
            greatestPrefHeight  = std::max(greatestPrefHeight, compPrefSize.y);
        }

        prefWidth  = sumPrefWidth;
        prefHeight = greatestPrefHeight;
    } else {
        int greatestPrefWidth = 0;
        int sumPrefHeight     = 0;

        for(const std::shared_ptr<Component> &comp : components) {
            const glm::ivec2 compPrefSize = comp->getPrefSize();

            greatestPrefWidth  = std::max(greatestPrefWidth, compPrefSize.x);
            sumPrefHeight     += compPrefSize.y;
        }

        prefWidth  = greatestPrefWidth;
        prefHeight = sumPrefHeight;
    }
}

glm::ivec2 NLUI::BoxPane::getPrefSize() const {
    if(horizontal) {
        int sumPrefWidth       = 0;
        int greatestPrefHeight = 0;
        for(const std::shared_ptr<Component> &comp : components) {
            const glm::ivec2 compPrefSize = comp->getPrefSize();

            sumPrefWidth       += compPrefSize.x;
            greatestPrefHeight  = std::max(greatestPrefHeight, compPrefSize.y);
        }

        return glm::ivec2(sumPrefWidth, greatestPrefHeight);
    } else {
        int greatestPrefWidth = 0;
        int sumPrefHeight     = 0;

        for(const std::shared_ptr<Component> &comp : components) {
            const glm::ivec2 compPrefSize = comp->getPrefSize();

            greatestPrefWidth  = std::max(greatestPrefWidth, compPrefSize.x);
            sumPrefHeight     += compPrefSize.y;
        }

        return glm::ivec2(greatestPrefWidth, sumPrefHeight);
    }
}

int NLUI::BoxPane::getPrefWidth() const {
    if(horizontal) {
        int sumPrefWidth       = 0;
        for(const std::shared_ptr<Component> &comp : components) {
            sumPrefWidth += comp->getPrefWidth();
        }

        return sumPrefWidth;
    } else {
        int greatestPrefWidth = 0;

        for(const std::shared_ptr<Component> &comp : components) {
            greatestPrefWidth = std::max(greatestPrefWidth, comp->getPrefWidth());
        }

        return greatestPrefWidth;
    }
}

int NLUI::BoxPane::getPrefHeight() const {
    if(horizontal) {
        int greatestPrefHeight = 0;
        for(const std::shared_ptr<Component> &comp : components) {
            greatestPrefHeight = std::max(greatestPrefHeight, comp->getPrefHeight());
        }

        return greatestPrefHeight;
    } else {
        int sumPrefHeight     = 0;

        for(const std::shared_ptr<Component> &comp : components) {
            sumPrefHeight += comp->getPrefHeight();
        }

        return sumPrefHeight;
    }
}

void NLUI::BoxPane::getMinSize(int &minWidth, int &minHeight) const {
    if(horizontal) {
        int sumMinWidth       = 0;
        int greatestMinHeight = 0;
        for(const std::shared_ptr<Component> &comp : components) {
            const glm::ivec2 compMinSize = comp->getMinSize();

            sumMinWidth       += compMinSize.x;
            greatestMinHeight  = std::max(greatestMinHeight, compMinSize.y);
        }

        minWidth  = std::max(minSize.x, sumMinWidth);
        minHeight = std::max(minSize.y, greatestMinHeight);
    } else {
        int greatestMinWidth = 0;
        int sumMinHeight     = 0;

        for(const std::shared_ptr<Component> &comp : components) {
            const glm::ivec2 compMinSize = comp->getMinSize();

            greatestMinWidth  = std::max(greatestMinWidth, compMinSize.x);
            sumMinHeight     += compMinSize.y;
        }

        minWidth  = std::max(minSize.x, greatestMinWidth);
        minHeight = std::max(minSize.y, sumMinHeight);
    }
}

glm::ivec2 NLUI::BoxPane::getMinSize() const {
    if(horizontal) {
        int sumMinWidth       = 0;
        int greatestMinHeight = 0;
        for(const std::shared_ptr<Component> &comp : components) {
            const glm::ivec2 compMinSize = comp->getMinSize();

            sumMinWidth       += compMinSize.x;
            greatestMinHeight  = std::max(greatestMinHeight, compMinSize.y);
        }

        return glm::ivec2(std::max(minSize.x, sumMinWidth), std::max(minSize.y, greatestMinHeight));
    } else {
        int greatestMinWidth = 0;
        int sumMinHeight     = 0;

        for(const std::shared_ptr<Component> &comp : components) {
            const glm::ivec2 compMinSize = comp->getMinSize();

            greatestMinWidth  = std::max(greatestMinWidth, compMinSize.x);
            sumMinHeight     += compMinSize.y;
        }

        return glm::ivec2(std::max(minSize.x, greatestMinWidth), std::max(minSize.y, sumMinHeight));
    }
}

int NLUI::BoxPane::getMinWidth() const {
    if(horizontal) {
        int sumMinWidth       = 0;
        for(const std::shared_ptr<Component> &comp : components) {
            sumMinWidth += comp->getMinWidth();
        }

        return std::max(minSize.x, sumMinWidth);
    } else {
        int greatestMinWidth = 0;

        for(const std::shared_ptr<Component> &comp : components) {
            greatestMinWidth = std::max(greatestMinWidth, comp->getMinWidth());
        }

        return std::max(minSize.x, greatestMinWidth);
    }
}

int NLUI::BoxPane::getMinHeight() const {
    if(horizontal) {
        int greatestMinHeight = 0;
        for(const std::shared_ptr<Component> &comp : components) {
            greatestMinHeight = std::max(greatestMinHeight, comp->getMinHeight());
        }

        return std::max(minSize.y, greatestMinHeight);
    } else {
        int sumMinHeight     = 0;

        for(const std::shared_ptr<Component> &comp : components) {
            sumMinHeight += comp->getMinHeight();
        }

        return std::max(minSize.y, sumMinHeight);
    }
}

void NLUI::BoxPane::getMaxSize(int &maxWidth, int &maxHeight) const {
    if(horizontal) {
        int sumMaxWidth       = 0;
        int greatestMaxHeight = 0;
        for(const std::shared_ptr<Component> &comp : components) {
            const glm::ivec2 compMaxSize = comp->getMaxSize();

            sumMaxWidth       += compMaxSize.x;
            greatestMaxHeight  = std::max(greatestMaxHeight, compMaxSize.y);
        }

        maxWidth  = std::min(maxSize.x, sumMaxWidth);
        maxHeight = std::min(maxSize.y, greatestMaxHeight);
    } else {
        int greatestMaxWidth = 0;
        int sumMaxHeight     = 0;

        for(const std::shared_ptr<Component> &comp : components) {
            const glm::ivec2 compMaxSize = comp->getMaxSize();

            greatestMaxWidth  = std::max(greatestMaxWidth, compMaxSize.x);
            sumMaxHeight     += compMaxSize.y;
        }

        maxWidth  = std::min(maxSize.x, greatestMaxWidth);
        maxHeight = std::min(maxSize.y, sumMaxHeight);
    }
}

glm::ivec2 NLUI::BoxPane::getMaxSize() const {
    if(horizontal) {
        int sumMaxWidth       = 0;
        int greatestMaxHeight = 0;
        for(const std::shared_ptr<Component> &comp : components) {
            const glm::ivec2 compMaxSize = comp->getMaxSize();

            sumMaxWidth       += compMaxSize.x;
            greatestMaxHeight  = std::max(greatestMaxHeight, compMaxSize.y);
        }

        return glm::ivec2(std::max(maxSize.x, sumMaxWidth), std::max(maxSize.y, greatestMaxHeight));
    } else {
        int greatestMaxWidth = 0;
        int sumMaxHeight     = 0;

        for(const std::shared_ptr<Component> &comp : components) {
            const glm::ivec2 compMaxSize = comp->getMaxSize();

            greatestMaxWidth  = std::max(greatestMaxWidth, compMaxSize.x);
            sumMaxHeight     += compMaxSize.y;
        }

        return glm::ivec2(std::min(maxSize.x, greatestMaxWidth), std::min(maxSize.y, sumMaxHeight));
    }
}

int NLUI::BoxPane::getMaxWidth() const {
    if(horizontal) {
        int sumMaxWidth       = 0;
        for(const std::shared_ptr<Component> &comp : components) {
            sumMaxWidth += comp->getMaxWidth();
        }

        return std::min(maxSize.x, sumMaxWidth);
    } else {
        int greatestMaxWidth = 0;

        for(const std::shared_ptr<Component> &comp : components) {
            greatestMaxWidth = std::max(greatestMaxWidth, comp->getMaxWidth());
        }

        return std::min(maxSize.x, greatestMaxWidth);
    }
}

int NLUI::BoxPane::getMaxHeight() const {
    if(horizontal) {
        int greatestMaxHeight = 0;
        for(const std::shared_ptr<Component> &comp : components) {
            greatestMaxHeight = std::max(greatestMaxHeight, comp->getMaxHeight());
        }

        return std::min(maxSize.y, greatestMaxHeight);
    } else {
        int sumMaxHeight     = 0;

        for(const std::shared_ptr<Component> &comp : components) {
            sumMaxHeight += comp->getMaxHeight();
        }

        return std::min(maxSize.y, sumMaxHeight);
    }
}

bool NLUI::BoxPane::mouseInside(const double xPos, const double yPos) {
    if(Pane::mouseInside(xPos, yPos)) {
        for(const std::shared_ptr<Component> &component : components) {
            if(component->mouseInside(xPos, yPos)) {
                focus = component;
                break; // Can only be one anyways
            }
        }

        return true;
    } else {
        return false;
    }
}

void NLUI::BoxPane::removeComponent(const std::shared_ptr<Component> &component) {
    if(component == nullptr) {
        return;
    }

    // Find its position (if it has one)
    std::vector<std::shared_ptr<Component>>::iterator pos = std::find(components.begin(), components.end(), component);

    // If present remove it
    if(pos != components.end()) {
        std::shared_ptr<Component> copy = *pos; // Stops delete from being called on component

        if(focus == copy) {
            focus = nullptr;
        }
    
        components.erase(pos);
        copy->removeParent();

        layoutRoot();
    }
}

void NLUI::BoxPane::removeComponent(Component *const component) {
    if(component == nullptr) {
        return;
    }
    
    // Find its position (if it has one)
    std::vector<std::shared_ptr<Component>>::iterator pos = std::find_if(components.begin(), components.end(), 
        [component](const std::shared_ptr<Component> &ptr) { return ptr.get() == component; }
    );

    // If present remove it
    if(pos != components.end()) {
        std::shared_ptr<Component> copy = *pos; // Stops delete from being called on component

        if(focus == copy) {
            focus = nullptr;
        }
    
        components.erase(pos);
        copy->removeParent();

        layoutRoot();
    }
}

void NLUI::BoxPane::doLayout() {
    // Propose current size to each
    for(std::shared_ptr<Component> &comp : components) {
        comp->proposeSize(size);
    }

    if(horizontal) {
        int totalWidth    = 0;
        int totalMinWidth = 0;
        int totalMaxWidth = 0;

        for(std::shared_ptr<Component> &comp : components) {
            // Reduce heights to height, if needed
            if(comp->getHeight() > size.y) {
                comp->shrinkToHeight(size.y);
            }

            totalWidth    += comp->getWidth();
            totalMinWidth += comp->getMinWidth();
            totalMaxWidth += comp->getMaxWidth();
        }

        int totalExtraWidth  = std::max(0, totalWidth - totalMinWidth);
        int totalGrowthWidth = std::max(0, totalMaxWidth - totalWidth);

        if(totalWidth < size.x) {
            const int increase          = std::min(size.x - totalWidth, totalGrowthWidth);
            const int totalGrowthBefore = totalGrowthWidth;

            // Increase to max or to fill space proportionally
            for(std::shared_ptr<Component> &comp : components) {
                const int compGrowthWidth = comp->getGrowthWidth();

                const int incWidth = increase * (float(compGrowthWidth) / float(totalGrowthBefore));

                comp->growWidth(incWidth);
                totalWidth       += incWidth;
                totalGrowthWidth -= incWidth;
            }

            // Increase comp wioth largest growth until fit (or no more growthWidth)
            while(totalWidth < size.x && totalGrowthWidth > 0) {
                // Get greatest width growth
                int greatestGrowthCompIndex = 0;
                int greatestGrowth = components[0]->getGrowthWidth();

                for(int i = 1; i < components.size(); i++) {
                    const std::shared_ptr<NLUI::Component> &comp = components[i];
                    const int compGrowth = comp->getGrowthWidth();

                    if(greatestGrowth < compGrowth) {
                        greatestGrowthCompIndex = i;
                        greatestGrowth = compGrowth;
                    }
                }

                components[greatestGrowthCompIndex]->growWidth(1);
                totalWidth++;
                totalGrowthWidth--;
            }
        } else if(totalWidth > size.x) {
            if(totalWidth - totalExtraWidth <= size.x) {
                // Remove proporitonally
                const int decrease = totalWidth - size.x;
                for(std::shared_ptr<Component> &comp : components) {
                    const int compExtraWidth = comp->getExtraWidth();

                    const int decWidth = decrease * (float(compExtraWidth) / float(totalGrowthWidth));

                    comp->shrinkWidth(decWidth);
                    totalWidth -= decWidth;
                }

                // remove 1 from row with largest extra width
                while(totalWidth > size.x) {
                    // Get largest extra width
                    int greatestExtraCompIndex = 0;
                    int greatestExtra = components[0]->getExtraWidth();

                    for(int i = 1; i < components.size(); i++) {
                        const std::shared_ptr<NLUI::Component> &comp = components[i];
                        const int compExtra = comp->getExtraWidth();

                        if(greatestExtra < compExtra) {
                            greatestExtraCompIndex = i;
                            greatestExtra = compExtra;
                        }
                    }

                    components[greatestExtraCompIndex]->shrinkWidth(1);
                    totalWidth--;
                }
            } else {
                // Set to mins // TODO should have function to minimise row widths
                for(std::shared_ptr<Component> &comp : components) {
                    const int decWidth = comp->getExtraWidth();

                    comp->shrinkWidth(decWidth);
                    totalWidth -= decWidth;
                }

                // Set to below mins (proportionally)
                const int decrease    = totalWidth - size.x;
                const int totalBefore = totalWidth;
                for(std::shared_ptr<Component> &comp : components) {
                    const int compWidth = comp->getWidth();

                    const int decWidth = decrease * (float(compWidth) / float(totalBefore));

                    comp->shrinkWidth(decWidth);
                    totalWidth -= decWidth;
                }

                // Reduce largest width by one until fit
                while(totalWidth > size.x) {
                    // Get largest width
                    int greatestWidthCompIndex = 0;
                    int greatestWidth = components[0]->getWidth();

                    for(int i = 1; i < components.size(); i++) {
                        const std::shared_ptr<NLUI::Component> &comp = components[i];
                        const int compWidth = comp->getWidth();

                        if(greatestWidth < compWidth) {
                            greatestWidthCompIndex = i;
                            greatestWidth = compWidth;
                        }
                    }

                    components[greatestWidthCompIndex]->shrinkWidth(1);
                    totalWidth--;
                }
            }
        }

        int x = pos.x + ((size.x - totalWidth) / 2);
        int y = pos.y;
        for(std::shared_ptr<Component> &comp : components) {
            const int offset = (size.y - comp->getHeight()) / 2;

            comp->setPos(x, y + offset);

            x += comp->getWidth();
        }
    } else {
        int totalHeight    = 0;
        int totalMinHeight = 0;
        int totalMaxHeight = 0;

        for(std::shared_ptr<Component> &comp : components) {
            // Reduce heights to height, if needed
            if(comp->getWidth() > size.x) {
                comp->shrinkToWidth(size.x);
            }

            totalHeight    += comp->getHeight();
            totalMinHeight += comp->getMinHeight();
            totalMaxHeight += comp->getMaxHeight();
        }

        int totalExtraHeight  = std::max(0, totalHeight - totalMinHeight);
        int totalGrowthHeight = std::max(0, totalMaxHeight - totalHeight);

        if(totalHeight < size.y) {
            const int increase          = std::min(size.y - totalHeight, totalGrowthHeight);
            const int totalGrowthBefore = totalGrowthHeight;

            // Increase to max or to fill space proportionally
            for(std::shared_ptr<Component> &comp : components) {
                const int compGrowthHeight = comp->getGrowthHeight();

                const int incHeight = increase * (float(compGrowthHeight) / float(totalGrowthBefore));

                comp->growHeight(incHeight);
                totalHeight       += incHeight;
                totalGrowthHeight -= incHeight;
            }

            // Increase comp wioth largest growth until fit (or no more growthHeight)
            while(totalHeight < size.y && totalGrowthHeight > 0) {
                // Get greatest height growth
                int greatestGrowthCompIndex = 0;
                int greatestGrowth = components[0]->getGrowthHeight();

                for(int i = 1; i < components.size(); i++) {
                    const std::shared_ptr<NLUI::Component> &comp = components[i];
                    const int compGrowth = comp->getGrowthHeight();

                    if(greatestGrowth < compGrowth) {
                        greatestGrowthCompIndex = i;
                        greatestGrowth = compGrowth;
                    }
                }

                components[greatestGrowthCompIndex]->growHeight(1);
                totalHeight++;
                totalGrowthHeight--;
            }
        } else if(totalHeight > size.y) {
            if(totalHeight - totalExtraHeight <= size.y) {
                // Remove proporitonally
                const int decrease = totalHeight - size.y;
                for(std::shared_ptr<Component> &comp : components) {
                    const int compExtraHeight = comp->getExtraHeight();

                    const int decHeight = decrease * (float(compExtraHeight) / float(totalGrowthHeight));

                    comp->shrinkHeight(decHeight);
                    totalHeight -= decHeight;
                }

                // remove 1 from row with largest extra height
                while(totalHeight > size.y) {
                    // Get largest extra height
                    int greatestExtraCompIndex = 0;
                    int greatestExtra = components[0]->getExtraHeight();

                    for(int i = 1; i < components.size(); i++) {
                        const std::shared_ptr<NLUI::Component> &comp = components[i];
                        const int compExtra = comp->getExtraHeight();

                        if(greatestExtra < compExtra) {
                            greatestExtraCompIndex = i;
                            greatestExtra = compExtra;
                        }
                    }

                    components[greatestExtraCompIndex]->shrinkHeight(1);
                    totalHeight--;
                }
            } else {
                // Set to mins // TODO should have function to minimise row heights
                for(std::shared_ptr<Component> &comp : components) {
                    const int decHeight = comp->getExtraHeight();

                    comp->shrinkHeight(decHeight);
                    totalHeight -= decHeight;
                }

                // Set to below mins (proportionally)
                const int decrease    = totalHeight - size.y;
                const int totalBefore = totalHeight;
                for(std::shared_ptr<Component> &comp : components) {
                    const int compHeight = comp->getHeight();

                    const int decHeight = decrease * (float(compHeight) / float(totalBefore));

                    comp->shrinkHeight(decHeight);
                    totalHeight -= decHeight;
                }

                // Reduce largest height by one until fit
                while(totalHeight > size.y) {
                    // Get largest height
                    int greatestHeightCompIndex = 0;
                    int greatestHeight = components[0]->getHeight();

                    for(int i = 1; i < components.size(); i++) {
                        const std::shared_ptr<NLUI::Component> &comp = components[i];
                        const int compHeight = comp->getHeight();

                        if(greatestHeight < compHeight) {
                            greatestHeightCompIndex = i;
                            greatestHeight = compHeight;
                        }
                    }

                    components[greatestHeightCompIndex]->shrinkHeight(1);
                    totalHeight--;
                }
            }
        }

        int x = pos.x;
        int y = pos.y + ((size.y + totalHeight) / 2);
        for(std::shared_ptr<Component> &comp : components) {
            const int offset = (size.x - comp->getWidth()) / 2;
            y -= comp->getHeight();

            comp->setPos(x + offset, y);
        }

    }
}

void NLUI::BoxPane::addComponent(const std::shared_ptr<Component> &component) {
    component->setParent(this);
    components.push_back(component);

    layoutRoot();
}