#include "player.hpp"


ConsolePlayer::ConsolePlayer(cell own_cell) : Player(own_cell) { }


void ConsolePlayer::next_move(int& x, int& y, playground& playground) {
    x = 0;
    y = 0;
}