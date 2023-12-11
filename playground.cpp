#include <stdio.h>


#include "playground.hpp"
#include "player.hpp"
#include "default_messages.hpp"




bool visible_char(char c) {
    return (c >= 33 && c <= 126);
}


/// @brief character equal
/// @return если не равны - CELL_ERR (0b11), иначе один из тех равных символов
cell_t _cheq(cell_t c1, cell_t c2, cell_t c3) {
    if (c1 == c2 && c2 == c3)
        return c1; 
    return CELL_ERR; 
}

cell_t who_win(cell_t* cells) {

    // 0 1 2
    // 3 4 5
    // 6 7 8

    static cell_t winner;
    for (int i = 0; i < 3; i++) {
        winner = _cheq(cells[i*3 + 0], cells[i*3 + 1], cells[i*3 + 2]);
        if (winner != CELL_ERR && winner != CELL_SPACE) return winner;
    }

    for (int i = 0; i <= 6; i += 3) {
        winner = _cheq(cells[i + 0], cells[i + 1], cells[i + 2]);
        if (winner != CELL_ERR && winner != CELL_SPACE) return winner;
    }

    winner = _cheq(cells[0], cells[4], cells[8]);
    if (winner != CELL_ERR && winner != CELL_SPACE) return winner;

    winner = _cheq(cells[6], cells[4], cells[2]);
    if (winner != CELL_ERR && winner != CELL_SPACE) return winner;

    for (int i = 0; i < 9; i++)
        if (cells[i] == CELL_SPACE) return CELL_SPACE;

    return CELL_ERR;
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



char cell_to_char(cell_t cell) {
         if (cell == CELL_SPACE) return ' ';
    else if (cell == CELL_PL1)   return 'x';
    else if (cell == CELL_PL2)   return 'o';
    else if (cell == CELL_ERR)   return 'E';
    else                         return '?';
}



int compare(playground& pg1, playground& pg2) {
    unsigned char* pgg1 = pg1.get_ground();
    unsigned char* pgg2 = pg2.get_ground();
    for (int i = 0; i < PLAYGROUND_BYTES; i++) {
        if (pgg1[i] > pgg2[i]) return  1;
        if (pgg1[i] < pgg2[i]) return -1;
    }
    return 0;
}

playground transform(playground& pg, unsigned char i) {
    static int mix, miy, mjx, mjy;
    
    i &= 0b111;

    miy = mjx =    i >> 2;
    mix = mjy = (~(i >> 2)) & 0b1;

    if (i & 0b1) {
        mix *= -1;
        mjx *= -1;
    }

    if (i & 0b10) {
        miy *= -1;
        mjy *= -1;
    }


    playground npg = playground();

    for (int y = -4; y <= 4; y++)
        for (int x = -4; x <= 4; x++)
            npg.set_cell((mix * x + mjx * y + 4) | ((miy * x + mjy * y + 4) << 4), pg.get_cell((x + 4) | ((y + 4) << 4)));
    
    return npg;
}

playground::playground() {
    for (int i = 0; i < PLAYGROUND_BYTES; i++) ground[i] = 0;
    // третий бит отвечает за хранение того, кто сейчас ходит, 
    // с тетьего по 8 - куда можно ходить (если значение больше 8, ходить можно куда угодно)
    ground[20] |= 0b11111100; 
}
playground::~playground() { }

unsigned char playground::get_cell(pos_t pos) {
    static size_t x, y;
    x = pos & 0b1111;
    y = pos >> 4;
    if (x >= PLAYGROUND_SIDE_SIZE * PLAYGROUND_SIDE_SIZE || y >= PLAYGROUND_SIDE_SIZE * PLAYGROUND_SIDE_SIZE) 
        return CELL_ERR;
    // xbox - кордината коробки 3 на 3 (0, 1, 2)
    // xinbox - кордината ячейки в коробке (0, 1, 2)
    static int xinbox, yinbox, xbox, ybox;
    xinbox = x % PLAYGROUND_SIDE_SIZE;
    yinbox = y % PLAYGROUND_SIDE_SIZE;

    xbox = (x - xinbox) / PLAYGROUND_SIDE_SIZE;
    ybox = (y - yinbox) / PLAYGROUND_SIDE_SIZE;


    
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






void playground::set_cell(pos_t pos, cell_t c) {
    static size_t x, y;
    x = pos & 0b1111;
    y = pos >> 4;
    if (x >= PLAYGROUND_SIDE_SIZE * PLAYGROUND_SIDE_SIZE || y >= PLAYGROUND_SIDE_SIZE * PLAYGROUND_SIDE_SIZE) 
        return;
    // xbox - кордината коробки 3 на 3 (0, 1, 2)
    // xinbox - кордината ячейки в коробке (0, 1, 2)
    static int xinbox, yinbox, xbox, ybox;
    xinbox = x % PLAYGROUND_SIDE_SIZE;
    yinbox = y % PLAYGROUND_SIDE_SIZE;

    xbox = (x - xinbox) / PLAYGROUND_SIDE_SIZE;
    ybox = (y - yinbox) / PLAYGROUND_SIDE_SIZE;


    
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

bool playground::move(pos_t pos) {
    
    cell_t move_cell_c = get_cell(pos);
    if (move_cell_c != CELL_SPACE) return false;

    pos_t move_box_p = get_move_box();


    pos_t wanna_move_box_p;
    wanna_move_box_p = (pos & 0b1111) % PLAYGROUND_SIDE_SIZE;
    wanna_move_box_p |= ((pos >> 4) % PLAYGROUND_SIDE_SIZE) << 4;


    if (move_box_p != POS_MAX && wanna_move_box_p != move_box_p) return false;

    cell_t who_move = get_who_moves();
    if (who_move != CELL_PL1 && who_move != CELL_PL2) return false;

    set_cell(pos, who_move);
    swap_players();
}

bool playground::move(int x, int y) {
    x &= 0b1111;
    y &= 0b1111;

    return move((cell_t)(x) + (cell_t)(y << 4));
}

inline pos_t index_to_pos(pos_t index, unsigned char side_size) {
    pos_t pos = index % side_size;
    pos += ((index - pos) / side_size) << 4;
}

inline pos_t pos_to_index(pos_t pos, unsigned char side_size) {
    return (pos >> 4) * side_size + (pos & (pos_t)0b1111);
}

cell_t playground::get_who_moves() {
    return _get2(ground[20], 2);
}

pos_t playground::get_move_box() {

    //    0 1 2    
    //
    // 0  0 1 2
    // 1  3 4 5
    // 2  6 7 8


    return index_to_pos((ground[20] & ~(unsigned char)0b1111) >> 4, 3);
}


void playground::set_who_moves(cell_t cell) {
    _set2(ground[20], 2, cell);
}

void playground::set_move_box(pos_t pos) {

    //    0 1 2    
    //
    // 0  0 1 2
    // 1  3 4 5
    // 2  6 7 8

    ground[20] &= ~(unsigned char)0b1111;
    ground[20] |= pos_to_index(pos, 3) << 4;

}

static cell_t cells[9];
bool playground::is_box_marked(pos_t pos) {
    static int i;
    i = 0;
    for (int y = 0; y < 2; y++)
        for (int x = 0; x < 2; x++)
        {
            cells[i] = get_cell(pos + x + (y << 4));
            i++;
        }
    
    return !(who_win(cells) == CELL_SPACE);
}

void generate_legal_moves(playground& pg, pos_t* moves_restrict) {
    pos_t move_box = pg.get_move_box();
    int moves_len = 0;
    if (move_box >> 4 > 2 || move_box & 0b1111 > 2) {
        for (int yb = 0; yb < 2; yb++)
            for (int xb = 0; xb < 2; xb++)
            {
                if (pg.is_box_marked(xb | (yb << 4))) continue;
                for (int y = 0; y < 2; y++)
                    for (int x = 0; x < 2; x++)
                    {
                        if (pg.get_cell((xb * 3 + x) | ((yb * 3 + y) << 4)) == CELL_SPACE) {
                            moves_restrict[moves_len] = (xb * 3 + x) | ((yb * 3 + y) << 4);
                            moves_len++;
                        }
                    }
            }
    }
}