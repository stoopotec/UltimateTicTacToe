#pragma once

#include "playground.hpp"

class Player
{
public:
    /// @brief 
    /// @param own_cell будет извлекаться только char, если пройдёт проверку на видимый символ
    Player(cell own_cell);
    virtual void next_move(int& x, int& y, playground& playground) = 0;
    cell get_own_cell();
private:
    cell own_cell;
};

class ConsolePlayer : public Player
{
public:
    ConsolePlayer(cell own_cell);
    void next_move(int& x, int& y, playground& playground) override;
};

class BotPlayer : public Player
{
public:
    BotPlayer(cell own_cell);
    void next_move(int& x, int& y, playground& playground) override;
};