#include "gridPane.hpp"

// Includes from standard
#include <memory>

// Includes from third party libraries
#include <glm/glm.hpp>
using namespace glm;

// Includes from personal libraries


// Includes from project
#include "../component/nullComponent.hpp"

// Forward declarations


// Type aliases

int index(const int row, const int col, const int cols) {
    return col + cols * row;
}

NLUI::GridPane::GridPane(const int rows, const int cols, const glm::ivec2 &minSize, const glm::ivec2 &maxSize) : Pane(minSize, maxSize), 
    rows(rows), cols(cols) {
    components = new std::shared_ptr<Component>[rows * cols];
    for(int i = 0; i < rows * cols; i++) {
        components[i] = NullComponent::getInstance();
    }
}

NLUI::GridPane::~GridPane() {
    delete[] components;
}

std::shared_ptr<NLUI::GridPane> NLUI::GridPane::create(const int rows, const int cols, const glm::ivec2 &minSize, const glm::ivec2 &maxSize) {
    return std::shared_ptr<GridPane>(new GridPane(rows, cols, minSize, maxSize));
}

void NLUI::GridPane::shrinkRowHeight(const int row, const int decHeight) {
    const int rowHeight  = getRowHeight(row);
    const int propHeight = rowHeight - decHeight; 

    for(int col = 0; col < cols; col++) {
        components[index(row, col, cols)]->shrinkToHeight(propHeight);
    }
}

void NLUI::GridPane::growRowHeight(const int row, const int incHeight) {
    const int rowHeight  = getRowHeight(row);
    const int propHeight = rowHeight + incHeight;

    for(int col = 0; col < cols; col++) {
        components[index(row, col, cols)]->growToHeight(propHeight);
    }
}

void NLUI::GridPane::shrinkRowToHeight(const int row, const int propHeight) {
    for(int col = 0; col < cols; col++) {
        components[index(row, col, cols)]->shrinkToHeight(propHeight);
    }
}

void NLUI::GridPane::growRowToHeight(const int row, const int propHeight) {
    for(int col = 0; col < cols; col++) {
        components[index(row, col, cols)]->growToHeight(propHeight);
    }
}

void NLUI::GridPane::shrinkColWidth(const int col, const int decWidth) {
    const int colWidth  = getColWidth(col);
    const int propWidth = colWidth - decWidth;

    for(int row = 0; row < rows; row++) {
        components[index(row, col, cols)]->shrinkToWidth(propWidth);
    }
}

void NLUI::GridPane::growColWidth(const int col, const int incWidth) {
    const int colWidth  = getColWidth(col);
    const int propWidth = colWidth + incWidth;

    for(int row = 0; row < rows; row++) {
        components[index(row, col, cols)]->growToWidth(propWidth);
    }
}

void NLUI::GridPane::shrinkColToWidth(const int col, const int propWidth) {
    for(int row = 0; row < rows; row++) {
        components[index(row, col, cols)]->shrinkToWidth(propWidth);
    }
}

void NLUI::GridPane::growColToWidth(const int col, const int propWidth) {
    for(int row = 0; row < rows; row++) {
        components[index(row, col, cols)]->growToWidth(propWidth);
    }
}

int NLUI::GridPane::getRowHeight(const int row) const {
    int rowHeight = 0;
    for(int col = 0; col < cols; col++) {
        rowHeight = std::max(rowHeight, components[index(row, col, cols)]->getHeight());
    }

    return rowHeight;
}

int NLUI::GridPane::getRowPrefHeight(const int row) const {
    int rowPrefHeight = 0;
    for(int col = 0; col < cols; col++) {
        rowPrefHeight = std::max(rowPrefHeight, components[index(row, col, cols)]->getPrefHeight());
    }

    return rowPrefHeight;
}

int NLUI::GridPane::getRowMinHeight(const int row) const {
    int rowMinHeight = 0;
    for(int col = 0; col < cols; col++) {
        rowMinHeight = std::max(rowMinHeight, components[index(row, col, cols)]->getMinHeight());
    }

    return rowMinHeight;
}

