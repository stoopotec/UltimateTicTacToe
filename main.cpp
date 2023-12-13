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
    // ЭТО ПРИМЕР!!!! желательно делать так, но если что-то придумаешь прикольное, то можешь мне предложить и делать

    // массив из указателей на Player, нужно для апкаста. (watch extremecode)
    RenderWindow window(VideoMode(700 * PHI, 700), "UltimateTicTacToe");

    playground g = playground();
    Grid grid = Grid(g, sf::Vector2f(600, 600), resources);

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

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }


        window.clear(resources.BackgroundColor);
        window.draw(grid);
        window.display();
    }


    return 0;
}