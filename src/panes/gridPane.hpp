#pragma once

// Includes from standard
#include <memory>

// Includes from third party libraries


// Includes from personal libraries


// Includes from project
#include "pane.hpp"

// Forward declarations


// Type aliases


namespace NLUI {
    class GridPane : public Pane {
    private:
        std::shared_ptr<Component> *components;

        // TODO update this be unsigned and to have getters
        const int rows;
        const int cols;

    protected:

    public:

    /*----------  Functions  ----------*/
    private:
        void shrinkRowHeight(const int row, const int decHeight);
        void growRowHeight(const int row, const int incHeight);

        void shrinkColWidth(const int col, const int decWidth);
        void growColWidth(const int col, const int incWidth);

        int getRowHeight(const int row) const;
        int getRowPrefHeight(const int row) const;
        int getRowMinHeight(const int row) const;
        int getRowMaxHeight(const int row) const;
        int getRowExtraHeight(const int row) const;
        int getRowGrowthHeight(const int row) const;

        int getColWidth(const int col) const;
        int getColPrefWidth(const int col) const;
        int getColMinWidth(const int col) const;
        int getColMaxWidth(const int col) const;
        int getColExtraWidth(const int col) const;
        int getColGrowthWidth(const int col) const;

    protected:
        GridPane(const int rows, const int cols, const glm::ivec2 &minSize, const glm::ivec2 &maxSize);

    public:
        virtual ~GridPane() override;

        static std::shared_ptr<GridPane> create(const int rows, const int cols, const glm::ivec2 &minSize = glm::ivec2(0, 0), const glm::ivec2 &maxSize = glm::ivec2(INT_MAX, INT_MAX));

        // Overridden from Component
        virtual void draw() const override;

        virtual void getPrefSize(int &prefWidth, int &prefHeight) const override;
        virtual glm::ivec2 getPrefSize() const override;
        virtual int getPrefWidth() const override;
        virtual int getPrefHeight() const override;

        virtual void getMinSize(int &minWidth, int &minHeight) const override;
        virtual glm::ivec2 getMinSize() const override;
        virtual int getMinWidth() const override;
        virtual int getMinHeight() const override;

        virtual void getMaxSize(int &maxWidth, int &maxHeight) const override;
        virtual glm::ivec2 getMaxSize() const override;
        virtual int getMaxWidth() const override;
        virtual int getMaxHeight() const override;
        
        virtual bool mouseInside(const double xPos, const double yPos) override;

        // Override from Container
        virtual void removeComponent(const std::shared_ptr<Component> &component) override;
        virtual void removeComponent(Component *const component) override;

        virtual void doLayout(const bool forceWidth, const bool forceHeight) override;

        // New functions
        void addComponent(const std::shared_ptr<Component> &component, const int row, const int col); // TODO one to remove it
    };
};