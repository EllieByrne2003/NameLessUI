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
namespace NLUI { class Container; };

// Type aliases
typedef unsigned int GLuint;

namespace NLUI {
    class BaseComponent : public Component {
        friend class Container; // Can need to access private variables // TODO don't like this, but changes to window needed
    private:
        glm::vec4 backgroundColour = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

    protected:
        Container *parent = nullptr;
        
        glm::ivec2 pos;

        // TODO make these private
        glm::ivec2 size; 
        glm::ivec2 minSize;
        glm::ivec2 maxSize;

    public:

    /*----------  Functions  ----------*/
    private:

    protected:
        BaseComponent(const glm::ivec2 &minSize, const glm::ivec2 &maxSize);

    public:
        virtual ~BaseComponent() = 0;

        virtual void setParent(Container *parent) final;
        virtual void removeParent() final;
        virtual void layoutRoot() override;

        // Function to draw self
        virtual void draw() const override;

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

        virtual void getMinSize(int &minWidth, int &minHeight) const override;
        virtual glm::ivec2 getMinSize() const override;
        virtual int getMinWidth() const override;
        virtual int getMinHeight() const override;

        virtual void getMaxSize(int &maxWidth, int &maxHeight) const override;
        virtual glm::ivec2 getMaxSize() const override;
        virtual int getMaxWidth() const override;
        virtual int getMaxHeight() const override;

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
        
        // For handling focus
        virtual bool mouseInside(const double xPos, const double yPos) override;

        // Coloured backgrounds
        virtual glm::vec4 getBackgroundColour() const final;

        virtual void setBackgroundColour(const float r, const float g, const float b, const float a) final;
        virtual void setBackgroundColour(const float r, const float g, const float b) final;

        virtual void setBackgroundColour(const glm::vec4 &backgroundColour) final;
    };
};