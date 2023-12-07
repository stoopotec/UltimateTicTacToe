#include <iostream>
#include "playground.hpp"
#include "player.hpp"

int main(int argc, char** argv)
{
    // ЭТО ПРИМЕР!!!! желательно делать так, но если что-то придумаешь прикольное, то можешь мне предложить и делать

    // массив из указателей на Player, нужно для апкаста. (watch extremecode)
    Player* players[2];

    ConsolePlayer p1 = ConsolePlayer();
    players[0] = &p1;
    ConsolePlayer p2 = ConsolePlayer();
    players[1] = &p2;

    playground ground = playground();

    
}