#pragma once

#include <stdlib.h>

#include "player.hpp"

/// @brief actually - число от 0 до 4 (см CELL_... в playground.hpp)
typedef unsigned char cell_t;

/// @brief actually - один байт, первые 4 бита которого - кордината по оси x, последние4 бита - кордината по оси y (тип беззнаковый)
typedef unsigned char pos_t;

#define CELL_SPACE (cell_t)0b00
#define CELL_PL1   (cell_t)0b01
#define CELL_PL2   (cell_t)0b10
#define CELL_ERR   (cell_t)0b11

#define POS_MAX    (~(pos_t)0b0)

/// @brief 
/// @param cell число от 0 до 4
/// @return символ, ассоциирующийся с номером клетки (см CELL_... в playground.hpp)
char cell_to_char(cell_t cell);


#define PLAYGROUND_SIDE_SIZE 3
#define PLAYGROUND_BYTES 21




/// @brief РАБОТАЕТ ТОЛЬКО С ASCII, NO RUSSIAN!!
/// @param c 
/// @return если выидимый символ - true, иначе false
bool visible_char(char c);

/// @brief ищет победителя в игре в крестики-нолики
/// @param cells массив из 9 ячеек
/// @return '\0', если победителя нету, иначе ячейку ассоциируется с победителем
cell_t who_win(cell_t* cells);


struct playground
{
public:
    playground();
    ~playground();

    /// @param x максимум - get_side_size() * get_side_size() - 1
    /// @param y максимум - get_side_size() * get_side_size() - 1
    /// @return если CELL_ERR - выход за пределы поля, иначе то, что вернулось
    cell_t get_cell(size_t x, size_t y);

    /// @param x максимум - get_side_size() * get_side_size() - 1
    /// @param y максимум - get_side_size() * get_side_size() - 1
    void set_cell(size_t x, size_t y, cell_t c);

    /// @brief делает ход текущим игроком на выбранную клетку
    /// @return если ход сделан успешно, true, иначе false
    bool move(pos_t move);

    /// @brief делает ход текущим игроком на выбранную клетку
    /// @return если ход сделан успешно, true, иначе false
    bool move(int x, int y);

    /// @brief узнаёт, какой игрок сейчас должен ходить
    /// @return если не CELL_PL1 или CELL_PL2 - ходить больше нельзя
    cell_t get_who_moves();

    /// @return кординату коробки на поле, куда можно ходить. Если любая кордината больше 2 - можно ходить куда угодно
    pos_t get_move_box();

    /// @brief записывает, какой игрок сейчас должен ходить
    /// @param cell CELL_PL1 или CELL_PL2, иначе не запишется
    void set_who_moves(cell_t cell);

    /// @param pos кордината коробки на поле, куда можно ходить. Если любая кордината больше 2 - ничего не запишется
    void set_move_box(pos_t pos);

    /// @param pos кордината коробки (see pos_t в playground.hpp)
    /// @return если коробка сыграна в ничью, или кто-то на ней победил - возвращает true, иначе false
    bool is_box_marked(pos_t pos);

    unsigned char* get_ground() { return ground; }
private:
    unsigned char ground[PLAYGROUND_BYTES];
};

/// @brief "сравнивает" 2 игровых поля
/// @return если первое "меньше" второго, возвращает значение меньше нуля, если больше - больше нуля, если равны - ноль
int compare(playground& pg1, playground& pg2);

/// @brief применяет трансформацию под номером i к копии pg, и возвращает её (про номера трансформаций смотри README.md)
/// @param transform_num от 0 до 7
playground transform(playground& pg, unsigned char i);

/// @brief трансформирует pg так, чтобы compare(pg, transform(pg, n)) <= 0
void min_transform(playground& pg, int& transform_num);

/// @param moves_restrict массив (максимальный размер - 82 элемента) один ход - один байт (1 - 4 бит под x, 5 - 8 бит под y) конец массива - 0b11111111 (максимальное для unsigned char)
void generate_legal_moves(playground& pg, unsigned char* moves_restrict);