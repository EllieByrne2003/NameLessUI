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


// Forward declarations
namespace NLUI { class Container; };

// Type aliases
typedef unsigned int GLuint;

namespace NLUI {
    class Component {
    private:

    protected:
        Component();

    public:
        virtual ~Component() = 0;

        virtual void setParent(Container *parent) = 0;
        virtual void removeParent() = 0;
        virtual void layoutRoot() = 0;

        // Function to draw self
        virtual void draw() const = 0;

        // Functions to set sizes
        virtual void setSize(const int width, const int height) = 0;
        virtual void setSize(const glm::ivec2 &size) = 0;
        virtual void setWidth(const int width) = 0;
        virtual void setHeight(const int height) = 0;

        // Functions to perform layout tasks
        virtual void proposeSize(const int propWidth, const int propHeight) = 0;
        virtual void proposeSize(const glm::ivec2 &propSize) = 0;
        virtual void proposeWidth(const int propWidth) = 0;
        virtual void proposeHeight(const int propHeight) = 0;

        virtual void shrinkSize(const int decWidth, const int decHeight) = 0;
        virtual void shrinkSize(const glm::ivec2 &decSize) = 0;
        virtual void shrinkWidth(const int decWidth) = 0;
        virtual void shrinkHeight(const int decHeight) = 0;

        virtual void shrinkToSize(const int propWidth, const int propHeight) = 0;
        virtual void shrinkToSize(const glm::ivec2 &propSize) = 0;
        virtual void shrinkToWidth(const int propWidth) = 0;
        virtual void shrinkToHeight(const int propHeight) = 0;

        virtual void growSize(const int incWidth, const int incHeight) = 0;
        virtual void growSize(const glm::ivec2 &incSize) = 0;
        virtual void growWidth(const int incWidth) = 0;
        virtual void growHeight(const int incHeight) = 0;

        virtual void growToSize(const int propWidth, const int propHeight) = 0;
        virtual void growToSize(const glm::ivec2 &propSize) = 0;
        virtual void growToWidth(const int propWidth) = 0;
        virtual void growToHeight(const int propHeight) = 0;

        // Functions to set positions
        virtual void setPos(const int xPos, const int yPos) = 0;
        virtual void setPos(const glm::ivec2 &pos) = 0;
        virtual void setXPos(const int xPos) = 0;
        virtual void setYPos(const int yPos) = 0;

        // Functions to set limits
        virtual void setMinSize(const int minWidth, const int minHeight) = 0;
        virtual void setMinSize(const glm::ivec2 &minSize) = 0;
        virtual void setMinWidth(const int minWidth) = 0;
        virtual void setMinHeight(const int minHeight) = 0;

        virtual void setMaxSize(const int maxWidth, const int maxHeight) = 0;
        virtual void setMaxSize(const glm::ivec2 &maxSize) = 0;
        virtual void setMaxWidth(const int maxWidth) = 0;
        virtual void setMaxHeight(const int maxHeight) = 0;

        // Functions to get sizes and data on them
        virtual void getSize(int &width, int &height) const = 0;
        virtual glm::ivec2 getSize() const = 0;
        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;

        virtual void getPrefSize(int &prefWidth, int &prefHeight) const = 0;
        virtual glm::ivec2 getPrefSize() const = 0;
        virtual int getPrefWidth() const = 0;
        virtual int getPrefHeight() const = 0;

        virtual void getMinSize(int &minWidth, int &minHeight) const = 0;
        virtual glm::ivec2 getMinSize() const = 0;
        virtual int getMinWidth() const = 0;
        virtual int getMinHeight() const = 0;

        virtual void getMaxSize(int &maxWidth, int &maxHeight) const = 0;
        virtual glm::ivec2 getMaxSize() const = 0;
        virtual int getMaxWidth() const = 0;
        virtual int getMaxHeight() const = 0;

        virtual void getExtraSize(int &extraWidth, int &extraHeight) const = 0;
        virtual glm::ivec2 getExtraSize() const = 0;
        virtual int getExtraWidth() const = 0;
        virtual int getExtraHeight() const = 0;

        virtual void getGrowthSize(int &growthWidth, int &growthHeight) const = 0;
        virtual glm::ivec2 getGrowthSize() const = 0;
        virtual int getGrowthWidth() const = 0;
        virtual int getGrowthHeight() const = 0;

        // Functions to get positions
        virtual void getPos(int &xPos, int &yPos) const = 0;
        virtual glm::ivec2 getPos() const = 0;
        virtual int getXPos() const = 0;
        virtual int getYPos() const = 0;

        // Handle size changes
        virtual void onResize() = 0;
        
        // For handling focus
        virtual bool mouseInside(const double xPos, const double yPos) = 0;

        // Coloured backgrounds
        virtual glm::vec4 getBackgroundColour() const = 0;

        virtual void setBackgroundColour(const float r, const float g, const float b, const float a) = 0;
        virtual void setBackgroundColour(const float r, const float g, const float b) = 0;

        virtual void setBackgroundColour(const glm::vec4 &backgroundColour) = 0;
    };
};