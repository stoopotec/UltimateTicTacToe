#pragma once

#include <stdlib.h>

#include "player.hpp"



class Player;


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

struct cell
{
    cell(bool visible, char symbol);
    bool visible;
    char symbol;
};

struct box
{
public:
    /// @brief 
    /// @param side_size размер стороны коробки (предпологается, что коробка квадратная)
    box(size_t side_size);
    ~box();
    
    /// @brief ищет выигрыши
    void update();
private:
    bool captured;
    cell capture_cell;
    cell* cells;
    size_t side_size;
};

struct playground
{
public:
    playground(size_t side_size, Player** players, size_t players_count);
    ~playground();
    size_t get_side_size();

    /// @brief 
    /// @param x координата по x, максимум - get_side_size() * get_side_size() - 1
    /// @param y координата по y, максимум - get_side_size() * get_side_size() - 1
    /// @return указатель на ячейку в блоке в игровом поле, возвращает nullptr, если x и y вышли за границы поля
    cell* get_cell_on_pos(size_t x, size_t y);

    /// @brief 
    /// @param x координата по x, максимум - get_side_size() - 1
    /// @param y координата по y, максимум - get_side_size() - 1
    /// @return указатель на блок в игровом поле, возвращает nullptr, если x и y перешли уже все границы
    box* get_box_on_pos(size_t x, size_t y);

    /// @brief ищет выигрыши
    void update();
private:
    Player** players;
    size_t players_count;
    box* boxes;
    size_t side_size;
};