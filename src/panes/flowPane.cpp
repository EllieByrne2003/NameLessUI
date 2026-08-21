#include "flowPane.hpp"

// Includes from standard
#include <algorithm>
#include <memory>
#include <vector>

// Includes from third party libraries
#include <glm/glm.hpp>
using namespace glm;

// Includes from personal libraries


// Includes from project


// Forward declarations
void shrinkRowHeight(const std::vector<std::shared_ptr<NLUI::Component>> &row, const int decHeight);
void growRowHeight(const std::vector<std::shared_ptr<NLUI::Component>> &row, const int incHeight);

void shrinkColWidth(const std::vector<std::shared_ptr<NLUI::Component>> &col, const int decWidth);
void growColWidth(const std::vector<std::shared_ptr<NLUI::Component>> &col, const int incWidth);

int getRowWidth(const std::vector<std::shared_ptr<NLUI::Component>> &row);
int getRowMaxWidth(const std::vector<std::shared_ptr<NLUI::Component>> &row);
int getRowGrowthWidth(const std::vector<std::shared_ptr<NLUI::Component>> &row);

int getRowHeight(const std::vector<std::shared_ptr<NLUI::Component>> &row);
int getRowMinHeight(const std::vector<std::shared_ptr<NLUI::Component>> &row);
int getRowMaxHeight(const std::vector<std::shared_ptr<NLUI::Component>> &row);
int getRowExtraHeight(const std::vector<std::shared_ptr<NLUI::Component>> &row);
int getRowGrowthHeight(const std::vector<std::shared_ptr<NLUI::Component>> &row);

int getColWidth(const std::vector<std::shared_ptr<NLUI::Component>> &col);
int getColMinWidth(const std::vector<std::shared_ptr<NLUI::Component>> &col);
int getColMaxWidth(const std::vector<std::shared_ptr<NLUI::Component>> &col);
int getColExtraWidth(const std::vector<std::shared_ptr<NLUI::Component>> &col);
int getColGrowthWidth(const std::vector<std::shared_ptr<NLUI::Component>> &col);

int getColHeight(const std::vector<std::shared_ptr<NLUI::Component>> &col);
int getColMaxHeight(const std::vector<std::shared_ptr<NLUI::Component>> &col);
int getColGrowthHeight(const std::vector<std::shared_ptr<NLUI::Component>> &col);

// Type aliases


NLUI::FlowPane::FlowPane(const bool horizontal, const glm::ivec2 &minSize, const glm::ivec2 &maxSize) : Pane(minSize, maxSize),
    horizontal(horizontal) {

}

NLUI::FlowPane::~FlowPane() {
}

std::shared_ptr<NLUI::FlowPane> NLUI::FlowPane::create(const bool horizontal, const glm::ivec2 &minSize, const glm::ivec2 &maxSize) {
    return std::shared_ptr<FlowPane>(new FlowPane(horizontal, minSize, maxSize));
}

void NLUI::FlowPane::draw() const {
    Pane::draw();

    for(const std::shared_ptr<const Component> &component : components) {
        component->draw();
    }
}

void NLUI::FlowPane::getPrefSize(int &prefWidth, int &prefHeight) const {
    if(horizontal) {
        int greatestRowPrefWidth = 0;
        int sumPrefHeight        = 0;
        for(int row = 0; row < rows.size(); row++) {
            int rowPrefWidth  = 0;
            int rowPrefHeight = 0;
            for(const std::shared_ptr<Component> &comp : rows[row]) {
                const glm::ivec2 compPrefSize = comp->getPrefSize();

                rowPrefWidth  += compPrefSize.x;
                rowPrefHeight  = std::max(rowPrefHeight, compPrefSize.y);
            }

            greatestRowPrefWidth  = std::max(greatestRowPrefWidth, rowPrefWidth);
            sumPrefHeight        += rowPrefHeight;
        }

        prefWidth  = greatestRowPrefWidth;
        prefHeight = sumPrefHeight;
    } else {
        int sumPrefWidth          = 0;
        int greatestColPrefHeight = 0;
        for(int col = 0; col < cols.size(); col++) {
            int colPrefWidth  = 0;
            int colPrefHeight = 0;
            for(const std::shared_ptr<Component> &comp : cols[col]) {
                const glm::ivec2 compPrefSize = comp->getPrefSize();

                colPrefWidth   = std::max(colPrefWidth, compPrefSize.x);
                colPrefHeight += colPrefHeight;
            }

            sumPrefWidth          += colPrefWidth;
            greatestColPrefHeight  = std::max(greatestColPrefHeight, colPrefHeight);
        }

        prefWidth  = sumPrefWidth;
        prefHeight = greatestColPrefHeight;
    }
}