int NLUI::GridPane::getRowMaxHeight(const int row) const {
    int rowMaxHeight = 0;
    for(int col = 0; col < cols; col++) {
        rowMaxHeight = std::max(rowMaxHeight, components[index(row, col, cols)]->getMaxHeight());
    }

    return rowMaxHeight;
}

int NLUI::GridPane::getRowExtraHeight(const int row) const {
    return std::max(0, getRowHeight(row) - getRowMinHeight(row));
}

int NLUI::GridPane::getRowGrowthHeight(const int row) const {
    return std::max(0, getRowMaxHeight(row) - getRowHeight(row));
}

int NLUI::GridPane::getColWidth(const int col) const {
    int colWidth = 0;
    for(int row = 0; row < rows; row++) {
        colWidth = std::max(colWidth, components[index(row, col, cols)]->getWidth());
    }

    return colWidth;
}

int NLUI::GridPane::getColPrefWidth(const int col) const {
    int colPrefWidth = 0;
    for(int row = 0; row < rows; row++) {
        colPrefWidth = std::max(colPrefWidth, components[index(row, col, cols)]->getPrefWidth());
    }

    return colPrefWidth;
}

int NLUI::GridPane::getColMinWidth(const int col) const {
    int colMinWidth = 0;
    for(int row = 0; row < rows; row++) {
        colMinWidth = std::max(colMinWidth, components[index(row, col, cols)]->getMinWidth());
    }

    return colMinWidth;
}

int NLUI::GridPane::getColMaxWidth(const int col) const {
    int colMaxWidth = 0;
    for(int row = 0; row < rows; row++) {
        colMaxWidth = std::max(colMaxWidth, components[index(row, col, cols)]->getMaxWidth());
    }

    return colMaxWidth;
}

int NLUI::GridPane::getColExtraWidth(const int col) const {
    return std::max(0, getColWidth(col) - getColMinWidth(col));
}
        
int NLUI::GridPane::getColGrowthWidth(const int col) const {
    return std::max(0, getColMaxWidth(col) - getColWidth(col));
}

void NLUI::GridPane::draw() const {
    Pane::draw();

    for(int i = 0; i < rows * cols; i++) {
        components[i]->draw();
    }
}

void NLUI::GridPane::getPrefSize(int &prefWidth, int &prefHeight) const {
    int *rowPrefHeights = new int[rows];
    int *colPrefWidths  = new int[cols];

    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            const glm::ivec2 compPrefSize = components[index(row, col, cols)]->getPrefSize();

            rowPrefHeights[row] = std::max(rowPrefHeights[row], compPrefSize.y);
            colPrefWidths[col]  = std::max(colPrefWidths[col],  compPrefSize.x);
        }
    }

    int sumPrefWidth = 0;
    for(int col = 0; col < cols; col++) {
        sumPrefWidth += colPrefWidths[col];
    }

    int sumPrefHeight = 0;
    for(int row = 0; row < rows; row++) {
        sumPrefHeight += rowPrefHeights[row];
    }

    prefWidth  = sumPrefWidth;
    prefHeight = sumPrefHeight;

    delete[] rowPrefHeights;
    delete[] colPrefWidths;
}

glm::ivec2 NLUI::GridPane::getPrefSize() const {
    int *rowPrefHeights = new int[rows];
    int *colPrefWidths  = new int[cols];

    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            const glm::ivec2 compPrefSize = components[index(row, col, cols)]->getPrefSize();

            rowPrefHeights[row] = std::max(rowPrefHeights[row], compPrefSize.y);
            colPrefWidths[col]  = std::max(colPrefWidths[col],  compPrefSize.x);
        }
    }

    int prefWidth = 0;
    for(int col = 0; col < cols; col++) {
        prefWidth += colPrefWidths[col];
    }

    int prefHeight = 0;
    for(int row = 0; row < rows; row++) {
        prefHeight += rowPrefHeights[row];
    }

    delete[] rowPrefHeights;
    delete[] colPrefWidths;

    return glm::ivec2(prefWidth, prefHeight);
}

