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

    class BoxPane : public Pane {
    private:
        std::vector<std::shared_ptr<Component>> components;

        // TODO make funtions to set these
        bool horizontal;
        // vAlignment  vAlignment  = vAlignment::Top;
        // hAlignment  hAlignment  = hAlignment::Left;

    protected:

    public:

    /*----------  Functions  ----------*/
    private:

    protected:
        BoxPane(const bool horizontal, const glm::ivec2 &minSize, const glm::ivec2 &maxSize);

    public:
        virtual ~BoxPane() override;

        static std::shared_ptr<BoxPane> create(const bool horizontal = true, const glm::ivec2 &minSize = glm::ivec2(0, 0), const glm::ivec2 &maxSize = glm::ivec2(INT_MAX, INT_MAX));

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

        virtual void doLayout() override;

        // New functions
        void addComponent(const std::shared_ptr<Component> &component);
    };
};