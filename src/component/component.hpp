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
        friend class Container; // Can need to access private variables // TODO don't like this, but changes to window needed
    private:
        Container *parent = nullptr;

        glm::vec4 backgroundColour = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

    protected:
        glm::ivec2 pos;

        // TODO make these private
        glm::ivec2 size; 
        glm::ivec2 minSize;
        glm::ivec2 maxSize;

    public:

    /*----------  Functions  ----------*/
    private:

    protected:
        Component(const glm::ivec2 &minSize, const glm::ivec2 &maxSize);

        // Functions to set sizes
        void setSize(const int width, const int height);
        void setSize(const glm::ivec2 &size);
        void setWidth(const int width);
        void setHeight(const int height);

    public:
        virtual ~Component() = 0;

        void setParent(Container *parent);
        void removeParent();
        void validateParent();

        // Function to draw self
        virtual void draw() const;

        // Functions to perform layout tasks
        virtual void proposeSize(const int propWidth, const int propHeight);
        virtual void proposeSize(const glm::ivec2 &propSize);
        virtual void proposeWidth(const int propWidth);
        virtual void proposeHeight(const int propHeight);

        void shrinkSize(const int decWidth, const int decHeight);
        void shrinkSize(const glm::ivec2 &decSize);
        void shrinkWidth(const int decWidth);
        void shrinkHeight(const int decHeight);

        void growSize(const int incWidth, const int incHeight);
        void growSize(const glm::ivec2 &incSize);
        void growWidth(const int incWidth);
        void growHeight(const int incHeight);

        // Functions to set positions
        void setPos(const int xPos, const int yPos);
        void setPos(const glm::ivec2 &pos);
        void setXPos(const int xPos);
        void setYPos(const int yPos);

        // Functions to set limits
        void setMinSize(const int minWidth, const int minHeight);
        void setMinSize(const glm::ivec2 &minSize);
        void setMinWidth(const int minWidth);
        void setMinHeight(const int minHeight);

        void setMaxSize(const int maxWidth, const int maxHeight);
        void setMaxSize(const glm::ivec2 &maxSize);
        void setMaxWidth(const int maxWidth);
        void setMaxHeight(const int maxHeight);

        // Functions to get sizes and data on them
        void getSize(int &width, int &height) const;
        glm::ivec2 getSize() const;
        int getWidth() const;
        int getHeight() const;

        virtual void getPrefSize(int &prefWidth, int &prefHeight) const = 0;
        virtual glm::ivec2 getPrefSize() const = 0;
        virtual int getPrefWidth() const = 0;
        virtual int getPrefHeight() const = 0;

        virtual void getMinSize(int &minWidth, int &minHeight) const;
        virtual glm::ivec2 getMinSize() const;
        virtual int getMinWidth() const;
        virtual int getMinHeight() const;

        virtual void getMaxSize(int &maxWidth, int &maxHeight) const;
        virtual glm::ivec2 getmaxSize() const;
        virtual int getMaxWidth() const;
        virtual int getMaxHeight() const;

        void getExtraSize(int &extraWidth, int &extraHeight) const;
        glm::ivec2 getExtraSize() const;
        int getExtraWidth() const;
        int getExtraHeight() const;

        void getGrowthSize(int &growthWidth, int &growthHeight) const;
        glm::ivec2 getGrowthSize() const;
        int getGrowthWidth() const;
        int getGrowthHeight() const;

        // Functions to get positions
        void getPos(int &xPos, int &yPos) const;
        glm::ivec2 getPos() const;
        int getXPos() const;
        int getYPos() const;

        // Handle size changes
        virtual void onResize() = 0;
        
        // For handling focus
        virtual bool mouseInside(const double xPos, const double yPos);

        // Coloured backgrounds
        glm::vec4 getBackgroundColour() const;

        void setBackgroundColour(const float r, const float g, const float b, const float a);
        void setBackgroundColour(const float r, const float g, const float b);

        void setBackgroundColour(const glm::vec4 &backgroundColour);
    };
};