#include "flowPane.hpp"

// Includes from standard
#include <algorithm>
#include <vector>

// Includes from third party libraries
#include <glm/glm.hpp>
using namespace glm;

// Includes from personal libraries


// Includes from project


// Forward declarations


// Type aliases



NLUI::FlowPane::FlowPane() {

}

NLUI::FlowPane::~FlowPane() {
    for(const Component *const component : components) {
        delete component;
    }
}

void NLUI::FlowPane::draw() const {
    Pane::draw();

    for(const Component *const component : components) {
        component->draw();
    }
}

void NLUI::FlowPane::getMinimumSize(int &minimumWidth, int &minimumHeight) const {
    minimumWidth  = getMinimumWidth();
    minimumHeight = getMinimumHeight();
}

ivec2 NLUI::FlowPane::getMinimumSize() const {
    return ivec2(getMinimumWidth(), getMinimumHeight());
}

int NLUI::FlowPane::getMinimumWidth() const {
    int minimumWidth = 0;

    if(orientation == Orientation::Horizontal) {
        // Largest of sums
        for(const Component *const component : components) {
            const int componentMinimumWidth = component->getMinimumWidth();

            if(componentMinimumWidth > minimumWidth) {
                minimumWidth = componentMinimumWidth;
            }
        }
    } else if (orientation == Orientation::Vertical) {
        // When in vertical, the minimum width depends on the minimum height
        const int minimumHeight = getMinimumHeight();

        // Simulate making rows
        int currentColumnHeight    = 0;
        int currentColumnMaxWidth  = 0;

        for(const Component *const component : components) {
            const ivec2 componentMinimumSize = component->getMinimumSize();

            if(currentColumnHeight + componentMinimumSize.y > minimumHeight) {
                minimumWidth          += currentColumnMaxWidth;
                currentColumnHeight    = 0;
                currentColumnMaxWidth  = 0;
            }

            currentColumnHeight   += componentMinimumSize.y;
            currentColumnMaxWidth  = std::max(currentColumnMaxWidth, componentMinimumSize.x);
        }

        minimumWidth += currentColumnMaxWidth;
    
    } else {
        // TODO throw some error? Maybe?
    }

    // Use the set minimum if it is greater
    const int baseMinimumWidth = Pane::getMinimumWidth();
    if(baseMinimumWidth > minimumWidth) {
        return baseMinimumWidth;
    } else {
        return minimumWidth;
    }
}

int NLUI::FlowPane::getMinimumHeight() const {
    int minimumHeight = 0;

    if(orientation == Orientation::Horizontal) {
        // When in horizontal, the minimum height depends on the minimum width
        const int minimumWidth = getMinimumWidth();

        // Simulate making rows
        int currentRowWidth         = 0;
        int currentRowMaximumHeight = 0;

        for(const Component *const component : components) {
            const ivec2 componentMinimumSize = component->getMinimumSize();

            if(currentRowWidth + componentMinimumSize.x > minimumWidth) {
                minimumHeight           += currentRowMaximumHeight;
                currentRowWidth          = 0;
                currentRowMaximumHeight  = 0;
            }

            currentRowWidth         += componentMinimumSize.x;
            currentRowMaximumHeight  = std::max(currentRowMaximumHeight, componentMinimumSize.y);
        }

        minimumHeight += currentRowMaximumHeight;
    } else if (orientation == Orientation::Vertical) {
        // Largest of sums
        for(const Component *const component : components) {
            const int componentMinimumHeight = component->getMinimumHeight();

            if(componentMinimumHeight > minimumHeight) {
                minimumHeight = componentMinimumHeight;
            }
        }
    } else {
        // TODO throw some error? Maybe?
    }

    // Use the set minimum if it is greater
    const int baseMinimumHeight = Pane::getMinimumHeight();
    if(baseMinimumHeight > minimumHeight) {
        return baseMinimumHeight;
    } else {
        return minimumHeight;
    }
}

