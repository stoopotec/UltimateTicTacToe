#include "player.hpp"


BotPlayer::BotPlayer(cell own_cell) : Player(own_cell) { }


void BotPlayer::next_move(int& x, int& y, playground& playground) {
    x = 0;
    y = 0;
}