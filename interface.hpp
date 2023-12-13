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
    Box(sf::Vector2f size, Resources& resources);

    sf::Vector2f GetSize();

    virtual void processClick(sf::Vector2u& pos);

    std::vector<Box*> Childs;

protected:
    sf::Vector2f size;
    Resources& resources;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};



class Grid : public Box
{
public:

    Grid(playground& ground, sf::Vector2f size, Resources& resources);

    void processClick(sf::Vector2u& pos) override;
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    playground& ground;
};