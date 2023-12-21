#pragma once

#include "playground.hpp"
#include <SFML/Graphics.hpp>


class Resources
{
public:
    Resources();
    sf::Color CrossColor;
    sf::Color CircleColor;
    sf::Color BackgroundColor;
    sf::Color BorderColor;
    sf::Color ErrorColor;
};


class Element : public sf::Transformable, public sf::Drawable
{
public:
    Element(sf::Vector2f size, Resources& resources);

    sf::Vector2f GetSize();

    virtual void processClick(sf::Vector2u& pos) = 0;

protected:
    sf::Vector2f size;
    Resources& resources;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

class Box : public Element
{
public:
    Box(sf::Vector2f size, Resources& resources);

    virtual void processClick(sf::Vector2u& pos);

    std::vector<Element*> Childs;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};




class Cell : public Element
{
public:

    Cell(sf::Vector2f size, Resources& resources);

    virtual void processClick(sf::Vector2u& pos) = 0;
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};


class Cell_Cross : public Cell
{
public:
    
    Cell_Cross(sf::Vector2f size, Resources& resources);

    virtual void processClick(sf::Vector2u& pos);
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Cell_Circle : public Cell
{
public:
    
    Cell_Circle(sf::Vector2f size, Resources& resources);

    virtual void processClick(sf::Vector2u& pos);
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Cell_Space : public Cell
{
public:
    
    Cell_Space(sf::Vector2f size, Resources& resources);

    virtual void processClick(sf::Vector2u& pos);
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Cell_Error : public Cell
{
public:
    
    Cell_Error(sf::Vector2f size, Resources& resources);

    virtual void processClick(sf::Vector2u& pos);
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};



/// @brief сетка 3 на 3, в которой расположены дочерние блоки
class Grid : public Box
{
public:

    Grid(void (*click_event_handler)(pos_t* poses, int poses_len, Grid& sender), unsigned int nested_grids, sf::Vector2f size, Resources& resources);

    void processClick(sf::Vector2u& pos) override;

    void setCell(pos_t* posses, cell_t cell);
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void (*click_event_handler)(pos_t* poses, int poses_len, Grid& sender);
};