#pragma once

#ifndef _play
#define _play

#include "game.h"

//typedef bool (*movefun)(unsigned int**, int, int, peo&, NODE&, NODE&);

int game_p(map_a& mpa, DWORD msec, bool playback);
bool move_p_f(unsigned int** map, int mx, int my, peo& pe, NODE& nodeR, NODE& nodeF);

#endif