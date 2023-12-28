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

enum EElementType { // первые 8 бит для первых родителей, вторые 8 для вторых родителей итд. для финальных детей используй последние 8 бит (считай первый - послений как слева направо)
    ELEMENT = 0b1000000000000000000000000000000000000000000000000000000000000000,
    BOX     = 0b1000000010000000000000000000000000000000000000000000000000000000,
    GRID    = 0b1000000010000000000000000000000000000000000000000000000000000001,
    CELL    = 0b1000000010000000100000000000000000000000000000000000000000000000,
};


class Element : public sf::Transformable, public sf::Drawable
{
public:
    Element(sf::Vector2f size, Resources& resources);

    sf::Vector2f GetSize();

    virtual void processClick(sf::Vector2u& pos) = 0;

    virtual EElementType GetType() { return EElementType::ELEMENT; }
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

    EElementType GetType() override { return EElementType::BOX; }
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};




class Cell : public Element
{
public:

    Cell(sf::Vector2f size, Resources& resources);

    virtual void processClick(sf::Vector2u& pos) = 0;

    virtual cell_t CellType() = 0;

    EElementType GetType() override { return EElementType::CELL; }
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};


class Cell_Cross : public Cell
{
public:
    
    Cell_Cross(sf::Vector2f size, Resources& resources);

    virtual void processClick(sf::Vector2u& pos);

    virtual cell_t CellType() { return CELL_PL1; }
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Cell_Circle : public Cell
{
public:
    
    Cell_Circle(sf::Vector2f size, Resources& resources);

    virtual void processClick(sf::Vector2u& pos);

    virtual cell_t CellType() { return CELL_PL2; }
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Cell_Space : public Cell
{
public:
    
    Cell_Space(sf::Vector2f size, Resources& resources);

    virtual void processClick(sf::Vector2u& pos);

    virtual cell_t CellType() { return CELL_SPACE; }
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Cell_Error : public Cell
{
public:
    
    Cell_Error(sf::Vector2f size, Resources& resources);

    virtual void processClick(sf::Vector2u& pos);

    virtual cell_t CellType() { return CELL_ERR; }
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};



/// @brief сетка 3 на 3, в которой расположены дочерние блоки
class Grid : public Box
{
public:

    Grid(void (*click_event_handler)(pos_t* poses, int poses_len, Element* sender), unsigned int nested_grids, sf::Vector2f size, Resources& resources);

    void processClick(sf::Vector2u& pos) override;

    void setCell(pos_t* posses, int posses_len, cell_t cell);

    /// @brief ищет клетку (кординаты / позиция / x, y), куда указывает coord (минимум 0, максимум GetSize())
    pos_t getCellByCoord(sf::Vector2f coord);

    EElementType GetType() override { return EElementType::GRID; }
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void (*click_event_handler)(pos_t* poses, int poses_len, Element* sender);
};