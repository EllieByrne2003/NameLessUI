#include "gridPane.hpp"

// Includes from standard
#include <memory>

// Includes from third party libraries
#include <glm/glm.hpp>
using namespace glm;

// Includes from personal libraries


// Includes from project


// Forward declarations


// Type aliases

int index(const int row, const int col, const int columns) {
    return col + columns * row;
}

NLUI::GridPane::GridPane(const int rows, const int columns, const glm::ivec2 &minSize, const glm::ivec2 &maxSize) : Pane(minSize, maxSize), 
    rows(rows), columns(columns) {
    components = new std::shared_ptr<Component>[rows * columns];
    for(int i = 0; i < rows * columns; i++) {
        components[i] = nullptr;
    }
}

NLUI::GridPane::~GridPane() {
    delete[] components;
}

std::shared_ptr<NLUI::GridPane> NLUI::GridPane::create(const int rows, const int columns, const glm::ivec2 &minSize, const glm::ivec2 &maxSize) {
    return std::shared_ptr<GridPane>(new GridPane(rows, columns, minSize, maxSize));
}

void NLUI::GridPane::draw() const {
    Pane::draw();

    for(int i = 0; i < rows * columns; i++) {
        const std::shared_ptr<const Component> &component = components[i];

        if(component != nullptr) {
            component->draw();
        }
    }
}

int NLUI::GridPane::getMinimumWidth() const {
    int minWidth = 0;

    // Get sum of minimum widths across all columns
    for(int col = 0; col < columns; col++) {
        minWidth += getColMinimumWidth(col);
    }

    return minWidth;
}

int NLUI::GridPane::getMinimumHeight() const {
    int minHeight = 0;

    // Get sum of minimum heights across all rows
    for(int row = 0; row < rows; row++) {
        minHeight += getRowMinimumHeight(row);
    }

    return minHeight;
}

int NLUI::GridPane::getPreferredWidth() const {
    int prefWidth = 0;

    // Get sum of preferred widths across all columns
    for(int col = 0; col < columns; col++) {
        prefWidth += getColPreferredWidth(col);
    }

    return prefWidth;
}

int NLUI::GridPane::getPreferredHeight() const {
    int prefHeight = 0;

    // Get sum of preferred heights across all rows
    for(int row = 0; row < rows; row++) {
        prefHeight += getRowPreferredHeight(row);
    }

    return prefHeight;
}

void NLUI::GridPane::resize() {
    const ivec2 currentSize   = getSize(); 
    const ivec2 preferredSize = getPreferredSize();

    // If big enough for preferred sizes, use them.
    // Otherwise use largest minimums

    int *const rowHeights = new int[rows];
    int *const colWidths = new int[columns];

    // Get row sizes
    for(int row = 0; row < rows; row++) {
        if(currentSize.y <= preferredSize.y) {
            rowHeights[row] = getRowMinimumHeight(row);
        } else {
            rowHeights[row] = getRowPreferredHeight(row);
        }
    }

    // Get column sizes
    for(int col = 0; col < columns; col++) {
        if(currentSize.x <= preferredSize.x) {
            colWidths[col] = getColMinimumWidth(col);
        } else {
            colWidths[col] = getColPreferredWidth(col);
        }
    }

    const ivec2 currentPos = getPos();
    int y = currentPos.y;
    for(int row = 0; row < rows; row++) {
        const int rowHeight = rowHeights[row];

        int x = currentPos.x;
        for(int col = 0; col < columns; col++) {
            const int colWidth = colWidths[col];

            const std::shared_ptr<Component> &component = components[index(row, col, columns)];
            if(component == nullptr) {
                x += colWidth;
                continue;
            }

            const int compPrefWidth  = component->getPreferredWidth();
            const int compPrefHeight = component->getPreferredHeight();
            
            // Set width
            if(colWidth < compPrefWidth) {
                component->setWidth(colWidth); // TODO maybe don't force expansion? Or allow components to ignore changes beyond their max
            } else {
                component->setWidth(compPrefWidth);
            }

            // Set height
            if(rowHeight < compPrefHeight) {
                component->setHeight(rowHeight); // TODO maybe don't force expansion? Or allow components to ignore changes beyond their max
            } else {
                component->setHeight(compPrefHeight);
            }

            // Set position
            component->setPos(x, y);
            
            x += colWidth;
        }

        y += rowHeight;
    }

    delete[] rowHeights;
    delete[] colWidths;
}
        