glm::ivec2 NLUI::FlowPane::getPrefSize() const {
    if(horizontal) {
        int greatestRowPrefWidth = 0;
        int sumPrefHeight        = 0;
        for(int row = 0; row < rows.size(); row++) {
            int rowPrefWidth  = 0;
            int rowPrefHeight = 0;
            for(const std::shared_ptr<Component> &comp : rows[row]) {
                const glm::ivec2 compPrefSize = comp->getPrefSize();

                rowPrefWidth  += compPrefSize.x;
                rowPrefHeight  = std::max(rowPrefHeight, compPrefSize.y);
            }

            greatestRowPrefWidth  = std::max(greatestRowPrefWidth, rowPrefWidth);
            sumPrefHeight        += rowPrefHeight;
        }

        return glm::ivec2(greatestRowPrefWidth, sumPrefHeight);
    } else {
        int sumPrefWidth          = 0;
        int greatestColPrefHeight = 0;
        for(int col = 0; col < cols.size(); col++) {
            int colPrefWidth  = 0;
            int colPrefHeight = 0;
            for(const std::shared_ptr<Component> &comp : cols[col]) {
                const glm::ivec2 compPrefSize = comp->getPrefSize();

                colPrefWidth   = std::max(colPrefWidth, compPrefSize.x);
                colPrefHeight += colPrefHeight;
            }

            sumPrefWidth          += colPrefWidth;
            greatestColPrefHeight  = std::max(greatestColPrefHeight, colPrefHeight);
        }

        return glm::ivec2(sumPrefWidth, greatestColPrefHeight);
    }
}

int NLUI::FlowPane::getPrefWidth() const {
    int sumPrefWidth = 0;

    if(horizontal) {
        for(const std::vector<std::shared_ptr<Component>> &row : rows) {
            int rowPrefWidth = 0;
            for(const std::shared_ptr<Component> &comp : row) {
                rowPrefWidth = std::max(rowPrefWidth, comp->getPrefWidth());
            }

            sumPrefWidth += rowPrefWidth;
        }
    } else {
        for(const std::vector<std::shared_ptr<Component>> &col : cols) {
            int colPrefWidth = 0;
            for(const std::shared_ptr<Component> &comp : col) {
                colPrefWidth += comp->getPrefWidth();
            }

            sumPrefWidth = std::max(sumPrefWidth, colPrefWidth);
        }
    }

    return sumPrefWidth;
}

int NLUI::FlowPane::getPrefHeight() const {
    int sumPrefHeight = 0;

    if(horizontal) {
        for(const std::vector<std::shared_ptr<Component>> &row : rows) {
            int rowPrefHeight = 0;
            for(const std::shared_ptr<Component> &comp : row) {
                rowPrefHeight = std::max(rowPrefHeight, comp->getPrefHeight());
            }

            sumPrefHeight += rowPrefHeight;
        }
    } else {
        for(const std::vector<std::shared_ptr<Component>> &col : cols) {
            int colPrefHeight = 0;
            for(const std::shared_ptr<Component> &comp : col) {
                colPrefHeight += comp->getPrefHeight();
            }

            sumPrefHeight = std::max(sumPrefHeight, colPrefHeight);
        }
    }

    return sumPrefHeight;
}

void NLUI::FlowPane::getMinSize(int &minWidth, int &minHeight) const {
    if(horizontal) {
        int greatestRowMinWidth = 0;
        int sumMinHeight        = 0;
        for(int row = 0; row < rows.size(); row++) {
            int rowMinWidth  = 0;
            int rowMinHeight = 0;
            for(const std::shared_ptr<Component> &comp : rows[row]) {
                const glm::ivec2 compMinSize = comp->getMinSize();

                rowMinWidth  += compMinSize.x;
                rowMinHeight  = std::max(rowMinHeight, compMinSize.y);
            }

            greatestRowMinWidth  = std::max(greatestRowMinWidth, rowMinWidth);
            sumMinHeight        += rowMinHeight;
        }

        minWidth  = std::max(minSize.x, greatestRowMinWidth);
        minHeight = std::max(minSize.y, sumMinHeight);
    } else {
        int sumMinWidth          = 0;
        int greatestColMinHeight = 0;
        for(int col = 0; col < cols.size(); col++) {
            int colMinWidth  = 0;
            int colMinHeight = 0;
            for(const std::shared_ptr<Component> &comp : cols[col]) {
                const glm::ivec2 compMinSize = comp->getMinSize();

                colMinWidth   = std::max(colMinWidth, compMinSize.x);
                colMinHeight += colMinHeight;
            }

            sumMinWidth          += colMinWidth;
            greatestColMinHeight  = std::max(greatestColMinHeight, colMinHeight);
        }

        minWidth  = std::max(minSize.x, sumMinWidth);
        minHeight = std::max(minSize.y, greatestColMinHeight);
    }
}