int NLUI::GridPane::getPrefWidth() const {
    int prefWidth = 0;
    for(int col = 0; col < cols; col++) {
        prefWidth += getColPrefWidth(col);
    }

    return prefWidth;
}

int NLUI::GridPane::getPrefHeight() const {
    int prefHeight = 0;
    for(int row = 0; row < rows; row++) {
        prefHeight += getRowPrefHeight(row);
    }

    return prefHeight;
}

void NLUI::GridPane::getMinSize(int &minWidth, int &minHeight) const {
    int *rowMinHeights = new int[rows];
    int *colMinWidths  = new int[cols];

    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            const glm::ivec2 compMinSize = components[index(row, col, cols)]->getMinSize();

            rowMinHeights[row] = std::max(rowMinHeights[row], compMinSize.y);
            colMinWidths[col]  = std::max(colMinWidths[col],  compMinSize.x);
        }
    }

    int sumMinWidth = 0;
    for(int col = 0; col < cols; col++) {
        sumMinWidth += colMinWidths[col];
    }

    int sumMinHeight = 0;
    for(int row = 0; row < rows; row++) {
        sumMinHeight += rowMinHeights[row];
    }

    // Take larger computed value or set min
    minWidth  = std::max(minSize.x, sumMinWidth);
    minHeight = std::max(minSize.y, sumMinHeight);

    delete[] rowMinHeights;
    delete[] colMinWidths;
}

glm::ivec2 NLUI::GridPane::getMinSize() const {
    int *rowMinHeights = new int[rows];
    int *colMinWidths  = new int[cols];

    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            const glm::ivec2 compMinSize = components[index(row, col, cols)]->getMinSize();

            rowMinHeights[row] = std::max(rowMinHeights[row], compMinSize.y);
            colMinWidths[col]  = std::max(colMinWidths[col],  compMinSize.x);
        }
    }

    int sumMinWidth = 0;
    for(int col = 0; col < cols; col++) {
        sumMinWidth += colMinWidths[col];
    }

    int sumMinHeight = 0;
    for(int row = 0; row < rows; row++) {
        sumMinHeight += rowMinHeights[row];
    }

    delete[] rowMinHeights;
    delete[] colMinWidths;

    // Return larger of computed value or set min
    return glm::ivec2(std::max(minSize.x, sumMinWidth), std::max(minSize.y, sumMinHeight));
}

int NLUI::GridPane::getMinWidth() const {
    int sumMinWidth = 0;
    for(int col = 0; col < cols; col++) {
        sumMinWidth += getColMinWidth(col);
    }

    return std::max(minSize.x, sumMinWidth);
}

int NLUI::GridPane::getMinHeight() const {
    int sumMinHeight = 0;
    for(int row = 0; row < rows; row++) {
        sumMinHeight += getRowMinHeight(row);
    }

    return std::max(minSize.y, sumMinHeight);
}

void NLUI::GridPane::getMaxSize(int &maxWidth, int &maxHeight) const {
    int *rowMaxHeights = new int[rows];
    int *colMaxWidths  = new int[cols];

    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            const glm::ivec2 compMaxSize = components[index(row, col, cols)]->getMaxSize();

            rowMaxHeights[row] = std::max(rowMaxHeights[row], compMaxSize.y);
            colMaxWidths[col]  = std::max(colMaxWidths[col],  compMaxSize.x);
        }
    }

    int sumMaxWidth = 0;
    for(int col = 0; col < cols; col++) {
        sumMaxWidth += colMaxWidths[col];
    }

    int sumMaxHeight = 0;
    for(int row = 0; row < rows; row++) {
        sumMaxHeight += rowMaxHeights[row];
    }

    // Take the smaller of computed value or set max
    maxWidth  = std::min(maxSize.x, sumMaxWidth);
    maxHeight = std::min(maxSize.y, sumMaxHeight);

    delete[] rowMaxHeights;
    delete[] colMaxWidths;
}

