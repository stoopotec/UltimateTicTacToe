#pragma once

#include "playground.hpp"

struct playground;
typedef unsigned char pos_t;

class Player
{
public:
    Player();
    virtual void next_move(pos_t& pos, playground& playground) = 0;
};

class ConsolePlayer : public Player
{
public:
    ConsolePlayer();
    void next_move(pos_t& pos, playground& playground) override;
};

class BotPlayer : public Player
{
public:
    BotPlayer();
    void next_move(pos_t& pos, playground& playground) override;
};