glm::ivec2 NLUI::FlowPane::getMinSize() const {
    if(horizontal) {
        int greatestRowMinWidth = 0;
        int sumMinHeight        = 0;
        for(int row = 0; row < rows.size(); row++) {
            int rowMinWidth  = 0;
            int rowMinHeight = 0;
            for(const std::shared_ptr<Component> &comp : rows[row]) {
                const glm::ivec2 compMinSize = comp->getMinSize();

                rowMinWidth  += compMinSize.x;
                rowMinHeight  = std::max(rowMinHeight, compMinSize.y);
            }

            greatestRowMinWidth  = std::max(greatestRowMinWidth, rowMinWidth);
            sumMinHeight        += rowMinHeight;
        }

        return glm::ivec2(std::max(minSize.x, greatestRowMinWidth), std::max(minSize.y, sumMinHeight));
    } else {
        int sumMinWidth          = 0;
        int greatestColMinHeight = 0;
        for(int col = 0; col < cols.size(); col++) {
            int colMinWidth  = 0;
            int colMinHeight = 0;
            for(const std::shared_ptr<Component> &comp : cols[col]) {
                const glm::ivec2 compMinSize = comp->getMinSize();

                colMinWidth   = std::max(colMinWidth, compMinSize.x);
                colMinHeight += colMinHeight;
            }

            sumMinWidth          += colMinWidth;
            greatestColMinHeight  = std::max(greatestColMinHeight, colMinHeight);
        }

        return glm::ivec2(std::max(minSize.x, sumMinWidth), std::max(minSize.y, greatestColMinHeight));
    }
}

int NLUI::FlowPane::getMinWidth() const {
    int sumMinWidth = 0;

    if(horizontal) {
        for(const std::vector<std::shared_ptr<Component>> &row : rows) {
            int rowMinWidth = 0;
            for(const std::shared_ptr<Component> &comp : row) {
                rowMinWidth = std::max(rowMinWidth, comp->getMinWidth());
            }

            sumMinWidth += rowMinWidth;
        }
    } else {
        for(const std::vector<std::shared_ptr<Component>> &col : cols) {
            int colMinWidth = 0;
            for(const std::shared_ptr<Component> &comp : col) {
                colMinWidth += comp->getMinWidth();
            }

            sumMinWidth = std::max(sumMinWidth, colMinWidth);
        }
    }

    return std::max(minSize.x, sumMinWidth);
}

int NLUI::FlowPane::getMinHeight() const {
    int sumMinHeight = 0;

    if(horizontal) {
        for(const std::vector<std::shared_ptr<Component>> &row : rows) {
            int rowMinHeight = 0;
            for(const std::shared_ptr<Component> &comp : row) {
                rowMinHeight = std::max(rowMinHeight, comp->getMinHeight());
            }

            sumMinHeight += rowMinHeight;
        }
    } else {
        for(const std::vector<std::shared_ptr<Component>> &col : cols) {
            int colMinHeight = 0;
            for(const std::shared_ptr<Component> &comp : col) {
                colMinHeight += comp->getMinHeight();
            }

            sumMinHeight = std::max(sumMinHeight, colMinHeight);
        }
    }

    return std::max(minSize.y, sumMinHeight);
}

void NLUI::FlowPane::getMaxSize(int &maxWidth, int &maxHeight) const {
    if(horizontal) {
        int greatestRowMinWidth = 0;
        int sumMinHeight        = 0;
        for(int row = 0; row < rows.size(); row++) {
            int rowMinWidth  = 0;
            int rowMinHeight = 0;
            for(const std::shared_ptr<Component> &comp : rows[row]) {
                const glm::ivec2 compMinSize = comp->getMinSize();

                rowMinWidth  += compMinSize.x;
                rowMinHeight  = std::max(rowMinHeight, compMinSize.y);
            }

            greatestRowMinWidth  = std::max(greatestRowMinWidth, rowMinWidth);
            sumMinHeight        += rowMinHeight;
        }

        maxWidth  = std::min(maxSize.x, greatestRowMinWidth);
        maxHeight = std::min(maxSize.y, sumMinHeight);
    } else {
        int sumMinWidth          = 0;
        int greatestColMinHeight = 0;
        for(int col = 0; col < cols.size(); col++) {
            int colMinWidth  = 0;
            int colMinHeight = 0;
            for(const std::shared_ptr<Component> &comp : cols[col]) {
                const glm::ivec2 compMinSize = comp->getMinSize();

                colMinWidth   = std::max(colMinWidth, compMinSize.x);
                colMinHeight += colMinHeight;
            }

            sumMinWidth          += colMinWidth;
            greatestColMinHeight  = std::max(greatestColMinHeight, colMinHeight);
        }

        maxWidth  = std::min(maxSize.x, sumMinWidth);
        maxHeight = std::min(maxSize.y, greatestColMinHeight);
    }
}

