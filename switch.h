#pragma once

#ifndef _switch
#define _switch

#include <stdlib.h>

#include "menu.h"
#include "game.h"
#include "play.h"
#include "read_map.h"
#include "read_map_list.h"
#include "linked_list.h"
#include "make_map_list.h"

//Ö÷²Ëµ¥
int game_switch(map_j& mpj, std::fstream& fin_a);

#endif