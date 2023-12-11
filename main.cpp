#include <iostream>
#include "playground.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>

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
    Player* players[2];

    ConsolePlayer p1 = ConsolePlayer();
    players[0] = &p1;
    ConsolePlayer p2 = ConsolePlayer();
    players[1] = &p2;

    playground ground = playground();
}