bool NLUI::GridPane::mouseInside(const double xPos, const double yPos) {
    if(Pane::mouseInside(xPos, yPos)) {
        for(int i = 0; i < rows * columns; i++) {
            const std::shared_ptr<Component> &component = components[i];

            if(component != nullptr) {
                if(component->mouseInside(xPos, yPos)) {
                    focus = component;
                    break; // Can only be one anyways
                }
            }
        }

        return true;
    } else {
        return false;
    }
}

void NLUI::GridPane::addComponent(const std::shared_ptr<Component> &component, const int row, const int col) {
    const std::shared_ptr<Component> &currentComponent = components[index(row, col, columns)]; // TODO add function to remove by index

    // If a component was there already, remove it
    if(currentComponent != nullptr) {
        removeComponent(currentComponent);
    }

    component->setParent(this);
    components[index(row, col, columns)] = component;

    // Validate size and components
    validate();
}


int NLUI::GridPane::getRowMinimumHeight(const int row) const {
    int rowMinHeight = 0;

    for(int col = 0; col < columns; col++) {
        const std::shared_ptr<const Component> &component = components[index(row, col, columns)];

        if(component != nullptr) {
            const int compMinHeight = component->getMinimumHeight();

            if(compMinHeight > rowMinHeight) {
                rowMinHeight = compMinHeight;
            }
        }
    }

    return rowMinHeight;
}

int NLUI::GridPane::getRowPreferredHeight(const int row) const {
    int rowPrefHeight = 0;

    for(int col = 0; col < columns; col++) {
        const std::shared_ptr<const Component> &component = components[index(row, col, columns)];

        if(component != nullptr) {
            const int compPrefHeight = component->getPreferredHeight();

            if(compPrefHeight > rowPrefHeight) {
                rowPrefHeight = compPrefHeight;
            }
        }
    }

    return rowPrefHeight;
}

int NLUI::GridPane::getColMinimumWidth(const int col) const {
    int colMinWidth = 0; // TODO rename all excessively long names for mins and maxs and pref

    for(int row = 0; row < rows; row++) {
        const std::shared_ptr<const Component> &component = components[index(row, col, columns)];

        if(component != nullptr) {
            const int compMinWidth = component->getMinimumWidth();

            if(compMinWidth > colMinWidth) {
                colMinWidth = compMinWidth;
            }
        }
    }

    return colMinWidth;
}

int NLUI::GridPane::getColPreferredWidth(const int col) const {
    int colPrefWidth = 0; // TODO rename all excessively long names for mins and maxs and pref

    for(int row = 0; row < rows; row++) {
        const std::shared_ptr<const Component> &component = components[index(row, col, columns)];

        if(component != nullptr) {
            const int compPrefWidth = component->getPreferredWidth();

            if(compPrefWidth > colPrefWidth) {
                colPrefWidth = compPrefWidth;
            }
        }
    }

    return colPrefWidth;
}

void NLUI::GridPane::removeComponent(const std::shared_ptr<Component> &component) {
    if(component == nullptr) {
        return;
    }
    
    for(int i = 0; i < rows * columns; i++) {
        if(components[i] == component) {
            const std::shared_ptr<Component> copy = components[i];

            if(focus == copy) {
                focus = nullptr;
            }

            components[i] = nullptr;
            component->removeParent();
            validate();

            return; // Duplicates should be impossible anyways
        }
    }
}

void NLUI::GridPane::removeComponent(Component *const component) {
    if(component == nullptr) {
        return;
    }

    for(int i = 0; i < rows * columns; i++) {
        if(components[i].get() == component) {
            const std::shared_ptr<Component> copy = components[i];

            if(focus == copy) {
                focus = nullptr;
            }

            components[i] = nullptr;
            component->removeParent();
            validate();

            return; // Duplicates should be impossible anyways
        }
    }  
}

void NLUI::GridPane::validate() {

}