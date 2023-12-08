#include <iostream>
#include "playground.hpp"
#include "player.hpp"

void gp(playground& g)
{
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            unsigned char c = g.get_cell_on_pos(x, y);
                 if (c == CELL_SPACE) putchar(' ');
            else if (c == CELL_PL1)   putchar('x');
            else if (c == CELL_PL1)   putchar('o');
            else if (c == CELL_ERR)   putchar('E');
            else                      putchar('?');
        }
        putchar('\n');
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

    for (int y = 0; y < 9; y++)
        for (int x = 0; x < 9; x++)
        {
            char s;
            std::cin >> s;
            ground.set_cell_on_pos(x, y, CELL_PL1);
            system("clear");
            gp(ground);
        }
    
}