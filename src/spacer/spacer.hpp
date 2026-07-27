#pragma once

// Includes from standard


// Includes from third party libraries
#include <glm/glm.hpp>

// Includes from personal libraries


// Includes from project
#include "../component/component.hpp"

// Forward declarations


// Type aliases


namespace NLUI {
    class Spacer final : public Component {
    private:
        glm::ivec2 preferredSize = ivec2(0, 0);

    protected:

    public:
        Spacer();
        virtual ~Spacer() override;

        // Override from Component
        // Preferred size
        virtual void getPreferredSize(int &preferredWidth, int &preferredHeight) const override;
        virtual ivec2 getPreferredSize() const override;

        virtual int getPreferredWidth() const override;
        virtual int getPreferredHeight() const override;

        // Resizing/positioning
        virtual void resize() override; // TODO no need to implement empty function here, maybe remove and implement in Component

        // New functions
        // Preferred size
        void setPreferredSize(const int preferredWidth, const int preferredHeight);
        void setPreferredSize(const ivec2 &preferredSize);

        void setPreferredWidth(const int preferredWidth);
        void setPreferredHeight(const int preferredHeight);
    };
};