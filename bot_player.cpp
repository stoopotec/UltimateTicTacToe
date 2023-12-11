#include "player.hpp"


BotPlayer::BotPlayer() { }


/// @brief рассичтывает примерный "шанс" победить первому (крестик) игроку
/// @param ground 
/// @return число от 0.0 до 1.0 
double rate(playground& ground)
{
    // x - o, тоесть количество поставленных и доступных крестиков минус ноликов (крестик - первый игрок, нолик- второй игрок)
    static char xmo;
    static char xb, yb, x, y, c;
    xmo = 0;

    for (xb = 0; xb < 2; xb++)
        for (yb = 0; yb < 2; yb++) 
        {
            if (!ground.is_box_marked(xb | (yb << 4)))
            for (x = 0; x < 2; x++) 
                for (y = 0; y < 2; y++)
                {
                    c = ground.get_cell((xb*3+x) | ((yb*3+x) << 4));
                    if (c == CELL_PL1) xmo++;
                    if (c == CELL_PL2) xmo--;
                }
        }

    return ((double)xmo / 81.0) * 0.5 + 0.5;
}

void BotPlayer::next_move(int& x, int& y, playground& playground) {
    
}