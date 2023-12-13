#include <stdio.h>

#include "player.hpp"
#include "playground.hpp"
#include "default_messages.hpp"



Player::Player(void (*move)(pos_t pos)) : move(move) { }

