#include "player.hpp"


BotPlayer::BotPlayer() { }


/// @brief рассичтывает примерный "шанс" победить первому (крестик) игроку
/// @param ground 
/// @return число от 0.0 до 1.0 
double rate(playground& ground)
{
    // x - o, тоесть количество поставленных и доступных крестиков минус ноликов (крестик - первый игрок, нолик- второй игрок)
    static int xmo, x, y, c;
    xmo = 0;

    for (x = 0; x < 9; x++) 
        for (y = 0; y < 9; y++)
        {
            c = ground.get_cell_on_pos(x, y);
            if (c == CELL_PL1) xmo++;
            if (c == CELL_PL2) xmo--;
        }

    return ((double)xmo / 81.0) * 0.5 + 0.5;
}

void BotPlayer::next_move(int& x, int& y, playground& playground) {
    
}