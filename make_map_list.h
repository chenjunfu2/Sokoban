#pragma once

#ifndef _make_map_list
#define _make_map_list

#include <Windows.h>
#include <stdio.h>
#include <fstream>
#include <time.h>

#include "linked_list.h"
#include "read_map.h"
#include "error.h"

typedef unsigned long long ULL;
typedef unsigned int UI;
typedef unsigned char BYT;

#define STU(S,N) ((ULL)(((ULL)(S))<<((N-1)*8)))//str to unsigned long long
#define BTC(B,C) ((BYT)(((BYT)(B))<<(C-1)))//bin to char
#define OPB(B,N) ((B)|=((decltype(B))(1)<<(N-1))//open bin bit
#define CLB(B,N) ((B)&=(~((decltype(B))(1)<<(N-1))))//close bin bit
#define ISB(B,N) ((bool)(((B)>>(N-1))&(decltype(B)(1))))//is bin bit open

#define MAPBIN ((ULL)(STU('M', 1) | STU('A', 2) | STU('P', 3) | STU(' ', 4) | STU('B', 5) | STU('I', 6) | STU('N', 7) | STU('\0', 8)))
#define FLAG(F8,F7,F6,F5,F4,F3,F2,F1) ((BYT)(BTC(F8, 8) | BTC(F7, 7) | BTC(F6, 6) | BTC(F5, 5) | BTC(F4, 4) | BTC(F3, 3) | BTC(F2, 2) | BTC(F1, 1)))//flag

struct LinkData
{
	int list_x : 2;//移动数据x
	int list_y : 2;//移动数据y
	int list_n : 4;//移动数据n
};

//二进制文件头结构体
struct BinFileHead
{
	ULL STRULL = 0;		//文件类型MAPBIN
	ULL size = 0;		//文件大小标记sizeof(BinFileHead)

	BYT flags = 0;		//文件类型标记 1字节8位
	/*
	第08位	1表示被修改过的地图可用	0表示不可用
	第07位	1表示没有修改的地图可用	0表示不可用
	第06位	1表示已走操作链表数据可用	0表示不可用
	第05位	1表示撤销操作链表数据可用	0表示不可用
	第04位	保留备用	置0
	第03位	保留备用	置0
	第02位	保留备用	置0
	第01位	1表示是回放文件	0表示是残局文件
	*/

	UI mapX = 0;		//地图长
	UI mapY = 0;		//地图宽
	UI nodeRN = 0;		//已走步数
	UI nodeFN = 0;		//撤销步数

	std::streamoff mapF = 0;	//地图符号
	std::streamoff map = 0;		//被修改过的地图
	std::streamoff lmap = 0;	//没有修改的地图
	std::streamoff nodeR = 0;	//已走操作链表数据
	std::streamoff nodeF = 0;	//撤销操作链表数据
};

extern inline void Get_Time(char lctime[]);//sizeof (lctime的实参)应至少为28
bool Make_Mapf_BinFile(map_a& mpa, std::fstream& fout, std::streamoff& MapfPos);
bool Make_Map_BinFile(map_a& mpa, std::fstream& fout, std::streamoff& MapPos, std::streamoff& LMapPos, bool M, bool L);
bool Make_Link_BinFile(map_a& mpa, std::fstream& fout, std::streamoff& RLinkPos, std::streamoff& FLinkPos, bool R, bool F);



ERR Make_MLD(map_a& mpa, bool playback);

#endif