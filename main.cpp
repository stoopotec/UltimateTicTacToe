#include <iostream>
#include <SFML/Graphics.hpp>

#include "playground.hpp"
#include "player.hpp"
#include "interface.hpp"

using namespace sf;

#define PHI 1.618033988749

Resources resources = Resources();

int main(int argc, char** argv)
{
    ContextSettings settings = ContextSettings(0U, 0U, 3U, 1U, 1U, 0U, false);
    RenderWindow window(VideoMode(700 * PHI, 700), "UltimateTicTacToe", 7U, settings);
    Mouse mouse = Mouse();
    sf::Vector2u mousePos = sf::Vector2u(0.0f, 0.0f);

    Box body = Box((sf::Vector2f)window.getSize(), resources);

    playground g = playground();
    Grid grid = Grid(g, sf::Vector2f(600, 600), resources);
    body.Childs.push_back(&grid);

    // g.set_cell(coord_to_pos(0, 0), CELL_PL1);
    // g.set_cell(coord_to_pos(1, 1), CELL_PL1);
    // g.set_cell(coord_to_pos(1, 0), CELL_PL1);
    // g.set_cell(coord_to_pos(0, 1), CELL_PL1);

    g.set_cell(coord_to_pos(7, 7), CELL_ERR);
    g.set_cell(coord_to_pos(8, 8), CELL_ERR);
    g.set_cell(coord_to_pos(8, 7), CELL_ERR);
    g.set_cell(coord_to_pos(7, 8), CELL_ERR);

    g.set_cell(coord_to_pos(7, 0), CELL_PL2);
    g.set_cell(coord_to_pos(8, 1), CELL_PL2);
    g.set_cell(coord_to_pos(8, 0), CELL_PL2);
    g.set_cell(coord_to_pos(7, 1), CELL_PL2);

    g.set_cell(coord_to_pos(0, 0), CELL_PL1);
    g.set_cell(coord_to_pos(0, 1), CELL_PL1);
    g.set_cell(coord_to_pos(1, 0), CELL_PL1);
    g.set_cell(coord_to_pos(1, 1), CELL_PL1);

    g.set_cell(coord_to_pos(2, 0), CELL_PL2);
    g.set_cell(coord_to_pos(3, 0), CELL_PL2);
    g.set_cell(coord_to_pos(2, 1), CELL_PL2);
    g.set_cell(coord_to_pos(3, 0), CELL_PL2);

    g.set_cell(coord_to_pos(4, 0), CELL_PL2);
    g.set_cell(coord_to_pos(5, 0), CELL_PL2);
    g.set_cell(coord_to_pos(4, 1), CELL_PL2);
    g.set_cell(coord_to_pos(7, 1), CELL_PL2);
    

    g.set_cell(coord_to_pos(0, 7), CELL_ERR);
    g.set_cell(coord_to_pos(1, 8), CELL_ERR);
    g.set_cell(coord_to_pos(1, 7), CELL_ERR);
    g.set_cell(coord_to_pos(0, 8), CELL_ERR);

    CircleShape cursor = CircleShape(10);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::Resized) {
                window.setView(View(sf::FloatRect(Vector2f(0.0f, 0.0f), (Vector2f)window.getSize())));
            }
            if (event.type == Event::MouseMoved) {
                mousePos = (Vector2u)mouse.getPosition(window);
                body.processClick(mousePos);
            }
            if (event.type == Event::MouseButtonPressed) {
                mousePos = (Vector2u)mouse.getPosition(window);
                body.processClick(mousePos);
            }
        }


        window.clear(resources.BackgroundColor);
        window.draw(body);
        
        cursor.setPosition((sf::Vector2f)mousePos - sf::Vector2f(cursor.getRadius(), cursor.getRadius()));
        window.draw(cursor);

        window.display();
    }


    return 0;
}