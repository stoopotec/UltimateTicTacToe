#include <iostream>
#include "playground.hpp"
#include "player.hpp"

void gp(playground& g)
{
    printf("board view:\n");
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            unsigned char c = g.get_cell_on_pos(x, y);
            putchar(cell_to_char(c));
        }
        putchar('\n');
    }
    putchar('\n');
    printf("bits view:\n");
    printf("cell to char  |  byte\n");
    for (int i = 0; i < PLAYGROUND_BYTES; i++) {
        unsigned char gb = *(g.get_ground() + i);

        for (int b = 0; b < sizeof(unsigned char) * 8; b += 2) {
            putchar(cell_to_char((gb >> b) & (unsigned char)0b11));
            putchar(' ');
        }
        printf("      |  ");
        for (int b = 0; b < sizeof(unsigned char) * 8; b += 2) {
            putchar(((gb >>  b   ) & (unsigned char)0b1) ? '1' : '0');
            putchar(((gb >> (b+1)) & (unsigned char)0b1) ? '1' : '0');
            putchar(' ');
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

    printf("press any key to see a magic!\n");
    for (unsigned char fill = 0b01; fill < 0b100; fill--)
        for (int y = 0; y < 9; y++)
            for (int x = 0; x < 9; x++)
            {
                std::cin.get();
                ground.set_cell_on_pos(x, y, fill);
                system("clear");
                gp(ground);
            }
    
}