glm::ivec2 NLUI::GridPane::getMaxSize() const {
    int *rowMaxHeights = new int[rows];
    int *colMaxWidths  = new int[cols];

    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            const glm::ivec2 compMaxSize = components[index(row, col, cols)]->getMaxSize();

            rowMaxHeights[row] = std::max(rowMaxHeights[row], compMaxSize.y);
            colMaxWidths[col]  = std::max(colMaxWidths[col],  compMaxSize.x);
        }
    }

    int sumMaxWidth = 0;
    for(int col = 0; col < cols; col++) {
        sumMaxWidth += colMaxWidths[col];
    }

    int sumMaxHeight = 0;
    for(int row = 0; row < rows; row++) {
        sumMaxHeight += rowMaxHeights[row];
    }

    delete[] rowMaxHeights;
    delete[] colMaxWidths;

    // Return smaller of computed value or set max
    return glm::ivec2(std::min(maxSize.x, sumMaxWidth), std::min(maxSize.y, sumMaxHeight));
}

int NLUI::GridPane::getMaxWidth() const {
    int sumMaxWidth = 0;
    for(int col = 0; col < cols; col++) {
        sumMaxWidth += getColMaxWidth(col);
    }

    return std::min(maxSize.x, sumMaxWidth);
}

int NLUI::GridPane::getMaxHeight() const {
    int sumMaxHeight = 0;
    for(int row = 0; row < rows; row++) {
        sumMaxHeight += getRowMaxHeight(row);
    }

    return std::min(maxSize.y, sumMaxHeight);
}
    
