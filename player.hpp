#pragma once

#include "playground.hpp"

struct playground;
typedef unsigned char pos_t;

class Player
{
public:
    Player(void (*move)(pos_t pos));

    virtual void prepare_move(playground& ground) = 0;
protected:
    void (*move)(pos_t pos);
};

class BotPlayer : public Player
{
public:
    BotPlayer(void (*move)(pos_t pos));

    void prepare_move(playground& ground);
};

class GraphicPlayer : public Player
{
public:
    GraphicPlayer(void (*move)(pos_t pos));

    void prepare_move(playground& ground);
};