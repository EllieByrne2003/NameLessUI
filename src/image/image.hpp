#pragma once

// Includes from standard
#include <filesystem>
#include <memory>

// Includes from third party libraries
#include <glm/glm.hpp>

// Includes from personal libraries
#include <NLUT/files/textures.hpp>

// Includes from project
#include "../component/component.hpp"

// Forward declarations


// Type aliases
typedef unsigned int GLuint;


namespace NLUI {
    class Image : public Component {
    private:
        const GLuint     imageID;
        const glm::uvec2 imageSize; // TODO might not need to keep this (maybe keep as preferred size)

        // TODO the threee below could have functions to change them
        const unsigned int magLimit;
        const unsigned int minLimit;

        const bool keepRatio;

    protected:

    public:

    /*----------  Functions  ----------*/
    private:

    protected:
        Image(const GLuint imageID, const glm::uvec2 &imageSize, const unsigned int magLimit, const unsigned int minLimit, const bool keepRatio);

    public:
        virtual ~Image() override;

        static std::shared_ptr<Image> create(const std::filesystem::path &path, const unsigned int magLimit = 1, const unsigned int minLimit = 1, const bool keepRatio = true);

        // Override from Component
        virtual void draw() const override;

        // Minimum size
        // virtual void  getMinimumSize(int &minimumWidth, int &minimumHeight) const;
        // virtual glm::ivec2 getMinimumSize() const;

        // virtual int getMinimumWidth() const override;
        // virtual int getMinimumHeight() const override;

        // Preferred size
        virtual int getPreferredWidth() const override;
        virtual int getPreferredHeight() const override;

        // Resizing/positioning
        virtual void resize() override;
    };
};