#pragma once

// Includes from standard
#include <memory>

// Includes from third party libraries
#include <glm/glm.hpp>

// Includes from personal libraries


// Includes from project
#include "../component/baseComponent.hpp"

// Forward declarations


// Type aliases


namespace NLUI {
    class Spacer final : public BaseComponent {
    private:
        glm::ivec2 prefSize;

    protected:

    public:

    /*----------  Functions  ----------*/
    private:

    protected:
        Spacer(const glm::ivec2 &prefSize, const glm::ivec2 &minSize, const glm::ivec2 &maxSize);

    public:
        virtual ~Spacer() override;

        static std::shared_ptr<Spacer> create(const glm::ivec2 &prefSize, const glm::ivec2 &minSize = glm::ivec2(0, 0), const glm::ivec2 &maxSize = glm::ivec2(INT_MAX, INT_MAX));

        // Overridden from Component
        virtual void getPrefSize(int &prefWidth, int &prefHeight) const override;
        virtual glm::ivec2 getPrefSize() const override;
        virtual int getPrefWidth() const override;
        virtual int getPrefHeight() const override;

        virtual void onResize() override;

        // New functions
        // Preferred size
        void setPreferredSize(const int preferredWidth, const int preferredHeight);
        void setPreferredSize(const glm::ivec2 &preferredSize);

        void setPreferredWidth(const int preferredWidth);
        void setPreferredHeight(const int preferredHeight);
    };
};