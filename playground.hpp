#pragma once

#include <stdlib.h>

#include "player.hpp"


#define CELL_SPACE 0b00
#define CELL_PL1   0b01
#define CELL_PL2   0b10
#define CELL_ERR   0b11

/// @brief 
/// @param cell число от 0 до 4
/// @return символ, ассоциирующийся с номером клетки (см CELL_... в playground.hpp)
char cell_to_char(unsigned char cell);


#define PLAYGROUND_SIDE_SIZE 3
#define PLAYGROUND_BYTES 21


// struct color
// {
//     color(unsigned char r, unsigned char g, unsigned char b);
//     color(unsigned char gray);
//     color();
//     unsigned char r, g, b;
// };


/// @brief РАБОТАЕТ ТОЛЬКО С ASCII, NO RUSSIAN!!
/// @param c 
/// @return если выидимый символ - true, иначе false
bool visible_char(char c);

/// @brief ищет победителя в игре в крестики-нолики
/// @param cells массив из 9 ячеек
/// @return '\0', если победителя нету, иначе ячейку ассоциируется с победителем
char who_win(char* cells);


struct playground
{
public:
    playground();
    ~playground();

    /// @brief 
    /// @param x максимум - get_side_size() * get_side_size() - 1
    /// @param y максимум - get_side_size() * get_side_size() - 1
    /// @return если 0 - то пусто, если 1 - то крестик, если 2 - то нолик, если 3 - неопределено, всё остальное - выход за пределы поля
    unsigned char get_cell_on_pos(size_t x, size_t y);

    /// @brief
    /// @param x максимум - get_side_size() * get_side_size() - 1
    /// @param y максимум - get_side_size() * get_side_size() - 1
    void set_cell_on_pos(size_t x, size_t y, unsigned char c);

    /// @brief ищет выигрыши
    void update();

    /// @brief узнаёт, какой игрок сейчас должен ходить
    /// @return число 1 или 0. если 0, ходит второй игрок (нолик), если 1 - первый
    unsigned char who_moves();

    /// @brief 
    /// @return номер блока, куда можно ходить. ЕСЛИ НОМЕР БОЛЬШЕ 8 - можно ходить куда угодно
    unsigned char where_to_move();

    unsigned char* get_ground() { return ground; }
private:
    unsigned char ground[PLAYGROUND_BYTES];
};