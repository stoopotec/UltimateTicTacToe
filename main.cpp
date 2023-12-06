#include <iostream>
#include "interface.hpp"

int main(int argc, char** argv)
{
    // ЭТО ПРИМЕР!!!! желательно делать так, но если что-то придумаешь прикольное, то можешь мне предложить и делать

    // массив из указателей на Player, нужно для апкаста. (watch extremecode)
    Player* players[2];

    players[0] = &ConsolePlayer(cell(false, 'x'));
    players[1] = &ConsolePlayer(cell(false, 'o'));

    playground ground = playground(3, players, 2);

    
}