// void NLUI::FlowPane::getPreferredSize(const int availableWidth, const int availableHeight, int &preferredWidth, int &preferredHeight) const {
//     preferredWidth  = getPreferredWidth(availableWidth);
//     preferredHeight = getPreferredHeight(availableHeight);
// }

// ivec2 NLUI::FlowPane::getPreferredSize(const int availableWidth, const int availableHeight) const {
//     return ivec2(getPreferredWidth(availableWidth), getPreferredHeight(availableHeight));
// }

// void NLUI::FlowPane::getPreferredSize(const ivec2 &availableSize, int &preferredWidth, int &preferredHeight) const {
//     preferredWidth  = getPreferredWidth(availableSize.x);
//     preferredHeight = getPreferredHeight(availableSize.y);
// }

// ivec2 NLUI::FlowPane::getPreferredSize(const ivec2 &availableSize) const {
//     return ivec2(getPreferredWidth(availableSize.x), getPreferredHeight(availableSize.y));
// }

// int NLUI::FlowPane::getPreferredWidth(const int availableWidth) const {
//     return availableWidth; // TODO have a flag to decide whether to fill all space or just add up components answers
// }

// int NLUI::FlowPane::getPreferredHeight(const int availableHeight) const {
//     return availableHeight; // TODO have a flag to decide whether to fill all space or just add up components answers
// }

void NLUI::FlowPane::getPreferredSize(int &preferredWidth, int &preferredHeight) const {
    preferredWidth  = getPreferredWidth();
    preferredHeight = getPreferredHeight();
}

ivec2 NLUI::FlowPane::getPreferredSize() const {
    const int preferredWidth  = getPreferredWidth();
    const int preferredHeight = getPreferredHeight();

    return ivec2(preferredWidth, preferredHeight);
}

int NLUI::FlowPane::getPreferredWidth() const {
    int preferredWidth = 0;

    if(orientation == Orientation::Horizontal) {
        // Sum of components
        for(const Component *const component : components) {
            preferredWidth += component->getPreferredWidth();
        }
    } else if(orientation == Orientation::Vertical) {
        // Largest of components
        for(const Component *const component : components) {
            const int componentPreferredWidth = component->getPreferredWidth();

            if(componentPreferredWidth > preferredWidth) {
                preferredWidth = componentPreferredWidth;
            }
        }
    } else {
        // TODO throw some error? Maybe?
    }

    return preferredWidth;
}

int NLUI::FlowPane::getPreferredHeight() const {
    int preferredHeight = 0;

    if(orientation == Orientation::Horizontal) {
        // Largest of components
        for(const Component *const component : components) {
            const int componentPreferredHeight = component->getPreferredHeight();

            if(componentPreferredHeight > preferredHeight) {
                preferredHeight = componentPreferredHeight;
            }
        }
    } else if(orientation == Orientation::Vertical) {
        // Sum of components
        for(const Component *const component : components) {
            preferredHeight += component->getPreferredHeight();
        }
    } else {
        // TODO throw some error? Maybe?
    }

    return preferredHeight;
}

