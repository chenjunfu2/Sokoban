#pragma once

#ifndef _read_map_list
#define _read_map_list

#include <fstream>

#include "linked_list.h"
#include "make_map_list.h"
#include "read_map.h"
#include "error.h"


bool Read_Mapf_BinFile(map_a& mpa, std::fstream& fin, std::streamoff& MapfPos);
bool Read_Map_BinFile(map_a& mpa, std::fstream& fin, std::streamoff& MapPos, std::streamoff& LMapPos, bool M, bool L);
bool Read_Link_BinFile(map_a& mpa, std::fstream& fin, std::streamoff& RLinkPos, std::streamoff& FLinkPos, bool R, bool F);



map_a Read_MLD(const char* FileName, bool& playback);

#endif