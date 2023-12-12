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




class Box : public sf::Transformable, public sf::Drawable
{
public:
    Box(sf::Vector2f size, Resources* resources);

    sf::Vector2f GetSize();
protected:
    sf::Vector2f size;
    Resources* resources;
};



class Grid : public Box
{
public:

    Grid(playground* ground, sf::Vector2f size);


private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    playground* ground;
};