void NLUI::FlowPane::resize() {
    const ivec2 currentSize   = getSize(); 
    const ivec2 preferredSize = getPreferredSize();

    // Set sizes
    bool useMinimum = preferredSize.x > currentSize.x || preferredSize.y > currentSize.y;
    for(Component *const component : components) {
        if(useMinimum) {
            component->setSize(component->getMinimumSize());
        } else {
            component->setSize(component->getPreferredSize());
        }
    }

    const ivec2 currentPos = getPos();
    const int  &x          = currentPos.x;
    const int  &y          = currentPos.y;

    // Arrange in rows/columns
    if(orientation == Orientation::Horizontal) {
        std::vector<std::pair<std::vector<Component *>, int>> rows = { { { }, 0 } }; // Load with empty row

        int currentRowWidth = 0;
        for(Component *const component : components) {
            // Skip to next row if not enough width available
            if(currentRowWidth + component->getWidth() > currentSize.x) {
                currentRowWidth = 0;
                rows.push_back({ { }, 0 });
            }

            // Give component it's x value
            component->setXPos(x + currentRowWidth);

            // Add current component to currentRow, adjust values
            std::pair<std::vector<Component *>, int> &currentRow = rows.back();
            currentRow.first.push_back(component);

            currentRow.second  = std::max(currentRow.second, component->getHeight());
            currentRowWidth   += component->getWidth();
        }

        // Set y positions
        int currentHeight = currentSize.y;
        for(std::pair<std::vector<Component *>, int> &row : rows) {
            currentHeight -= row.second;

            for(Component *const component : row.first) {
                component->setYPos(y + currentHeight);
            }
        }
    } else if(orientation == Orientation::Vertical) {
        std::vector<std::pair<std::vector<Component *>, int>> columns = { { { }, 0 } }; // Load with empty row

        int currentColumnHeight = currentSize.y;
        for(Component *const component : components) {
            // Skip to next column if not enough height available
            if(currentColumnHeight - component->getHeight() < 0) {
                currentColumnHeight = currentSize.x;
                columns.push_back({ { }, 0 });
            }

            // Give component it's y value
            component->setYPos(y + currentColumnHeight);

            // Add current component to currentColumn, adjust values
            std::pair<std::vector<Component *>, int> &currentColumn = columns.back();
            currentColumn.first.push_back(component);

            currentColumn.second  = std::max(currentColumn.second, component->getWidth());
            currentColumnHeight  -= component->getHeight();
        }

        // Set x positions
        int currentWidth = 0;
        for(std::pair<std::vector<Component *>, int> &column : columns) {
            for(Component *const component : column.first) {
                component->setXPos(x + currentWidth);
            }

            currentWidth += column.second;
        }
    } else {
        // TODO throw some error? Maybe?
    }



    // if(orientation == Orientation::Horizontal) {
    //     // Set sizes to their minimums
    //     for(Component *const component : components) {
    //         component->setSize(component->getMinimumSize());
    //     }

    //     // Try to make rows out of them
    //     std::vector<std::pair<std::vector<Component *>, std::pair<int, int>>> rows;
    //     rows.push_back({ { }, { 0, 0 }});
    //     // int accumWidth  = 0;
    //     int accumHeight = 0;
    //     for(Component *const component : components) {
    //         const int compWidth  = component->getWidth();
    //         const int compHeight = component->getHeight();

    //         if(rows.back().second.first + compWidth <= this->getWidth()) {
    //             // There is space to place it here, add to current row
    //             rows.back().first.push_back(component);

    //             // Adjust the size here
    //             rows.back().second.first += compWidth;

    //             // If the new component increases height, handle it and increase accumHeight
    //             if(rows.back().second.second < compHeight) {
    //                 accumHeight += (compHeight - rows.back().second.second);
    //                 rows.back().second.second = compHeight;
    //             }
    //         } else {
    //             // No space in this row, make new one and reset accumWidth
    //             rows.push_back({ {component}, { compWidth, compHeight } });

    //             accumHeight += compHeight;
    //         }
    //     }

    //     // Try to fill all width in rows
    //     for(std::pair<std::vector<Component *>, std::pair<int, int>> &row : rows) {
    //         const int maxTries = 5;

    //         for(int tries = 0; tries < maxTries && row.second.first < this->getWidth(); tries++) {
    //             const int emptyWidth = this->getWidth() - row.second.first;

    //             // Try to give all space at once, the gradually sub-divide until the new size fits
    //             for(int i = 1; i <= row.first.size(); i++) {
    //                 int usedWidth = 0;
    //                 for(const Component *const component : row.first) {
    //                     usedWidth += component->getPreferredWidth(component->getWidth() + (emptyWidth / i));
    //                 }

    //                 // Space found, increase sizes
    //                 if(usedWidth <= this->getWidth()) {
    //                     for(Component *const component : row.first) {
    //                         component->setWidth(getPreferredWidth(component->getWidth() + (emptyWidth / i)));
    //                     }

    //                     row.second.first = usedWidth;
    //                     break; // Need to move onto next try
    //                 }
    //             }
    //         }
    //     }

    //     // Try to fill all height across it all
    //     const int maxTries = 5;
    //     for(int tries = 0; tries < maxTries && accumHeight < this->getHeight(); tries++) {
    //         const int emptyHeight = this->getHeight() - accumHeight;

    //         // Try to give all space at once, the gradually sub-divide until the new size fits
    //         for(int i = 1; i <= rows.size(); i++) {
    //             int usedHeight = 0;
    //             for(std::pair<std::vector<Component *>, std::pair<int, int>> &row : rows) {
    //                 int largestHeight = 0;

    //                 for(const Component *const component : row.first) {
    //                     if(component->getPreferredHeight(component->getHeight() + (emptyHeight / i)) > largestHeight) {
    //                         largestHeight = component->getPreferredHeight(component->getHeight() + (emptyHeight / i));
    //                     }
    //                 }

    //                 usedHeight += largestHeight;
    //             }

    //             // Space found, increase sizes
    //             if(usedHeight <= this->getHeight()) {
    //                 accumHeight = 0;

    //                 for(std::pair<std::vector<Component *>, std::pair<int, int>> &row : rows) {
    //                     for(Component *const component : row.first) {
    //                         component->setHeight(getPreferredHeight(component->getHeight() + (emptyHeight / i)));

    //                         if(component->getHeight() > row.second.second) {
    //                             row.second.second = component->getHeight();
    //                         }
    //                     }

    //                     accumHeight += row.second.second;
    //                 }

    //                 break; // Need to move onto next try
    //             }
    //         }
    //     }
        
    //     // Set positions
    //     int y = this->getHeight();
    //     for(std::pair<std::vector<Component *>, std::pair<int, int>> &row : rows) {
    //         y -= row.second.second;

    //         int x = 0;
    //         for(Component *const component : row.first) {
    //             component->setPos(x, y);
    //             x += component->getWidth();
    //         }
    //     }
    // } else if(orientation == Orientation::Vertical) {
    //     // Ignore please
    // }
}

