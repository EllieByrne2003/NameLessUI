#include "boxPane.hpp"
#include <memory>

// Includes from standard


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
    // TODO implement this
}

void NLUI::BoxPane::addComponent(const std::shared_ptr<Component> &component) {
    component->setParent(this);
    components.push_back(component);

    layoutRoot();
}