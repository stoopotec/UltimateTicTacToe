#include <stdio.h>

#include "player.hpp"
#include "playground.hpp"
#include "default_messages.hpp"



Player::Player(cell own_cell) : own_cell(cell(true, MES_DEF_VISIBLE_CHAR)) {
    if (!visible_char(own_cell.symbol)) 
    {
        printf("Error occurred in Player constuctor\n");
        exit(EXIT_FAILURE);
    }
    this->own_cell.symbol = own_cell.symbol;
    // this->own_cell.background_color = own_cell.background_color;
    // this->own_cell.foreground_color = own_cell.foreground_color;
}
cell Player::get_own_cell() { return own_cell; }