bool NLUI::GridPane::mouseInside(const double xPos, const double yPos) {
    if(Pane::mouseInside(xPos, yPos)) {
        for(int i = 0; i < rows * cols; i++) {
            const std::shared_ptr<Component> &component = components[i];

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

void NLUI::GridPane::removeComponent(const std::shared_ptr<Component> &component) {
    if(component == NullComponent::getInstance()) {
        return;
    }
    
    for(int i = 0; i < rows * cols; i++) {
        if(components[i] == component) {
            const std::shared_ptr<Component> copy = components[i];

            if(focus == copy) {
                focus = nullptr;
            }

            components[i] = NullComponent::getInstance();
            component->removeParent();
            layoutRoot();

            return; // Duplicates should be impossible anyways
        }
    }
}

void NLUI::GridPane::removeComponent(Component *const component) {
    if(component == NullComponent::getInstance().get()) {
        return;
    }

    for(int i = 0; i < rows * cols; i++) {
        if(components[i].get() == component) {
            const std::shared_ptr<Component> copy = components[i];

            if(focus == copy) {
                focus = nullptr;
            }

            components[i] = NullComponent::getInstance();
            component->removeParent();
            layoutRoot();

            return; // Duplicates should be impossible anyways
        }
    }  
}

void NLUI::GridPane::doLayout() {
    // Propose current size to each
    for(int i = 0; i < rows * cols; i++) {
        components[i]->proposeSize(size);
    }

    // Get row heights // TODO should be unsigned
    int totalHeight    = 0;
    int totalMinHeight = 0;
    int totalMaxHeight = 0;
    for(int row = 0; row < rows; row++) {
        totalHeight    += getRowHeight(row);
        totalMinHeight += getRowMinHeight(row);
        totalMaxHeight += getRowMaxHeight(row);
    }

    int totalExtraHeight  = std::max(0, totalHeight - totalMinHeight);
    int totalGrowthHeight = std::max(0, totalMaxHeight - totalHeight);

    if(totalHeight < size.y) {
        const int increase          = std::min(size.y - totalHeight, totalGrowthHeight);
        const int totalGrowthBefore = totalGrowthHeight;

        // Increase to max or to fill space proporitonally
        for(int row = 0; row < rows; row++) {
            const int rowGrowthHeight = getRowGrowthHeight(row);

            const int incHeight = increase * (float(rowGrowthHeight) / float(totalGrowthBefore));

            growRowHeight(row, incHeight);
            totalHeight       += incHeight;
            totalGrowthHeight -= incHeight;
        }

        // Increase row with largest growth until fit (or no more growthHeight)
        while(totalHeight < size.y && totalGrowthHeight > 0) {
            // Get greateset height growth
            int greatestGrowthRow = 0;
            int greatestGrowth    = getRowGrowthHeight(0);

            for(int row = 1; row < rows; row++) {
                const int rowGrowth = getRowGrowthHeight(row);

                if(greatestGrowth < rowGrowth) {
                    greatestGrowthRow = row;
                    greatestGrowth = rowGrowth;
                }
            }

            growRowHeight(greatestGrowthRow, 1);
            totalHeight++;
            totalGrowthHeight--;
        }
    } else if(totalHeight > size.y) {
        if(totalHeight - totalExtraHeight <= size.y) {
            // Remove proporitionally
            const int reduction = totalHeight - size.y;
            for(int row = 0; row < rows; row++) {
                const int rowExtraHeight = getRowExtraHeight(row);

                const int decHeight = reduction * (float(rowExtraHeight) / float(totalExtraHeight));

                shrinkRowHeight(row, decHeight);
                totalHeight -= decHeight;
            }

            // Remove 1 from row with larget extra height
            while(totalHeight > size.y) {
                // Get largest extra
                int largestExtraRow = 0;
                int largestExtraHeight = getRowExtraHeight(0);
                for(int row = 1; row < rows; row++) {
                    const int rowExtraHeight = getRowExtraHeight(row);

                    if(largestExtraHeight < rowExtraHeight) {
                        largestExtraRow = row;
                        largestExtraHeight = rowExtraHeight;
                    }
                }

                // Take 1 from it
                shrinkRowHeight(largestExtraRow, 1);
                totalHeight--;
            }
        } else {
            // Set to mins // TODO should have function to minimise row heights
            for(int row = 0; row < rows; row++) {
                const int decHeight = getRowExtraHeight(row);

                shrinkRowHeight(row, decHeight);
                totalHeight -= decHeight;
            }

            // Set to below mins (proportionately)
            const int reduction   = totalHeight - size.y;
            const int totalBefore = totalHeight;
            for(int row = 0; row < rows; row++) {
                const int rowHeight = getRowHeight(row);

                const int decHeight = reduction * (float(rowHeight) / float(totalBefore));

                shrinkRowHeight(row, decHeight);
                totalHeight -= decHeight;
            }

            // Reduce largest height by one until fit
            while(totalHeight > size.y) {
                // Get largest height
                int tallestRow = 0;
                int tallestHeight = getRowHeight(0);
                for(int row = 1; row < rows; row++) {
                    const int rowheight = getRowHeight(row);

                    if(tallestHeight < rowheight) {
                        tallestRow = row;
                        tallestHeight = rowheight;
                    }
                }

                // Take 1 from it
                shrinkRowHeight(tallestRow, 1);
                totalHeight--;
            }
        }
    }

    // Get col widths // TODO should be unsigned
    int totalWidth    = 0;
    int totalMinWidth = 0;
    int totalMaxWidth = 0;
    for(int col = 0; col < cols; col++) {
        totalWidth    += getColWidth(col);
        totalMinWidth += getColMinWidth(col);
        totalMaxWidth += getColMaxWidth(col);
    }

    int totalExtraWidth  = std::max(0, totalWidth - totalMinWidth);
    int totalGrowthWidth = std::max(0, totalMaxWidth - totalWidth);

    if(totalWidth < size.x) {
        const int increase          = std::min(size.x - totalWidth, totalGrowthWidth);
        const int totalGrowthBefore = totalGrowthWidth;

        // Increase to max or to fill space proporitonally
        for(int col = 0; col < cols; col++) {
            const int colGrowthWidth = getColGrowthWidth(col);

            const int incWidth = increase * (float(colGrowthWidth) / float(totalGrowthBefore));

            growColWidth(col, incWidth);
            totalWidth       += incWidth;
            totalGrowthWidth -= incWidth;
        }

        // Increase row with largest growth until fit (or no more growthWidth)
        while(totalWidth < size.x && totalGrowthWidth > 0) {
            // Get greateset width growth
            int greatestGrowthCol = 0;
            int greatestGrowth    = getColGrowthWidth(0);

            for(int col = 1; col < cols; col++) {
                const int colGrowth = getColGrowthWidth(col);

                if(greatestGrowth < colGrowth) {
                    greatestGrowthCol = col;
                    greatestGrowth = colGrowth;
                }
            }

            growColWidth(greatestGrowthCol, 1);
            totalWidth++;
            totalGrowthWidth--;
        }
    } else if(totalWidth > size.x) {
        if(totalWidth - totalExtraWidth <= size.x) {
            // Remove proportionately
            const int reduction = totalWidth - size.x;
            for(int col = 0; col < cols; col++) {
                const int colExtraWidth = getColExtraWidth(col);

                const int decWidth = reduction * (float(colExtraWidth) / float(totalExtraWidth));

                shrinkColWidth(col, decWidth);
                totalWidth -= decWidth;
            }

            // Remove 1 from col with largest extra width
            while(totalWidth > size.x) {
                // Get largest extra
                int largestExtraCol = 0;
                int largestExtraWidth = getColExtraWidth(0);
                for(int col = 1; col < cols; col++) {
                    const int colExtraWidth = getColExtraWidth(col);

                    if(largestExtraWidth < colExtraWidth) {
                        largestExtraCol = col;
                        largestExtraWidth = colExtraWidth;
                    }
                }

                // Take 1 from it
                shrinkColWidth(largestExtraCol, 1);
                totalWidth--;
            }
        } else {
            // Set to mins // TODO should have function to minise col widths
            for(int col = 0; col < cols; col++) {
                const int decWidth = getColExtraWidth(col);

                shrinkColWidth(col, decWidth);
                totalWidth -= decWidth;
            }

            // Set below mins (proportionately)
            const int reduction   = totalWidth - size.x;
            const int totalBefore = totalWidth;
            for(int col = 0; col < cols; col++) {
                const int colWidth = getColWidth(col);

                const int decWidth = reduction * (float(colWidth) / float(totalBefore));

                shrinkColWidth(col, decWidth);
                totalWidth -= decWidth;
            }

            // Reduce largest width by one until fit
            while(totalWidth > size.x) {
                // Get largest width
                int widestCol = 0;
                int widestWidth = getColWidth(0);
                for(int col = 1; col < cols; col++) {
                    const int colWidth = getColWidth(col);

                    if(widestWidth < colWidth) {
                        widestCol = col;
                        widestWidth = colWidth;
                    }
                }

                // Take 1 from it
                shrinkColWidth(widestCol, 1);
                totalWidth--;
            }
        }
    }

    // Equalise size of components in rows and columns
    for(int row = 0; row < rows; row++) {
        growRowToHeight(row, getRowHeight(row));
    }

    for(int col = 0; col < cols; col++) {
        growColToWidth(col, getColWidth(col));
    }

    // Set positions
    int y = pos.y + ((size.y - totalHeight) / 2);
    for(int row = 0; row < rows; row++) {
        const int rowHeight = getRowHeight(row);

        for(int col = 0; col < cols; col++) {
            std::shared_ptr<Component> &comp = components[index(row, col, cols)];
                
            const int offset = (rowHeight - comp->getHeight()) / 2;
            comp->setYPos(y + offset);
        }

        y += rowHeight;
    }

    int x = pos.x + ((size.x - totalWidth) / 2);
    for(int col = 0; col < cols; col++) {
        const int colWidth = getColWidth(col);

        for(int row = 0; row < rows; row++) {
            std::shared_ptr<Component> &comp = components[index(row, col, cols)];

            const int offset = (colWidth - comp->getWidth()) / 2;
            comp->setXPos(x + offset);
        }

        x += colWidth;
    }
}

void NLUI::GridPane::addComponent(const std::shared_ptr<Component> &component, const int row, const int col) {
    // Prevent nullptr from entering array, replace with a NullComponent
    if(component == nullptr) {
        addComponent(NullComponent::getInstance(), row, col);
    } else {
        const std::shared_ptr<Component> &currentComponent = components[index(row, col, cols)]; // TODO add function to remove by index

        // If a component was there already, remove it
        removeComponent(currentComponent); // TODO better way to do this

        component->setParent(this);
        components[index(row, col, cols)] = component;

        layoutRoot();
    }
}