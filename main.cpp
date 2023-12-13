#include <iostream>
#include <SFML/Graphics.hpp>

#include "playground.hpp"
#include "player.hpp"
#include "interface.hpp"

using namespace sf;


enum class Cell { None, Cross, Circle };

const int WindowSize = 600;
const int size = 9;
const float CellSize = WindowSize / (size) ;
const int LineSize = WindowSize / (size);


Cell grid[size][size];


void initGrid(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            grid[i][j] = Cell::None;
        }
    }
}

void drawGrid(RenderWindow& window) {

    int offsetX = 0;
    int offsetY = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) { 
                RectangleShape cell(Vector2f(CellSize, CellSize));

                cell.setPosition(CellSize * i + 7, CellSize * j + 7);
                cell.setFillColor(Color::White);
                cell.setOutlineThickness(2);
                cell.setOutlineColor(Color::Black);

                window.draw(cell);

            if (j == 0 && i == 0) {
                RectangleShape cell(Vector2f(CellSize, CellSize));
                RectangleShape line(Vector2f(LineSize * 3, 5));
                RectangleShape line2(Vector2f(LineSize * 3, 5));

                line.setFillColor(Color::Black);
                line2.setFillColor(Color::Black);

                line.setPosition(LineSize * i + 5, LineSize * j );
                line2.setPosition(LineSize * i + 5, LineSize * j );

                line.rotate(90);

                window.draw(line);
                window.draw(line2);

                cell.setPosition(CellSize * i + 7, CellSize * j + 7);
                cell.setFillColor(Color::White);
                cell.setOutlineThickness(2);
                cell.setOutlineColor(Color::Black);

                window.draw(cell);
            }
            else if (j == 0 || i == 0) {
                RectangleShape cell(Vector2f(CellSize, CellSize));
                RectangleShape line(Vector2f(LineSize, 5));

                line.setFillColor(Color::Black);

                i == 0 ? line.rotate(90) : line.rotate(0);
                line.setPosition(LineSize * i + 5, LineSize * j );
                window.draw(line);
            }
            
            if (j > 2 && j % 3 == 0 || (j + 1) == size) {
                RectangleShape line(Vector2f(5, LineSize));
                line.rotate(90);
                line.setFillColor(Color::Black);
                ((j + 1) == size) ? line.setPosition(LineSize * (i + 1), LineSize * (j + 1)) : line.setPosition(LineSize * (i + 1) , LineSize * j + 5);
                window.draw(line);
            } 

            if (i > 2 && i % 3 == 0 || (i + 1) == size) {
                RectangleShape line(Vector2f(5, LineSize));

                line.setFillColor(Color::Black);
                ((i + 1) == size) ? line.setPosition(LineSize * (i + 1), LineSize * j + 5) : line.setPosition(LineSize * i, LineSize * j + 5);
                window.draw(line);
            }

        }
    }
}


int main(int argc, char** argv)
{
    // ЭТО ПРИМЕР!!!! желательно делать так, но если что-то придумаешь прикольное, то можешь мне предложить и делать

    // массив из указателей на Player, нужно для апкаста. (watch extremecode)
    RenderWindow window(VideoMode(WindowSize, WindowSize), "UltimateTicTacToe");

    playground g = playground();
    Grid grid = Grid(&g, sf::Vector2f(500, 500));

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


        window.clear(Color::Magenta);
        window.draw(grid);
        window.display();
    }


    return 0;
}