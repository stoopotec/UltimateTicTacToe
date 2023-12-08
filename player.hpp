#pragma once

#include "playground.hpp"

struct playground;

class Player
{
public:
    Player();
    virtual void next_move(int& x, int& y, playground& playground) = 0;
};

class ConsolePlayer : public Player
{
public:
    ConsolePlayer();
    void next_move(int& x, int& y, playground& playground) override;
};

class BotPlayer : public Player
{
public:
    BotPlayer();
    void next_move(int& x, int& y, playground& playground) override;
};