glm::ivec2 NLUI::FlowPane::getMaxSize() const {
    if(horizontal) {
        int greatestRowMinWidth = 0;
        int sumMinHeight        = 0;
        for(int row = 0; row < rows.size(); row++) {
            int rowMinWidth  = 0;
            int rowMinHeight = 0;
            for(const std::shared_ptr<Component> &comp : rows[row]) {
                const glm::ivec2 compMinSize = comp->getMinSize();

                rowMinWidth  += compMinSize.x;
                rowMinHeight  = std::max(rowMinHeight, compMinSize.y);
            }

            greatestRowMinWidth  = std::max(greatestRowMinWidth, rowMinWidth);
            sumMinHeight        += rowMinHeight;
        }

        return glm::ivec2(std::min(maxSize.x, greatestRowMinWidth), std::min(maxSize.y, sumMinHeight));
    } else {
        int sumMinWidth          = 0;
        int greatestColMinHeight = 0;
        for(int col = 0; col < cols.size(); col++) {
            int colMinWidth  = 0;
            int colMinHeight = 0;
            for(const std::shared_ptr<Component> &comp : cols[col]) {
                const glm::ivec2 compMinSize = comp->getMinSize();

                colMinWidth   = std::max(colMinWidth, compMinSize.x);
                colMinHeight += colMinHeight;
            }

            sumMinWidth          += colMinWidth;
            greatestColMinHeight  = std::max(greatestColMinHeight, colMinHeight);
        }

        return glm::ivec2(std::min(maxSize.x, sumMinWidth), std::min(maxSize.y, greatestColMinHeight));
    }
}

int NLUI::FlowPane::getMaxWidth() const {
    int sumMaxWidth = 0;

    if(horizontal) {
        for(const std::vector<std::shared_ptr<Component>> &row : rows) {
            int rowMaxWidth = 0;
            for(const std::shared_ptr<Component> &comp : row) {
                rowMaxWidth = std::max(rowMaxWidth, comp->getMaxWidth());
            }

            sumMaxWidth += rowMaxWidth;
        }
    } else {
        for(const std::vector<std::shared_ptr<Component>> &col : cols) {
            int colMaxWidth = 0;
            for(const std::shared_ptr<Component> &comp : col) {
                colMaxWidth += comp->getMaxWidth();
            }

            sumMaxWidth = std::max(sumMaxWidth, colMaxWidth);
        }
    }

    return std::min(maxSize.x, sumMaxWidth);
}

int NLUI::FlowPane::getMaxHeight() const {
    int sumMaxHeight = 0;

    if(horizontal) {
        for(const std::vector<std::shared_ptr<Component>> &row : rows) {
            int rowMaxHeight = 0;
            for(const std::shared_ptr<Component> &comp : row) {
                rowMaxHeight = std::max(rowMaxHeight, comp->getMaxHeight());
            }

            sumMaxHeight += rowMaxHeight;
        }
    } else {
        for(const std::vector<std::shared_ptr<Component>> &col : cols) {
            int colMaxHeight = 0;
            for(const std::shared_ptr<Component> &comp : col) {
                colMaxHeight += comp->getMaxHeight();
            }

            sumMaxHeight = std::max(sumMaxHeight, colMaxHeight);
        }
    }

    return std::min(maxSize.y, sumMaxHeight);
}

