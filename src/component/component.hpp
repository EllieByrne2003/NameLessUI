#pragma once

// Includes from standard
#include <filesystem>
#include <memory>
#include <limits>

// Includes from third party libraries
#include <glm/glm.hpp>
using namespace glm;

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
        Container *parent = nullptr;

        ivec2 minimumSize = ivec2(0, 0);

        vec4 backgroundColour = vec4(0.0f, 0.0f, 0.0f, 0.0f);

    protected:
        ivec2 pos;
        ivec2 size;

    public:
        Component();
        virtual ~Component() = 0;

        void setParent(Container *parent);
        void removeParent();
        
        void validateParent();


        // static Component * readComponent(Logger &logger, const json &jsonComponent, const std::filesystem::path &dirPath);
        // static Component * readComponent(Logger &logger, const std::filesystem::path &path);

        virtual void draw() const;

        // Minimum size
        virtual void  getMinimumSize(int &minimumWidth, int &minimumHeight) const;
        virtual ivec2 getMinimumSize() const;

        virtual int getMinimumWidth() const;
        virtual int getMinimumHeight() const;

        void setMinimumSize(const int minimumWidth, const int minimumHeight);
        void setMinimumSize(const ivec2 &minimumSize);

        void setMinimumWidth(const int minimumWidth);
        void setMinimumHeight(const int minimumHeight);

        // TODO may be use this later?
        // // Maximum size
        // virtual void  getMaximumSize(const int availableWidth, const int availableHeight, int &maximumWidth, int &maximumHeight) const = 0;
        // virtual ivec2 getMaximumSize(const int availableWidth, const int availableHeight) const = 0;

        // virtual void  getMaximumSize(const ivec2 &availableSize, int &maximumWidth, int &maximumHeight) const = 0;
        // virtual ivec2 getMaximumSize(const ivec2 &availableSize) const = 0;

        // virtual int getMaximumWidth(const int availableWidth) const = 0;
        // virtual int getMaximumHeight(const int availableHeight) const = 0;

        // Preferred size
        // virtual void  getPreferredSize(const int availableWidth, const int availableHeight, int &preferredWidth, int &preferredHeight) const = 0;
        // virtual ivec2 getPreferredSize(const int availableWidth, const int availableHeight) const = 0;

        // virtual void  getPreferredSize(const ivec2 &availableSize, int &preferredWidth, int &preferredHeight) const = 0;
        // virtual ivec2 getPreferredSize(const ivec2 &availableSize) const = 0;

        // virtual int getPreferredWidth(const int availableWidth) const = 0;
        // virtual int getPreferredHeight(const int availableHeight) const = 0;

        virtual void getPreferredSize(int &minimumWidth, int &minimumHeight) const = 0;
        virtual ivec2 getPreferredSize() const = 0;

        virtual int getPreferredWidth() const = 0;
        virtual int getPreferredHeight() const = 0;

        // Current size
        void  getSize(int &width, int &height) const;
        ivec2 getSize() const;

        int getWidth() const;
        int getHeight() const;

        // Current position
        void  getPos(int &xPos, int &yPos) const;
        ivec2 getPos() const;

        int getXPos() const;
        int getYPos() const;

        // Resizing/positioning
        void setSize(const int width, const int height);
        void setSize(const ivec2 &size);

        void setWidth(const int width);
        void setHeight(const int height);
        
        void setPos(const int xPos, const int yPos);
        void setPos(const ivec2 &pos);

        void setXPos(const int xPos);
        void setYPos(const int yPos);

        virtual void resize() = 0;
        
        // For handling focus
        virtual bool mouseInside(const double xPos, const double yPos);

        // Coloured backgrounds
        vec4 getBackgroundColour() const;

        void setBackgroundColour(const float r, const float g, const float b, const float a);
        void setBackgroundColour(const float r, const float g, const float b);

        void setBackgroundColour(const vec4 &backgroundColour);
    };
};