#include "player.hpp"


GraphicPlayer::GraphicPlayer(void (*move)(pos_t pos)) : Player(move) { }

void GraphicPlayer::prepare_move(playground& playground) { }