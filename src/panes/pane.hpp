#pragma once

// Includes from standard
#include <memory>

// Includes from third party libraries


// Includes from personal libraries


// Includes from project
#include "../component/component.hpp"
#include "../container/container.hpp"

// Forward declarations


// Type aliases


namespace NLUI {
    class Pane : public Component, public Container {
    private:

    protected:
        std::shared_ptr<Component> focus = nullptr;

    public:

    /*----------  Functions  ----------*/
    private:

    protected:
        Pane(const glm::ivec2 &minSize, const glm::ivec2 &maxSize);

    public:
        virtual ~Pane() = 0;

        // Overridden from Component
        // virtual void draw() override;

        // // Minimum size
        // virtual void  getMinimumSize(int &minimumWidth, int &minimumHeight) const override;
        // virtual ivec2 getMinimumSize() const override;

        // virtual int getMinimumWidth() const override;
        // virtual int getMinimumHeight() const override;

        // // Maximum size
        // virtual void  getMaximumSize(const int availableWidth, const int availableHeight, int &maximumWidth, int &maximumHeight) const override;
        // virtual ivec2 getMaximumSize(const int availableWidth, const int availableHeight) const override;

        // virtual void  getMaximumSize(const ivec2 &availableSize, int &maximumWidth, int &maximumHeight) const override;
        // virtual ivec2 getMaximumSize(const ivec2 &availableSize) const override;

        // virtual int getMaximumWidth(const int availableWidth) const override;
        // virtual int getMaximumHeight(const int availableHeight) const override;

        // // Preferred size
        // virtual void  getPreferredSize(const int availableWidth, const int availableHeight, int &preferredWidth, int &preferredHeight) const override;
        // virtual ivec2 getPreferredSize(const int availableWidth, const int availableHeight) const override;

        // virtual void  getPreferredSize(const ivec2 &availableSize, int &preferredWidth, int &preferredHeight) const override;
        // virtual ivec2 getPreferredSize(const ivec2 &availableSize) const override;

        // virtual int getPreferredWidth(const int availableWidth) const override;
        // virtual int getPreferredHeight(const int availableHeight) const override;

        // Resizing/positioning
        // virtual void setSize(const int width, const int height) override;
        // virtual void setSize(const ivec2 &size) override;

        // virtual void setWidth(const int width) override;
        // virtual void setHeight(const int height) override;

        // virtual void resize() override;
        
        // virtual bool mouseInside(const double xPos, const double yPos) override;

        // Override from Container
        // handle removal
        // virtual void removeComponent(Component *component) override;

        // Handle children changing sizes
        // virtual void validate() override;
    };
};