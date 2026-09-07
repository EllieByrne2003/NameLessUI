#pragma once

// Includes from standard


// Includes from third party libraries
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// Includes from personal libraries
#include <NLUT/logger/logger.hpp>
using Logger = NLUT::Logger;

// Includes from project
#include "component.hpp"

// Forward declarations


// Type aliases
typedef unsigned int GLuint;

namespace NLUI {
    class NullComponent : public Component {
    private:
        NullComponent();

    protected:

    public:
        virtual ~NullComponent();

        static std::shared_ptr<NullComponent> & getInstance();

        virtual void setParent(Container *parent) final;
        virtual void removeParent() final;
        virtual void layoutRoot() final;

        // Function to draw self
        virtual void draw() const final;

        // Functions to set sizes
        virtual void setSize(const int width, const int height) final;
        virtual void setSize(const glm::ivec2 &size) final;
        virtual void setWidth(const int width) final;
        virtual void setHeight(const int height) final;

        // Functions to perform layout tasks
        virtual void proposeSize(const int propWidth, const int propHeight) final;
        virtual void proposeSize(const glm::ivec2 &propSize) final;
        virtual void proposeWidth(const int propWidth) final;
        virtual void proposeHeight(const int propHeight) final;

        // TODO consider checks for growing and shrinking to make sure sizes increasing/decreasing as expected
        virtual void shrinkSize(const int decWidth, const int decHeight) final;
        virtual void shrinkSize(const glm::ivec2 &decSize) final;
        virtual void shrinkWidth(const int decWidth) final;
        virtual void shrinkHeight(const int decHeight) final;

        virtual void shrinkToSize(const int propWidth, const int propHeight) final;
        virtual void shrinkToSize(const glm::ivec2 &propSize) final;
        virtual void shrinkToWidth(const int propWidth) final;
        virtual void shrinkToHeight(const int propHeight) final;

        virtual void growSize(const int incWidth, const int incHeight) final;
        virtual void growSize(const glm::ivec2 &incSize) final;
        virtual void growWidth(const int incWidth) final;
        virtual void growHeight(const int incHeight) final;

        virtual void growToSize(const int propWidth, const int propHeight) final;
        virtual void growToSize(const glm::ivec2 &propSize) final;
        virtual void growToWidth(const int propWidth) final;
        virtual void growToHeight(const int propHeight) final;

        // Functions to set positions
        virtual void setPos(const int xPos, const int yPos) final;
        virtual void setPos(const glm::ivec2 &pos) final;
        virtual void setXPos(const int xPos) final;
        virtual void setYPos(const int yPos) final;

        // Functions to set limits
        virtual void setMinSize(const int minWidth, const int minHeight) final;
        virtual void setMinSize(const glm::ivec2 &minSize) final;
        virtual void setMinWidth(const int minWidth) final;
        virtual void setMinHeight(const int minHeight) final;

        virtual void setMaxSize(const int maxWidth, const int maxHeight) final;
        virtual void setMaxSize(const glm::ivec2 &maxSize) final;
        virtual void setMaxWidth(const int maxWidth) final;
        virtual void setMaxHeight(const int maxHeight) final;

        // Functions to get sizes and data on them
        virtual void getSize(int &width, int &height) const final;
        virtual glm::ivec2 getSize() const final;
        virtual int getWidth() const final;
        virtual int getHeight() const final;

        virtual void getPrefSize(int &prefWidth, int &prefHeight) const final;
        virtual glm::ivec2 getPrefSize() const final;
        virtual int getPrefWidth() const final;
        virtual int getPrefHeight() const final;

        virtual void getMinSize(int &minWidth, int &minHeight) const final;
        virtual glm::ivec2 getMinSize() const final;
        virtual int getMinWidth() const final;
        virtual int getMinHeight() const final;

        virtual void getMaxSize(int &maxWidth, int &maxHeight) const final;
        virtual glm::ivec2 getMaxSize() const final;
        virtual int getMaxWidth() const final;
        virtual int getMaxHeight() const final;

        virtual void getExtraSize(int &extraWidth, int &extraHeight) const final;
        virtual glm::ivec2 getExtraSize() const final;
        virtual int getExtraWidth() const final;
        virtual int getExtraHeight() const final;

        virtual void getGrowthSize(int &growthWidth, int &growthHeight) const final;
        virtual glm::ivec2 getGrowthSize() const final;
        virtual int getGrowthWidth() const final;
        virtual int getGrowthHeight() const final;

        // Functions to get positions
        virtual void getPos(int &xPos, int &yPos) const final;
        virtual glm::ivec2 getPos() const final;
        virtual int getXPos() const final;
        virtual int getYPos() const final;

        // Handle size changes
        virtual void onResize() final;
        
        // For handling focus
        virtual bool mouseInside(const double xPos, const double yPos) final;

        // Coloured backgrounds
        virtual glm::vec4 getBackgroundColour() const final;

        virtual void setBackgroundColour(const float r, const float g, const float b, const float a) final;
        virtual void setBackgroundColour(const float r, const float g, const float b) final;

        virtual void setBackgroundColour(const glm::vec4 &backgroundColour) final;
    };
};