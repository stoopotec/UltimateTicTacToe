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




Element::Element(sf::Vector2f size, Resources& resources) : size(size), resources(resources) {}

sf::Vector2f Element::GetSize() { return size; }



Box::Box(sf::Vector2f size, Resources& resources) : Element(size, resources) 
{
    Childs = std::vector<Element*>();
}

void Box::processClick(sf::Vector2u& pos) {
    for (int i = 0; i < Childs.size(); ++i) {
        Childs[i]->processClick(pos);
    }
}

void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= this->getTransform();
    for (int i = 0; i < Childs.size(); ++i)
        target.draw(*Childs[i], states);
}



sf::ConvexShape buffer_convex_shape = sf::ConvexShape();
sf::CircleShape buffer_circle_shape = sf::CircleShape();



Cell::Cell(sf::Vector2f size, Resources& resources) : Element(size, resources) {}



Cell_Cross::Cell_Cross(sf::Vector2f size, Resources& resources) : Cell(size, resources) {}

void Cell_Cross::processClick(sf::Vector2u& pos) { }

void Cell_Cross::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    buffer_convex_shape.setPointCount(4);
    buffer_convex_shape.setPoint(0, sf::Vector2f(size.x / 5, 0));
    buffer_convex_shape.setPoint(1, sf::Vector2f(size.x, size.y - (size.y / 5)));
    buffer_convex_shape.setPoint(2, sf::Vector2f(size.x - (size.x / 5), size.y));
    buffer_convex_shape.setPoint(3, sf::Vector2f(0, size.y / 5));

    buffer_convex_shape.setFillColor(resources.CrossColor);
    target.draw(buffer_convex_shape, states);
    
    buffer_convex_shape.setPointCount(4);
    buffer_convex_shape.setPoint(0, sf::Vector2f(size.x - (size.x / 5), 0));
    buffer_convex_shape.setPoint(1, sf::Vector2f(size.x, size.y / 5));
    buffer_convex_shape.setPoint(2, sf::Vector2f(size.x / 5, size.y));
    buffer_convex_shape.setPoint(3, sf::Vector2f(0, size.y - size.y / 5));

    buffer_convex_shape.setFillColor(resources.CrossColor);
    target.draw(buffer_convex_shape, states);
}



Cell_Circle::Cell_Circle(sf::Vector2f size, Resources& resources) : Cell(size, resources) {}

void Cell_Circle::processClick(sf::Vector2u& pos) { }

void Cell_Circle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    buffer_circle_shape.setRadius(size.x / 2);
    buffer_circle_shape.setPointCount(50);
    buffer_circle_shape.setFillColor(resources.CircleColor);
    target.draw(buffer_circle_shape, states);

    buffer_circle_shape.setRadius(size.x / 2 - 1.5f * sqrt(size.x));
    buffer_circle_shape.setPointCount(50);
    buffer_circle_shape.setFillColor(resources.BackgroundColor);
    target.draw(buffer_circle_shape, states);
}



Cell_Space::Cell_Space(sf::Vector2f size, Resources& resources) : Cell(size, resources) {}

void Cell_Space::processClick(sf::Vector2u& pos) { }

void Cell_Space::draw(sf::RenderTarget& target, sf::RenderStates states) const { }



Cell_Error::Cell_Error(sf::Vector2f size, Resources& resources) : Cell(size, resources) {}

void Cell_Error::processClick(sf::Vector2u& pos) { }

void Cell_Error::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    buffer_convex_shape.setPointCount(4);
    buffer_convex_shape.setPoint(0, sf::Vector2f(0, 0));
    buffer_convex_shape.setPoint(1, sf::Vector2f(size.x, 0));
    buffer_convex_shape.setPoint(2, size);
    buffer_convex_shape.setPoint(3, sf::Vector2f(0, size.y));
    buffer_convex_shape.setFillColor(resources.ErrorColor);
    target.draw(buffer_convex_shape, states);
}



Grid::Grid(void (*click_event_handler)(pos_t* poses, int poses_len, Grid& sender), unsigned int nested_grids, sf::Vector2f size, Resources& resources) 
    : Box(size, resources), click_event_handler(click_event_handler) 
{
    sf::Vector2f cell_size = (size) / 3.0f * 0.95f;
    sf::Vector2f cell_def_size = (size) / 3.0f;
    sf::Vector2f delta_pos = (cell_def_size - cell_size) / 2.0f;

    
    

    if (nested_grids > 0)
        for (int x = 0; x < 3; ++x)
            for (int y = 0; y < 3; ++y)
            {
                Childs.push_back(nullptr);
                Childs[Childs.size()-1] = new Grid(nullptr, nested_grids - 1, cell_size, resources);
                Childs[Childs.size()-1]->setPosition(
                    sf::Vector2f(cell_def_size.x * x, cell_def_size.y * y) + delta_pos);
            }
    if (nested_grids == 0)
        for (int x = 0; x < 3; ++x)
            for (int y = 0; y < 3; ++y)
            {
                Childs.push_back(nullptr);
                Childs[Childs.size()-1] = new Cell_Cross(cell_size, resources);
                Childs[Childs.size()-1]->setPosition(
                    sf::Vector2f(cell_def_size.x * x, cell_def_size.y * y) + delta_pos);
            }
}

void Grid::processClick(sf::Vector2u& pos) {
    Box::processClick(pos);
    sf::Vector2f rel_pos = (sf::Vector2f)pos - getPosition();
    if (rel_pos.x > size.x || rel_pos.y > size.y) return;

    rel_pos = sf::Vector2f(rel_pos.x / size.x * 9.0f, rel_pos.y / size.y * 9.0f);

    // pos_t* posses = (pos_t*)malloc((*posses) * 2); // 2 это максимальное вложенное количество сеток, как-то так ЕСЛИ ЧТО_ТО СЛОМАЛОСЬ, ТО ТУТ ТОЖЕ МОЖЕТ БЫТЬ ПРИЧИНА
    // if (click_event_handler != nullptr) click_event_handler(coord_to_pos(rel_pos.x, rel_pos.y));

}

void Grid::setCell(pos_t* posses, cell_t cell) 
{
    printf("SETTING CELL IS NOT IMPLEMENTED!!\n");
}

pos_t Grid::getCellByCoord(sf::Vector2f coord) {
    static sf::Vector2f rel_pos;
    rel_pos = sf::Vector2f(rel_pos.x / size.x * 9.0f, rel_pos.y / size.y * 9.0f);
    return coord_to_pos(rel_pos.x, rel_pos.y);
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // нужно для того, чтобы трансформации применялись от класса к классу как родители с детьми в html
    states.transform *= this->getTransform();

    for (int i = 0; i < 9 && i < Childs.size(); ++i)
        target.draw(*Childs[i], states);


    // buffer_convex_shape.setPointCount(4);
    // buffer_convex_shape.setPoint(0, sf::Vector2f(0, 0));
    // buffer_convex_shape.setPoint(1, sf::Vector2f(size.x, 0));
    // buffer_convex_shape.setPoint(2, size);
    // buffer_convex_shape.setPoint(3, sf::Vector2f(0, size.y));
    // buffer_convex_shape.setFillColor(sf::Color(0, 0, 0, 100));
    // buffer_convex_shape.setPosition(sf::Vector2f(0.0f, 0.0f));
    // target.draw(buffer_convex_shape, states);
}