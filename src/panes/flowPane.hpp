#pragma once

// Includes from standard
#include <memory>
#include <vector>

// Includes from third party libraries


// Includes from personal libraries


// Includes from project
#include "pane.hpp"

// Forward declarations


// Type aliases


namespace NLUI {
    enum class Orientation {
        Horizontal, // Components placed left to right
        Vertical    // Components placed top to bottom
    };

    // enum class vAlignment {
    //     Top,
    //     Bottom,
    //     Centre,
    //     Stretch
    // };

    // enum class hAlignment {
    //     Left,
    //     Right,
    //     Centre,
    //     Stretch
    // };

    class FlowPane : public Pane {
    private:
        std::vector<std::shared_ptr<Component>> components;

        // TODO make funtions to set these
        Orientation orientation;
        // vAlignment  vAlignment  = vAlignment::Top;
        // hAlignment  hAlignment  = hAlignment::Left;

    protected:

    public:

    /*----------  Functions  ----------*/
    private:

    protected:
        FlowPane(const Orientation orientation, const glm::ivec2 &minSize, const glm::ivec2 &maxSize);

    public:
        virtual ~FlowPane() override;

        static std::shared_ptr<FlowPane> create(const Orientation orientation = Orientation::Horizontal, const glm::ivec2 &minSize = glm::ivec2(0, 0), const glm::ivec2 &maxSize = glm::ivec2(INT_MAX, INT_MAX));

        // Overridden from Component
        virtual void draw() const override;

        // Minimum size
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

        virtual int getPreferredWidth() const override;
        virtual int getPreferredHeight() const override;

        // Resizing/positioning
        virtual void resize() override;
        
        virtual bool mouseInside(const double xPos, const double yPos) override;

        // New functions
        void addComponent(const std::shared_ptr<Component> &component);

        // Override from Container
        // handle removal
        virtual void removeComponent(const std::shared_ptr<Component> &component) override;
        virtual void removeComponent(Component *const component) override;

        // Handle children changing sizes
        virtual void validate() override;
    };
};