bool NLUI::FlowPane::mouseInside(const double xPos, const double yPos) {
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

void NLUI::FlowPane::removeComponent(const std::shared_ptr<Component> &component) {
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

void NLUI::FlowPane::removeComponent(Component *const component) {
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

void NLUI::FlowPane::doLayout() {
    rows.clear();
    cols.clear();

    // Propose current size to each
    for(std::shared_ptr<Component> &comp : components) {
        comp->proposeSize(size);
    }

    if(horizontal) {
        std::vector<std::shared_ptr<Component>> currentRow;
        int currentRowWidth = 0;

        int currentRowHeight    = 0;
        int currentRowMinHeight = 0;
        int currentRowMaxHeight = 0;

        int totalWidth = 0;
        // int totalMinWidth = 0;
        // int totalMaxWidth = 0;

        int totalHeight = 0;
        int totalMinHeight = 0;
        int totalMaxHeight = 0;

        for(std::shared_ptr<Component> &comp : components) {
            if(comp->getWidth() > size.x) {
                comp->shrinkToWidth(size.x);
            }

            if(currentRowWidth + comp->getWidth() > size.x) {
                rows.push_back(currentRow);
                currentRow.clear();

                totalHeight    += currentRowHeight;
                totalMinHeight += currentRowMinHeight;
                totalMaxHeight += currentRowMaxHeight;

                totalWidth = std::max(totalWidth, currentRowWidth);

                currentRowWidth     = 0;
                currentRowHeight    = 0;
                currentRowMinHeight = 0;
                currentRowMaxHeight = 0;
            }

            currentRow.push_back(comp);

            currentRowWidth     += comp->getWidth();
            currentRowHeight     = std::max(currentRowHeight,    comp->getHeight());
            currentRowMinHeight  = std::max(currentRowMinHeight, comp->getMinHeight());
            currentRowMaxHeight  = std::max(currentRowMaxHeight, comp->getMaxHeight());
        }

        if(currentRow.size() > 0) {
            rows.push_back(currentRow);
            currentRow.clear();

            totalHeight    += currentRowHeight;
            totalMinHeight += currentRowMinHeight;
            totalMaxHeight += currentRowMaxHeight;

            totalWidth = std::max(totalWidth, currentRowWidth);

            currentRowWidth     = 0;
            currentRowHeight    = 0;
            currentRowMinHeight = 0;
            currentRowMaxHeight = 0;
        }
        
        int totalExtraHeight  = std::max(0, totalHeight - totalMinHeight);
        int totalGrowthHeight = std::max(0, totalMaxHeight - totalHeight);

        if(totalHeight < size.y) {
            const int increase          = std::min(size.y - totalHeight, totalGrowthHeight);
            const int totalGrowthBefore = totalGrowthHeight;

            // Increase to max or to fill space proporitonally
            for(std::vector<std::shared_ptr<Component>> &row : rows) {
                const int rowGrowthHeight = getRowGrowthHeight(row);

                const int incHeight = increase * (float(rowGrowthHeight) / float(totalGrowthBefore));

                growRowHeight(row, incHeight);
                totalHeight       += incHeight;
                totalGrowthHeight -= incHeight;
            }

            // Increase row with largest growth until fit (or no more growthHeight)
            while(totalHeight < size.y && totalGrowthHeight > 0) {
                // Get greateset height growth
                int greatestGrowthRowIndex = 0;
                int greatestGrowth = getRowGrowthHeight(rows[greatestGrowthRowIndex]);

                for(int i = 1; i < rows.size(); i++) {
                    const std::vector<std::shared_ptr<NLUI::Component>> &row = rows[i];
                    const int rowGrowth = getRowGrowthHeight(row);

                    if(greatestGrowth < rowGrowth) {
                        greatestGrowthRowIndex = i;
                        greatestGrowth = rowGrowth;
                    }
                }

                growRowHeight(rows[greatestGrowthRowIndex], 1);
                totalHeight++;
                totalGrowthHeight--;
            }
        } else if(totalHeight > size.y) {
            if(totalHeight - totalExtraHeight <= size.y) {
                // Remove proporitionally
                const int reduction = totalHeight - size.y;
                for(std::vector<std::shared_ptr<Component>> &row : rows) {
                    const int rowExtraHeight = getRowExtraHeight(row);

                    const int decHeight = reduction * (float(rowExtraHeight) / float(totalExtraHeight));

                    shrinkRowHeight(row, decHeight);
                    totalHeight -= decHeight;
                }

                // Remove 1 from row with larget extra height
                while(totalHeight > size.y) {
                    // Get largest extra
                    std::vector<std::shared_ptr<NLUI::Component>> &largestExtraRow = rows[0];
                    int largestExtraHeight = getRowExtraHeight(largestExtraRow);
                    for(int i = 1; i < rows.size(); i++) {
                        const std::vector<std::shared_ptr<NLUI::Component>> &row = rows[i];
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
                for(std::vector<std::shared_ptr<Component>> &row : rows) {
                    const int decHeight = getRowExtraHeight(row);

                    shrinkRowHeight(row, decHeight);
                    totalHeight -= decHeight;
                }

                // Set to below mins (proportionately)
                const int reduction   = totalHeight - size.y;
                const int totalBefore = totalHeight;
                for(std::vector<std::shared_ptr<Component>> &row : rows) {
                    const int rowHeight = getRowHeight(row);

                    const int decHeight = reduction * (float(rowHeight) / float(totalBefore));

                    shrinkRowHeight(row, decHeight);
                    totalHeight -= decHeight;
                }

                // Reduce largest height by one until fit
                while(totalHeight > size.y) {
                    // Get largest height
                    int tallestRowIndex = 0;
                    int tallestHeight = getRowHeight(rows[tallestRowIndex]);
                    for(int i = 1; i < rows.size(); i++) {
                        const std::vector<std::shared_ptr<NLUI::Component>> &row = rows[i];
                        const int rowheight = getRowHeight(row);

                        if(tallestHeight < rowheight) {
                            tallestRowIndex = i;
                            tallestHeight = rowheight;
                        }
                    }

                    // Take 1 from it
                    shrinkRowHeight(rows[tallestRowIndex], 1);
                    totalHeight--;
                }
            }
        }

        // TODO increase component width to fill full space
        // TODO maybe offser a flag for that? Pack?
        // TODO this is soooooo messy, make it a private function?
        for(const std::vector<std::shared_ptr<Component>> &row : rows) {
            const int rowHeight = getRowHeight(row);
            for(const std::shared_ptr<Component> &comp : row) {
                comp->growToHeight(rowHeight);
            }
        }

        int y = pos.y + ((size.y + totalHeight) / 2);
        for(const std::vector<std::shared_ptr<Component>> &row : rows) {
            const int rowWidth  = getRowWidth(row);
            const int rowHeight = getRowHeight(row);

            int x  = pos.x + ((size.x - rowWidth) / 2);
            y     -= rowHeight;

            for(const std::shared_ptr<Component> &comp : row) {
                const int offset = (rowHeight - comp->getHeight()) / 2;

                comp->setXPos(x);
                comp->setYPos(y + offset);

                x += comp->getWidth();
            }
        }
    } else {
        std::vector<std::shared_ptr<Component>> currentCol;
        int currentColHeight = 0;

        int currentColWidth    = 0;
        int currentColMinWidth = 0;
        int currentColMaxWidth = 0;

        int totalHeight = 0;
        // int totalMinWidth = 0;
        // int totalMaxWidth = 0;

        int totalWidth = 0;
        int totalMinWidth = 0;
        int totalMaxWidth = 0;

        for(std::shared_ptr<Component> &comp : components) {
            if(comp->getHeight() > size.y) {
                comp->shrinkToHeight(size.y);
            }

            if(currentColHeight + comp->getHeight() > size.y) {
                cols.push_back(currentCol);
                currentCol.clear();

                totalWidth    += currentColWidth;
                totalMinWidth += currentColMinWidth;
                totalMaxWidth += currentColMaxWidth;

                totalHeight = std::max(totalHeight, currentColHeight);

                currentColHeight   = 0;
                currentColWidth    = 0;
                currentColMinWidth = 0;
                currentColMaxWidth = 0;
            }

            currentCol.push_back(comp);

            currentColHeight   += comp->getHeight();
            currentColWidth     = std::max(currentColWidth,    comp->getWidth());
            currentColMinWidth  = std::max(currentColMinWidth, comp->getMinWidth());
            currentColMaxWidth  = std::max(currentColMaxWidth, comp->getMaxWidth());
        }

        if(currentCol.size() > 0) {
            cols.push_back(currentCol);
            currentCol.clear();

            totalWidth    += currentColWidth;
            totalMinWidth += currentColMinWidth;
            totalMaxWidth += currentColMaxWidth;

            totalHeight = std::max(totalHeight, currentColHeight);

            currentColHeight   = 0;
            currentColWidth    = 0;
            currentColMinWidth = 0;
            currentColMaxWidth = 0;
        }
        
        int totalExtraWidth  = std::max(0, totalWidth - totalMinWidth);
        int totalGrowthWidth = std::max(0, totalMaxWidth - totalWidth);

        if(totalWidth < size.x) {
            const int increase          = std::min(size.x - totalWidth, totalGrowthWidth);
            const int totalGrowthBefore = totalGrowthWidth;

            // Increase to max or to fill space proporitonally
            for(std::vector<std::shared_ptr<Component>> &col : cols) {
                const int colGrowthWidth = getColGrowthWidth(col);

                const int incWidth = increase * (float(colGrowthWidth) / float(totalGrowthBefore));

                growColWidth(col, incWidth);
                totalWidth       += incWidth;
                totalGrowthWidth -= incWidth;
            }

            // Increase col with largest growth until fit (or no more growthWidth)
            while(totalWidth < size.x && totalGrowthWidth > 0) {
                // Get greateset width growth
                int greatestGrowthColIndex = 0;
                int greatestGrowth = getColGrowthWidth(cols[greatestGrowthColIndex]);

                for(int i = 1; i < cols.size(); i++) {
                    const std::vector<std::shared_ptr<NLUI::Component>> &col = cols[i];
                    const int colGrowth = getColGrowthWidth(col);

                    if(greatestGrowth < colGrowth) {
                        greatestGrowthColIndex = i;
                        greatestGrowth = colGrowth;
                    }
                }

                growColWidth(cols[greatestGrowthColIndex], 1);
                totalWidth++;
                totalGrowthWidth--;
            }
        } else if(totalWidth > size.x) {
            if(totalWidth - totalExtraWidth <= size.x) {
                // Remove proporitionally
                const int reduction = totalWidth - size.x;
                for(std::vector<std::shared_ptr<Component>> &col : cols) {
                    const int colExtraWidth = getColExtraWidth(col);

                    const int decWidth = reduction * (float(colExtraWidth) / float(totalExtraWidth));

                    shrinkColWidth(col, decWidth);
                    totalWidth -= decWidth;
                }

                // Remove 1 from col with larget extra width
                while(totalWidth > size.x) {
                    // Get largest extra
                    std::vector<std::shared_ptr<NLUI::Component>> &largestExtraCol = cols[0];
                    int largestExtraWidth = getColExtraWidth(largestExtraCol);
                    for(int i = 1; i < cols.size(); i++) {
                        const std::vector<std::shared_ptr<NLUI::Component>> &col = cols[i];
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
                // Set to mins // TODO should have function to minimise col widths
                for(std::vector<std::shared_ptr<Component>> &col : cols) {
                    const int decWidth = getColExtraWidth(col);

                    shrinkColWidth(col, decWidth);
                    totalWidth -= decWidth;
                }

                // Set to below mins (proportionately)
                const int reduction   = totalWidth - size.x;
                const int totalBefore = totalWidth;
                for(std::vector<std::shared_ptr<Component>> &col : cols) {
                    const int colWidth = getColWidth(col);

                    const int decWidth = reduction * (float(colWidth) / float(totalBefore));

                    shrinkColWidth(col, decWidth);
                    totalWidth -= decWidth;
                }

                // Reduce largest width by one until fit
                while(totalWidth > size.x) {
                    // Get largest width
                    int tallestColIndex = 0;
                    int tallestWidth = getColWidth(cols[tallestColIndex]);
                    for(int i = 1; i < cols.size(); i++) {
                        const std::vector<std::shared_ptr<NLUI::Component>> &col = cols[i];
                        const int colWidth = getColWidth(col);

                        if(tallestWidth < colWidth) {
                            tallestColIndex = i;
                            tallestWidth = colWidth;
                        }
                    }

                    // Take 1 from it
                    shrinkColWidth(cols[tallestColIndex], 1);
                    totalWidth--;
                }
            }
        }

        // TODO increase component width to fill full space
        // TODO maybe offser a flag for that? Pack?
        // TODO this is soooooo messy, make it a private function?
        for(const std::vector<std::shared_ptr<Component>> &col : cols) {
            const int colWidth = getColWidth(col);
            for(const std::shared_ptr<Component> &comp : col) {
                comp->growToWidth(colWidth);
            }
        }

        int x = pos.x + ((size.x - totalWidth) / 2);
        for(const std::vector<std::shared_ptr<Component>> &col : cols) {
            const int colWidth  = getColWidth(col);
            const int colHeight = getColHeight(col);

            int y = pos.y + ((size.y - colHeight) / 2);

            for(const std::shared_ptr<Component> &comp : col) {
                const int offset = (colWidth - comp->getWidth()) / 2;

                comp->setXPos(x + offset);
                comp->setYPos(y);

                y += comp->getHeight();
            }

            x += colWidth;
        }
    }
}

void NLUI::FlowPane::addComponent(const std::shared_ptr<Component> &component) {
    component->setParent(this);
    components.push_back(component);

    layoutRoot();
}

void shrinkRowHeight(const std::vector<std::shared_ptr<NLUI::Component>> &row, const int decHeight) {
    const int rowHeight  = getRowHeight(row);
    const int propHeight = rowHeight - decHeight; 

    for(const std::shared_ptr<NLUI::Component> &comp : row) {
        comp->shrinkToHeight(propHeight);
    }
}

void growRowHeight(const std::vector<std::shared_ptr<NLUI::Component>> &row, const int incHeight) {
    const int rowHeight  = getRowHeight(row);
    const int propHeight = rowHeight + incHeight;

    for(const std::shared_ptr<NLUI::Component> &comp : row) {
        comp->growToHeight(propHeight);
    }
}

void shrinkColWidth(const std::vector<std::shared_ptr<NLUI::Component>> &col, const int decWidth) {
    const int colWidth  = getColWidth(col);
    const int propWidth = colWidth - decWidth;

    for(const std::shared_ptr<NLUI::Component> &comp : col) {
        comp->shrinkToWidth(propWidth);
    }
}

void growColWidth(const std::vector<std::shared_ptr<NLUI::Component>> &col, const int incWidth) {
    const int colWidth  = getColWidth(col);
    const int propWidth = colWidth + incWidth;

    for(const std::shared_ptr<NLUI::Component> &comp : col) {
        comp->growToWidth(propWidth);
    }
}

int getRowWidth(const std::vector<std::shared_ptr<NLUI::Component>> &row) {
    int rowWidth = 0;
    for(const std::shared_ptr<NLUI::Component> &comp : row) {
        rowWidth += comp->getWidth();
    }

    return rowWidth;
}

int getRowMaxWidth(const std::vector<std::shared_ptr<NLUI::Component>> &row) {
    int rowMaxWidth = 0;
    for(const std::shared_ptr<NLUI::Component> &comp : row) {
        rowMaxWidth += comp->getMaxWidth();
    }

    return rowMaxWidth;
}

int getRowGrowthWidth(const std::vector<std::shared_ptr<NLUI::Component>> &row) {
    return std::max(0, getRowMaxWidth(row) - getRowHeight(row));
}

int getRowHeight(const std::vector<std::shared_ptr<NLUI::Component>> &row) {
    int rowHeight = 0;
    for(const std::shared_ptr<NLUI::Component> &comp : row) {
        rowHeight = std::max(rowHeight, comp->getHeight());
    }

    return rowHeight;
}

int getRowMinHeight(const std::vector<std::shared_ptr<NLUI::Component>> &row) {
    int rowMinHeight = 0;
    for(const std::shared_ptr<NLUI::Component> &comp : row) {
        rowMinHeight = std::max(rowMinHeight, comp->getMinHeight());
    }

    return rowMinHeight;
}

int getRowMaxHeight(const std::vector<std::shared_ptr<NLUI::Component>> &row) {
    int rowMaxHeight = 0;
    for(const std::shared_ptr<NLUI::Component> &comp : row) {
        rowMaxHeight = std::max(rowMaxHeight, comp->getMaxHeight());
    }

    return rowMaxHeight;
}

int getRowExtraHeight(const std::vector<std::shared_ptr<NLUI::Component>> &row) {
    return std::max(0, getRowHeight(row) - getRowMinHeight(row));
}

int getRowGrowthHeight(const std::vector<std::shared_ptr<NLUI::Component>> &row) {
    return std::max(0, getRowMaxHeight(row) - getRowHeight(row));
}

int getColWidth(const std::vector<std::shared_ptr<NLUI::Component>> &col) {
    int colWidth = 0;
    for(const std::shared_ptr<NLUI::Component> &comp : col) {
        colWidth = std::max(colWidth, comp->getWidth());
    }

    return colWidth;
}

int getColMinWidth(const std::vector<std::shared_ptr<NLUI::Component>> &col) {
    int colMinWidth = 0;
    for(const std::shared_ptr<NLUI::Component> &comp : col) {
        colMinWidth = std::max(colMinWidth, comp->getMinWidth());
    }

    return colMinWidth;
}

int getColMaxWidth(const std::vector<std::shared_ptr<NLUI::Component>> &col) {
    int colMaxWidth = 0;
    for(const std::shared_ptr<NLUI::Component> &comp : col) {
        colMaxWidth = std::max(colMaxWidth, comp->getMaxWidth());
    }

    return colMaxWidth;
}

int getColExtraWidth(const std::vector<std::shared_ptr<NLUI::Component>> &col) {
    return std::max(0, getColWidth(col) - getColMinWidth(col));
}

int getColGrowthWidth(const std::vector<std::shared_ptr<NLUI::Component>> &col) {
    return std::max(0, getColMaxWidth(col) - getColWidth(col));
}

int getColHeight(const std::vector<std::shared_ptr<NLUI::Component>> &col) {
    int colHeight = 0;
    for(const std::shared_ptr<NLUI::Component> &comp : col) {
        colHeight += comp->getHeight();
    }

    return colHeight;
}

int getColMaxHeight(const std::vector<std::shared_ptr<NLUI::Component>> &col) {
    int colMinHeight = 0;
    for(const std::shared_ptr<NLUI::Component> &comp : col) {
        colMinHeight += comp->getMaxHeight();
    }

    return colMinHeight;

}

int getColGrowthHeight(const std::vector<std::shared_ptr<NLUI::Component>> &col) {
    return std::max(0, getColMaxHeight(col) - getColHeight(col));
}