bool NLUI::FlowPane::mouseInside(const double xPos, const double yPos) {
    if(Pane::mouseInside(xPos, yPos)) {
        for(Component *const component : components) {
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

void NLUI::FlowPane::addComponent(Component *component) {
    component->setParent(this);
    components.push_back(component);

    // Validate size and components
    validate();
}

void NLUI::FlowPane::removeComponent(Component *component) {
    // Find it's position (if it has one)
    std::vector<Component *>::iterator position = std::find(components.begin(), components.end(), component);
    
    // If present remove it
    if(position != components.end()) {
        // Best avoid passing events if the component could potentially be deleted
        if(focus == component) {
            focus = nullptr;
        }
    
        components.erase(position);
        component->removeParent();

        // Validate size and components
        validate();
    }
}

void NLUI::FlowPane::validate() {
    const ivec2 currentSize   = getSize(); 
    const ivec2 minimumSize   = getMinimumSize();
    const ivec2 preferredSize = getPreferredSize();

    // Check if we have all the space needed already
    bool fitMinimum   = minimumSize.x   <= currentSize.x && minimumSize.y   <= currentSize.y;
    bool fitPreferred = preferredSize.x <= currentSize.x && preferredSize.y <= currentSize.y;

    // Can't fit, inform parent
    if(!fitMinimum && !fitPreferred) {
        validateParent();
    } else {
        // Fits but maybe the child components need more space
        for(const Component *const component : components) {
            const ivec2 compCurrentSize   = component->getSize(); 
            const ivec2 compMinimumSize   = component->getMinimumSize();
            const ivec2 compPreferredSize = component->getPreferredSize();

            bool compFitMinimum   = compMinimumSize.x   <= compCurrentSize.x && compMinimumSize.y   <= compCurrentSize.y;
            bool compFitPreferred = compPreferredSize.x <= compCurrentSize.x && compPreferredSize.y <= compCurrentSize.y;

            // Component too small, call resize (this will fix all so break too)
            if(!compFitMinimum && !compFitPreferred) {
                resize();
                break;
            }
        }
    }
}