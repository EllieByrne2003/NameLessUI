#pragma once

// Includes from standard
#include <memory>

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

    class BorderPane : public Pane {
    public:
        enum Position {
            CENTRE,
            NORTH,
            SOUTH,
            EAST,
            WEST
        };

    private:
        std::array<std::shared_ptr<Component>, 5> components;
        // north west centre east south

        // TODO make funtions to set these
        bool horizontal; // horizontal spreads north and south wide, vertical spreads east and west tall

        std::shared_ptr<Component> & getComponent(const Position &pos);
        std::shared_ptr<Component> & centre();
        std::shared_ptr<Component> & north();
        std::shared_ptr<Component> & south();
        std::shared_ptr<Component> & east();
        std::shared_ptr<Component> & west();

    protected:

    public:

    /*----------  Functions  ----------*/
    private:

    protected:
        BorderPane(const bool horizontal, const glm::ivec2 &minSize, const glm::ivec2 &maxSize);

    public:
        virtual ~BorderPane() override;

        static std::shared_ptr<BorderPane> create(const bool horizontal = true, const glm::ivec2 &minSize = glm::ivec2(0, 0), const glm::ivec2 &maxSize = glm::ivec2(INT_MAX, INT_MAX));

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
        void setComponent(const Position &pos, const std::shared_ptr<Component> &component);
        void setCentre(const std::shared_ptr<Component> &component);
        void setNorth(const std::shared_ptr<Component> &component);
        void setSouth(const std::shared_ptr<Component> &component);
        void setEast(const std::shared_ptr<Component> &component);
        void setWest(const std::shared_ptr<Component> &component);

        const std::shared_ptr<Component> & getComponent(const Position &pos) const;
        const std::shared_ptr<Component> & centre() const;
        const std::shared_ptr<Component> & north() const;
        const std::shared_ptr<Component> & south() const;
        const std::shared_ptr<Component> & east() const;
        const std::shared_ptr<Component> & west() const;

        // // TODO have individual ones for this (ones for centre, north, south, etc)
        // int getComponentPrefSize(const Position &pos, int &prefWidth, int &prefHeight) const;
        // glm::ivec2 getComponentPrefSize(const Position &pos) const;
        // int getComponentPrefWidth(const Position &pos) const;
        // int getComponentPrefHeight(const Position &pos) const;

        // int getComponentMinSize(const Position &pos, int &prefWidth, int &prefHeight) const;
        // glm::ivec2 getComponentMinSize(const Position &pos) const;
        // int getComponentMinWidth(const Position &pos) const;
        // int getComponentMinHeight(const Position &pos) const;
        
        // int getComponentMaxSize(int &prefWidth, int &prefHeight) const;
        // glm::ivec2 getComponentMaxSize() const;
        // int getComponentMaxWidth() const;
        // int getComponentMaxHeight() const;

        // int getCentrePrefSize(int &prefWidth, int &prefHeight) const;
        // glm::ivec2 getCentrePrefSize() const;
        // int getCentrePrefWidth() const;
        // int getCentrePrefHeight() const;

        // int getCentreMinSize(int &prefWidth, int &prefHeight) const;
        // glm::ivec2 getCentreMinSize() const;
        // int getCentreMinWidth() const;
        // int getCentreMinHeight() const;

        // int getCentreMaxSize(int &prefWidth, int &prefHeight) const;
        // glm::ivec2 getCentreMaxSize() const;
        // int getCentreMaxWidth() const;
        // int getCentreMaxHeight() const;
        
        // int getNorthPrefSize(int &prefWidth, int &prefHeight) const;
        // glm::ivec2 getNorthPrefSize() const;
        // int getNorthPrefWidth() const;
        // int getNorthPrefHeight() const;
        
        // int getNorthMinSize(int &prefWidth, int &prefHeight) const;
        // glm::ivec2 getNorthMinSize() const;
        // int getNorthMinWidth() const;
        // int getNorthMinHeight() const;
        
        // int getNorthMaxSize(int &prefWidth, int &prefHeight) const;
        // glm::ivec2 getNorthMaxSize() const;
        // int getNorthMaxWidth() const;
        // int getNorthMaxHeight() const;
        
        // int getSouthPrefSize(int &prefWidth, int &prefHeight) const;
        // glm::ivec2 getSouthPrefSize() const;
        // int getSouthPrefWidth() const;
        // int getSouthPrefHeight() const;
        
        // int getSouthMinSize(int &prefWidth, int &prefHeight) const;
        // glm::ivec2 getSouthMinSize() const;
        // int getSouthMinWidth() const;
        // int getSouthMinHeight() const;
        
        // int getSouthMaxSize(int &prefWidth, int &prefHeight) const;
        // glm::ivec2 getSouthMaxSize() const;
        // int getSouthMaxWidth() const;
        // int getSouthMaxHeight() const;
        
        // int getEastPrefSize(int &prefWidth, int &prefHeight) const;
        // glm::ivec2 getEastPrefSize() const;
        // int getEastPrefWidth() const;
        // int getEastPrefHeight() const;
        
        // int getEastMinSize(int &prefWidth, int &prefHeight) const;
        // glm::ivec2 getEastMinSize() const;
        // int getEastMinWidth() const;
        // int getEastMinHeight() const;
        
        // int getEastMaxSize(int &prefWidth, int &prefHeight) const;
        // glm::ivec2 getEastMaxSize() const;
        // int getEastMaxWidth() const;
        // int getEastMaxHeight() const;
        
        // int getWestPrefSize(int &prefWidth, int &prefHeight) const;
        // glm::ivec2 getWestPrefSize() const;
        // int getWestPrefWidth() const;
        // int getWestPrefHeight() const;
        
        // int getWestMinSize(int &prefWidth, int &prefHeight) const;
        // glm::ivec2 getWestMinSize() const;
        // int getWestMinWidth() const;
        // int getWestMinHeight() const;
        
        // int getWestMaxSize(int &prefWidth, int &prefHeight) const;
        // glm::ivec2 getWestMaxSize() const;
        // int getWestMaxWidth() const;
        // int getWestMaxHeight() const;
    };
};