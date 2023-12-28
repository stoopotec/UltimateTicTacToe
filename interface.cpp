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



Grid::Grid(void (*click_event_handler)(pos_t* poses, int poses_len, Element* sender), unsigned int nested_grids, sf::Vector2f size, Resources& resources) 
    : Box(size, resources), click_event_handler(click_event_handler) 
{
    sf::Vector2f cell_size = (size) / 3.0f * 0.95f;
    sf::Vector2f cell_def_size = (size) / 3.0f;
    sf::Vector2f delta_pos = (cell_def_size - cell_size) / 2.0f;

    
    

    if (nested_grids > 0)
        for (int y = 0; y < 3; ++y)
            for (int x = 0; x < 3; ++x)
            {
                Childs.push_back(nullptr);
                Childs[Childs.size()-1] = new Grid(nullptr, nested_grids - 1, cell_size, resources);
                Childs[Childs.size()-1]->setPosition(
                    sf::Vector2f(cell_def_size.x * x, cell_def_size.y * y) + delta_pos);
            }
    if (nested_grids == 0)
        for (int y = 0; y < 3; ++y)
            for (int x = 0; x < 3; ++x)
            {
                Childs.push_back(nullptr);
                Childs[Childs.size()-1] = new Cell_Space(cell_size, resources);
                Childs[Childs.size()-1]->setPosition(
                    sf::Vector2f(cell_def_size.x * x, cell_def_size.y * y) + delta_pos);
            }
}

void Grid::processClick(sf::Vector2u& pos) {
    size_t actual_size = 2;
    size_t posses_len = 0;
    pos_t* posses = (pos_t*)malloc(sizeof(*posses) * actual_size);

    
    Grid* temp_grid = this;
    Element* temp_elem;
    static sf::Vector2f temp_pos;
    temp_pos = (sf::Vector2f)pos;
    temp_pos -= getPosition();
    do {
        posses[posses_len++] = temp_grid->getCellByCoord(temp_pos);
        
        if (posses_len >= actual_size) {
            actual_size *= 2;
            posses = (pos_t*)realloc(posses, sizeof(*posses) * actual_size);
        }
        
        static size_t index;
        index = pos_to_index(posses[posses_len-1], 3);
        
        if (index >= 9) break;
        temp_elem = temp_grid->Childs[index]; 
        if (temp_elem->GetType() == EElementType::GRID) {
            temp_grid = (Grid*)temp_elem;
            temp_pos -= temp_grid->getPosition();
        }
        else break;
    } while (true);


    if (click_event_handler != nullptr) click_event_handler(posses, posses_len, this);


    free(posses);
}

void Grid::setCell(pos_t* posses, int posses_len, cell_t cell) 
{
    printf("click on\n");
    for (int i = 0; i < posses_len; ++i) {
        static unsigned char x, y;
        pos_to_coord(x, y, posses[i]);
        printf("x: %i, y: %i;\n", (int)x, (int)y);
    }
    printf("(try to set \'%c\' cell)\n\n", cell_to_char(cell));

    Grid* grid = this;
    for (size_t i = 0; i < posses_len-1; ++i) {
        grid = (Grid*)grid->Childs[pos_to_index(posses[i], 3)];
    }
    void* cellp = grid->Childs[pos_to_index(posses[posses_len-1], 3)];
    delete grid->Childs[pos_to_index(posses[posses_len-1], 3)];

    sf::Vector2f cell_size = (grid->GetSize()) / 3.0f * 0.95f;
    sf::Vector2f cell_def_size = (grid->GetSize()) / 3.0f;
    sf::Vector2f delta_pos = (cell_def_size - cell_size) / 2.0f;

         if (cell == CELL_PL1)   grid->Childs[pos_to_index(posses[posses_len-1], 3)] = new Cell_Cross (cell_size, grid->resources);
    else if (cell == CELL_PL2)   grid->Childs[pos_to_index(posses[posses_len-1], 3)] = new Cell_Circle(cell_size, grid->resources);
    else if (cell == CELL_SPACE) grid->Childs[pos_to_index(posses[posses_len-1], 3)] = new Cell_Space (cell_size, grid->resources);
    else                         grid->Childs[pos_to_index(posses[posses_len-1], 3)] = new Cell_Error (cell_size, grid->resources);
    
    static unsigned char x, y;
    pos_to_coord(x, y, posses[posses_len-1]);

    grid->Childs[pos_to_index(posses[posses_len-1], 3)]->setPosition(
                    sf::Vector2f(cell_def_size.x * x, cell_def_size.y * y) + delta_pos);
}

pos_t Grid::getCellByCoord(sf::Vector2f coord) {
    static sf::Vector2i rel_pos;
    rel_pos = sf::Vector2i(coord.x / size.x * 3.0f, coord.y / size.y * 3.0f);
    if (rel_pos.x >= 3 || rel_pos.y >= 3) return POS_MAX;
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