#include <stdio.h>


#include "playground.hpp"
#include "player.hpp"
#include "default_messages.hpp"




// color::color(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) { }
// color::color(unsigned char gray) : r(gray), g(gray), b(gray) { }
// color::color() : r(0), g(0), b(0) { }


bool visible_char(char c) {
    return (c >= 33 && c <= 126);
}


/// @brief character equal
/// @return если не равны - '\0', иначе один из тех равных символов
char _cheq(char c1, char c2, char c3) { if (c1 == c2 && c2 == c3) return c1; return '\0'; }

char who_win(char* cells) {

    // 0 1 2
    // 3 4 5
    // 6 7 8

    static char winner;
    for (int i = 0; i < 3; i++) {
        winner = _cheq(cells[i*3 + 0], cells[i*3 + 1], cells[i*3 + 2]);
        if (winner != '\0') return winner;
    }

    for (int i = 0; i <= 6; i += 3) {
        winner = _cheq(cells[i + 0], cells[i + 1], cells[i + 2]);
        if (winner != '\0') return winner;
    }

    winner = _cheq(cells[0], cells[4], cells[8]);
    if (winner != '\0') return winner;

    winner = _cheq(cells[6], cells[4], cells[2]);
    if (winner != '\0') return winner;

    return '\0';
}





cell::cell(bool visible, char symbol) : visible(visible), symbol(symbol) { }







box::box(size_t side_size) : capture_cell(cell(false, MES_DEF_VISIBLE_CHAR)) { 
    cells = (cell*)malloc(sizeof(*cells) * side_size * side_size);
    if (cells == nullptr) {
        printf(MES_MEMORY_NOT_ENOUGH);
        exit(EXIT_FAILURE);
    }
}

box::~box() { free(cells); }

char _temp9cells[9];
void box::update() {
    static char win;
    if (captured) return;
    for (int i = 0; i < 9; i++) _temp9cells[i] = cells[i].symbol;
    win = who_win(_temp9cells);
    if (win != '\0') {
        captured = true;
        capture_cell = cell(true, win);
    }
}







playground::playground(size_t side_size, Player** players, size_t players_count) 
    : side_size(side_size), players(players), players_count(players_count)
{
    boxes = (box*)malloc(sizeof(*boxes) * side_size * side_size);
    if (boxes == nullptr) {
        printf(MES_MEMORY_NOT_ENOUGH);
        exit(0);
    }
}
playground::~playground() { free(boxes); }
cell* playground::get_cell_on_pos(size_t x, size_t y) {
    static int xbox, ybox;
    xbox = x % side_size;
    ybox = y % side_size;

    x -= xbox;
    y -= ybox;

    box* _box = get_box_on_pos(x / side_size, y / side_size);
    if (_box == nullptr) return nullptr;


}
box* playground::get_box_on_pos(size_t x, size_t y) {
    // x и y и так unsigned :)
    if (x >= side_size || y >= side_size) return nullptr;
    return (boxes + (x + y * side_size));
}

size_t playground::get_side_size() { return side_size; }