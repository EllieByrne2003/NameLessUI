#pragma once

// Includes from standard
#include <filesystem>

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


// Type aliases


namespace NLUI {
    class Component {
    private:

    protected:
        ivec2 pos;
        ivec2 size;

    public:
        Component();
        ~Component();

        static Component * readComponent(Logger &logger, const json &jsonComponent, const std::filesystem::path &dirPath);
        static Component * readComponent(Logger &logger, const std::filesystem::path &path);

        virtual void draw() = 0;

        // Minimum size
        virtual void  getMinimumSize(int &minimumWidth, int &minimumHeight) const = 0;
        virtual ivec2 getMinimumSize() const = 0;

        virtual int getMinimumWidth() const = 0;
        virtual int getMinimumHeight() const = 0;

        // Maximum size
        virtual void  getMaximumSize(const int availableWidth, const int availableHeight, int &maximumWidth, int &maximumHeight) const = 0;
        virtual ivec2 getMaximumSize(const int availableWidth, const int availableHeight) const = 0;

        virtual void  getMaximumSize(const ivec2 &availableSize, int &maximumWidth, int &maximumHeight) const = 0;
        virtual ivec2 getMaximumSize(const ivec2 &availableSize) const = 0;

        virtual int getMaximumWidth(const int availableWidth) const = 0;
        virtual int getMaximumHeight(const int availableHeight) const = 0;

        // Preferred size
        virtual void  getPreferredSize(const int availableWidth, const int availableHeight, int &preferredWidth, int &preferredHeight) const = 0;
        virtual ivec2 getPreferredSize(const int availableWidth, const int availableHeight) const = 0;

        virtual void  getPreferredSize(const ivec2 &availableSize, int &preferredWidth, int &preferredHeight) const = 0;
        virtual ivec2 getPreferredSize(const ivec2 &availableSize) const = 0;

        virtual int getPreferredWidth(const int availableWidth) const = 0;
        virtual int getPreferredHeight(const int availableHeight) const = 0;

        // Current size
        void  getSize(int &width, int &height) const;
        ivec2 getSize() const;

        int getWidth() const;
        int getHeight() const;

        // Resizing/positioning
        virtual void setSize(const int width, const int height);
        virtual void setSize(const ivec2 &size);

        virtual void setWidth(const int width);
        virtual void setHeight(const int height);
        
        void setPos(const int xPos, const int yPos);
        void setPos(const ivec2 &pos);
        
        virtual bool mouseInside(const double xPos, const double yPos);
    };
};