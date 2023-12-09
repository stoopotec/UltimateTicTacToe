#include <iostream>
#include <vector>
#include "playground.hpp"
#include "player.hpp"

#define TEST_SUCCESS EXIT_SUCCESS
#define TEST_FAILURE EXIT_FAILURE
#define TEST_VISUAL_SUCCESS 0b100
#define TEST_VISUAL_FAILURE 0b010

#define TEST_IS_VISUAL(X) (bool)(X & ~0b1)

void gp(playground& g)
{
    printf("board view:\n");
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            unsigned char c = g.get_cell_on_pos(x, y);
            putchar(cell_to_char(c));
        }
        putchar('\n');
    }
    putchar('\n');
    printf("bits view:\n");
    printf("cell to char  |  byte\n");
    for (int i = 0; i < PLAYGROUND_BYTES; i++) {
        unsigned char gb = *(g.get_ground() + i);

        for (int b = 0; b < sizeof(unsigned char) * 8; b += 2) {
            putchar(cell_to_char((gb >> b) & (unsigned char)0b11));
            putchar(' ');
        }
        printf("      |  ");
        for (int b = 0; b < sizeof(unsigned char) * 8; b += 2) {
            putchar(((gb >>  b   ) & (unsigned char)0b1) ? '1' : '0');
            putchar(((gb >> (b+1)) & (unsigned char)0b1) ? '1' : '0');
            putchar(' ');
        }
        putchar('\n');
    }
}
int playground_get_set_test(bool visual)
{
    playground ground = playground();
    if (visual) goto vis;
    return TEST_VISUAL_FAILURE;


    // for (unsigned char fill = 0b00; fill <= 0b11; fill++)
    //     for (int y = 0; y < 9; y++)
    //         for (int x = 0; x < 9; x++)
    //         {
    //             ground.set_cell_on_pos(x, y, fill);
    //             for (int yy = 0; yy < 9; yy++)
    //                 for (int xx = 0; xx < 9; xx++)
    //                 {
    //                     unsigned char cc = ground.get_cell_on_pos(xx, yy);
    //                     if (xx == x && yy == x) {
    //                         if (cc != fill) return TEST_FAILURE;
    //                     }
    //                     else if (cc != CELL_SPACE) return TEST_FAILURE;
    //                 }
    //             ground.set_cell_on_pos(x, y, CELL_SPACE);
    //         }

    // return TEST_SUCCESS;



    vis:
    printf("press any key to see playground get set test!\n");
    for (unsigned char fill = 0b01; fill < 0b100; fill--)
        for (int y = 0; y < 9; y++)
            for (int x = 0; x < 9; x++)
            {
                std::cin.get();
                ground.set_cell_on_pos(x, y, fill);
                system("clear");
                gp(ground);
            }
            
    return TEST_VISUAL_SUCCESS;
}







int main(int argc, char** argv)
{
    using std::vector;

    vector<int (*)(bool)> tests = vector<int (*)(bool)>();
    bool visual = (argv[1][0] == '-' && argv[1][1] == 'v' && argv[1][2] == '\0');


    tests.push_back(playground_get_set_test);


    int total = 0;
    int failure = 0;
    int failure_visual = 0;
    for (int i = 0; i < tests.size(); i++) {
        total++;
        int result = tests[i](visual);
        if (result == TEST_FAILURE) {
            failure++;
            printf("test[%i] failure\n", i);
        }
        if (result == TEST_VISUAL_FAILURE) {
            failure_visual++;
            printf("test[%i] only is visual\n", i);
        }
    }
    printf("total: %i, %i failure\n", total, failure);
}