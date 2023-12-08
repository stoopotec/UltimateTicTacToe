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






/// @return переменная, содержащая 2 бита под индексом i из переменной c
inline unsigned char _get2(unsigned char c, unsigned char i) { return (c >> i) & (unsigned char)0b11; }

/// @return переменная, содержащая 1 бит под индексом i из переменной c
inline unsigned char _get1(unsigned char c, unsigned char i) { return (c >> i) & (unsigned char)0b1; }


/// @brief записывает в переменную cin 2 первых бита из c под индексом i
/// @param cin переменная, в которую записывать те злополучные 2 бита
/// @param i индекс
/// @param c берётся только 2 первых бита (see CELL_... в playground.hpp)
inline          void _set2(unsigned char& cin, unsigned char i, unsigned char c) { 
    cin &= ~((unsigned char)0b11 << i);
    cin |= (c & 0b11) << i; 
}

/// @brief записывает в переменную cin 1 первый бит из c под индексом i
/// @param cin переменная, в которую записывать бит
/// @param i индекс
/// @param c берётся только 1 первый бит
inline          void _set1(unsigned char& cin, unsigned char i, unsigned char c) { 
    cin &= ~((unsigned char)0b1 << i);
    cin |= (c & 0b1) << i; 
}


playground::playground() {
    for (int i = 0; i < PLAYGROUND_BYTES; i++) ground[i] = 0;
    // третий бит отвечает за хранение того, кто сейчас ходит, 
    // с тетьего по 8 - куда можно ходить (если значение больше 8, ходить можно куда угодно)
    ground[20] |= 0b11111100; 
}
playground::~playground() { }

unsigned char playground::get_cell_on_pos(size_t x, size_t y) {
    if (x >= PLAYGROUND_SIDE_SIZE * PLAYGROUND_SIDE_SIZE || y >= PLAYGROUND_SIDE_SIZE * PLAYGROUND_SIDE_SIZE) 
        return CELL_ERR;
    // xbox - кордината коробки 3 на 3 (0, 1, 2)
    // xinbox - кордината ячейки в коробке (0, 1, 2)
    static int xinbox, yinbox, xbox, ybox;
    xinbox = x % PLAYGROUND_SIDE_SIZE;
    yinbox = y % PLAYGROUND_SIDE_SIZE;

    xbox = (x - xinbox) / PLAYGROUND_SIDE_SIZE;
    xbox = (x - xinbox) / PLAYGROUND_SIDE_SIZE;


    
    if (yinbox == 1) {
        if (xinbox == 1) {
            if (ybox == 1) {
                if (xbox == 1) {
                    return _get2(ground[20], 0);
                }

                if (xbox == 0) return _get2(ground[18], 6);
                if (xbox == 2) return _get2(ground[19], 0);
            }

            if (ybox == 0) return _get2(ground[18],  xbox      * 2);
            if (ybox == 2) return _get2(ground[19], (xbox + 1) * 2);
        }

        if (xinbox == 0) return _get2(ground[ybox * 6 + 2 * xbox    ], 6);
        if (xinbox == 2) return _get2(ground[ybox * 6 + 2 * xbox + 1], 0);
    }

    if (yinbox == 0) return _get2(ground[ybox * 6 + 2 * xbox    ],  xinbox      * 2);
    if (yinbox == 2) return _get2(ground[ybox * 6 + 2 * xbox + 1], (xinbox + 1) * 2);


    return CELL_ERR;
}






void playground::set_cell_on_pos(size_t x, size_t y, unsigned char c) {
    if (x >= PLAYGROUND_SIDE_SIZE * PLAYGROUND_SIDE_SIZE || y >= PLAYGROUND_SIDE_SIZE * PLAYGROUND_SIDE_SIZE) 
        return;
    // xbox - кордината коробки 3 на 3 (0, 1, 2)
    // xinbox - кордината ячейки в коробке (0, 1, 2)
    static int xinbox, yinbox, xbox, ybox;
    xinbox = x % PLAYGROUND_SIDE_SIZE;
    yinbox = y % PLAYGROUND_SIDE_SIZE;

    xbox = (x - xinbox) / PLAYGROUND_SIDE_SIZE;
    xbox = (x - xinbox) / PLAYGROUND_SIDE_SIZE;


    
    if (yinbox == 1) {
        if (xinbox == 1) {
            if (ybox == 1) {
                if (xbox == 1) {
                    _set2(ground[20], 0, c);
                }

                if (xbox == 0) _set2(ground[18], 6, c);
                if (xbox == 2) _set2(ground[19], 0, c);
            }

            if (ybox == 0) _set2(ground[18],  xbox      * 2, c);
            if (ybox == 2) _set2(ground[19], (xbox + 1) * 2, c);
        }

        if (xinbox == 0) _set2(ground[ybox * 6 + 2 * xbox    ], 6, c);
        if (xinbox == 2) _set2(ground[ybox * 6 + 2 * xbox + 1], 0, c);
    }

    if (yinbox == 0) _set2(ground[ybox * 6 + 2 * xbox    ],  xinbox      * 2, c);
    if (yinbox == 2) _set2(ground[ybox * 6 + 2 * xbox + 1], (xinbox + 1) * 2, c);
}

unsigned char playground::who_moves() {
    return _get1(ground[20], 2);
}