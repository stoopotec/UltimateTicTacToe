#include "interface.hpp"
#include "math.h"

Resources::Resources() : 
    BackgroundColor(sf::Color(42, 46, 50, 255)),
    BorderColor(sf::Color(28, 32, 36, 255)),
    CrossColor(sf::Color(224, 71, 76, 255)),
    CircleColor(sf::Color(71, 119, 224, 255)),
    ErrorColor(sf::Color(216, 65, 213, 255)) 
{

}







Box::Box(sf::Vector2f size, Resources& resources) : size(size), resources(resources) { }

sf::Vector2f Box::GetSize() { return size; }




Grid::Grid(playground& ground, sf::Vector2f size, Resources& resources) : Box(size, resources), ground(ground) { }


sf::ConvexShape buffer_convex_shape = sf::ConvexShape();
sf::CircleShape buffer_circle_shape = sf::CircleShape();

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // нужно для того, чтобы трансформации применялись от класса к классу как родители с детьми в html
    states.transform *= this->getTransform();

    sf::Vector2f cell_size = size / 9.0f - sf::Vector2f(9 + 9/3, 9 + 9/3);
    sf::Vector2f totalSpaceing = sf::Vector2f(0.0f, 0.0f);
    for (int y = 0; y < 9; ++y)
    {
        totalSpaceing.y  = y;
        totalSpaceing.y += (y/3);
        for (int x = 0; x < 9; ++x)
        {
            totalSpaceing.x  = x;
            totalSpaceing.x += (x/3);

            cell_t c = ground.get_cell(coord_to_pos(x, y));

            // if (c == CELL_SPACE) {
            //     buffer_convex_shape.setPointCount(4);
            //     buffer_convex_shape.setPoint(0, sf::Vector2f(0, 0));
            //     buffer_convex_shape.setPoint(1, sf::Vector2f(cell_size.x, 0));
            //     buffer_convex_shape.setPoint(2, cell_size);
            //     buffer_convex_shape.setPoint(3, sf::Vector2f(0, cell_size.y));
            //     buffer_convex_shape.setFillColor(resources->BackgroundColor);
            //     buffer_convex_shape.setPosition(totalSpaceing + sf::Vector2f(cell_size.x * x, cell_size.y * y));
            //     target.draw(buffer_convex_shape, states);
            // }
            if (c == CELL_PL1) {
                buffer_convex_shape.setPointCount(4);
                buffer_convex_shape.setPoint(0, sf::Vector2f(cell_size.x / 5, 0));
                buffer_convex_shape.setPoint(1, sf::Vector2f(cell_size.x, cell_size.y - (cell_size.y / 5)));
                buffer_convex_shape.setPoint(2, sf::Vector2f(cell_size.x - (cell_size.x / 5), cell_size.y));
                buffer_convex_shape.setPoint(3, sf::Vector2f(0, cell_size.y / 5));

                buffer_convex_shape.setFillColor(resources.CrossColor);
                buffer_convex_shape.setPosition(totalSpaceing + sf::Vector2f(cell_size.x * x, cell_size.y * y));
                target.draw(buffer_convex_shape, states);
                
                buffer_convex_shape.setPointCount(4);
                buffer_convex_shape.setPoint(0, sf::Vector2f(cell_size.x - (cell_size.x / 5), 0));
                buffer_convex_shape.setPoint(1, sf::Vector2f(cell_size.x, cell_size.y / 5));
                buffer_convex_shape.setPoint(2, sf::Vector2f(cell_size.x / 5, cell_size.y));
                buffer_convex_shape.setPoint(3, sf::Vector2f(0, cell_size.y - cell_size.y / 5));

                buffer_convex_shape.setFillColor(resources.CrossColor);
                buffer_convex_shape.setPosition(totalSpaceing + sf::Vector2f(cell_size.x * x, cell_size.y * y));
                target.draw(buffer_convex_shape, states);
            }
            if (c == CELL_PL2) {
                buffer_circle_shape.setRadius(cell_size.x / 2);
                buffer_circle_shape.setPointCount(50);
                buffer_circle_shape.setFillColor(resources.CircleColor);
                buffer_circle_shape.setPosition(totalSpaceing + sf::Vector2f(cell_size.x * x, cell_size.y * y));
                target.draw(buffer_circle_shape, states);

                buffer_circle_shape.setRadius(cell_size.x / 2 - 1.5f * sqrt(cell_size.x));
                buffer_circle_shape.setPointCount(50);
                buffer_circle_shape.setFillColor(resources.BackgroundColor);
                buffer_circle_shape.setPosition(totalSpaceing + sf::Vector2f(cell_size.x * x + 1.5f * sqrt(cell_size.x), cell_size.y * y + 1.5f * sqrt(cell_size.x)));
                target.draw(buffer_circle_shape, states);
            }
            if (c == CELL_ERR) {
                buffer_convex_shape.setPointCount(4);
                buffer_convex_shape.setPoint(0, sf::Vector2f(0, 0));
                buffer_convex_shape.setPoint(1, sf::Vector2f(cell_size.x, 0));
                buffer_convex_shape.setPoint(2, cell_size);
                buffer_convex_shape.setPoint(3, sf::Vector2f(0, cell_size.y));
                buffer_convex_shape.setFillColor(resources.ErrorColor);
                buffer_convex_shape.setPosition(totalSpaceing + sf::Vector2f(cell_size.x * x, cell_size.y * y));
                target.draw(buffer_convex_shape, states);
            }
        }
    }
}