#pragma once

// Includes from standard


// Includes from third party libraries


// Includes from personal libraries


// Includes from project
#include "pane.hpp"

// Forward declarations


// Type aliases


namespace NLUI {
    class GridPane : public Pane {
    private:
        Component **components;

        // TODO update this be unsigned and to have getters
        const int rows;
        const int columns;

    protected:

    public:
        GridPane(const int rows, const int columns);
        virtual ~GridPane() override;

        // Overridden from Component
        virtual void draw() const override;

        // Minimum size
        virtual void  getMinimumSize(int &minimumWidth, int &minimumHeight) const override;
        virtual glm::ivec2 getMinimumSize() const override;

        virtual int getMinimumWidth() const override;
        virtual int getMinimumHeight() const override;

        // // Maximum size
        // virtual void  getMaximumSize(const int availableWidth, const int availableHeight, int &maximumWidth, int &maximumHeight) const override;
        // virtual ivec2 getMaximumSize(const int availableWidth, const int availableHeight) const override;

        // virtual void  getMaximumSize(const ivec2 &availableSize, int &maximumWidth, int &maximumHeight) const override;
        // virtual ivec2 getMaximumSize(const ivec2 &availableSize) const override;

        // virtual int getMaximumWidth(const int availableWidth) const override;
        // virtual int getMaximumHeight(const int availableHeight) const override;

        // Preferred size
        // virtual void  getPreferredSize(const int availableWidth, const int availableHeight, int &preferredWidth, int &preferredHeight) const override;
        // virtual ivec2 getPreferredSize(const int availableWidth, const int availableHeight) const override;

        // virtual void  getPreferredSize(const ivec2 &availableSize, int &preferredWidth, int &preferredHeight) const override;
        // virtual ivec2 getPreferredSize(const ivec2 &availableSize) const override;

        // virtual int getPreferredWidth(const int availableWidth) const override;
        // virtual int getPreferredHeight(const int availableHeight) const override;

        virtual void getPreferredSize(int &minimumWidth, int &minimumHeight) const override;
        virtual glm::ivec2 getPreferredSize() const override;

        virtual int getPreferredWidth() const override;
        virtual int getPreferredHeight() const override;

        // Resizing/positioning
        virtual void resize() override;
        
        virtual bool mouseInside(const double xPos, const double yPos) override;

        // New functions
        void addComponent(Component *component, const int row, const int col); // TODO one to remove it

        // TODO start using the below everywhere
        int getRowMinimumHeight(const int row) const; // TODO implement
        int getRowPreferredHeight(const int row) const;

        int getColMinimumWidth(const int col) const; // TODO implement
        int getColPreferredWidth(const int col) const;

        // Override from Container
        // handle removal
        virtual void removeComponent(Component *component) override;

        // Handle children changing sizes
        virtual void validate() override;
    };
};