#pragma once

#ifndef _read_map
#define _read_map

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "error.h"
#include "linked_list.h"

typedef unsigned long long ULL;

//地图及符号数组结构体
typedef struct map_a
{
	//地图大小及指针
	unsigned int mapx = 0;
	unsigned int mapy = 0;
	unsigned int** map = NULL;
	unsigned int** lmap = NULL;
	//对应地图符号
	char map_f[7][3] = { {0} };
	//关卡号
	unsigned int checkpoint = 0;
	//已走的步数和链表
	unsigned int nodeRnum = 0;
	NODE nodeR;
	//撤销的步数
	unsigned int nodeFnum = 0;
	NODE nodeF;
	//是否错误及报错码
	ERR error;
}MAPA;

//关卡选择结构体
typedef struct map_j
{
	//关卡个数
	ULL map_num = 0;
	//关卡文件位置
	std::vector<std::streamoff> map_checkpoint;
	//是否错误及报错码
	ERR error;
}MAPJ;

//打开地图
extern inline ERR open_map_r(std::fstream& fin_a);
//关闭地图
extern inline void close_map_fin(std::fstream& fin_a);
//重置部分地图数据
extern inline void init_map_data(map_a& mpa);
//清理地图
bool delete_map(map_a& mpa);
//重玩拷贝旧地图到新地图
extern inline void copy_lmapTOmap(map_a& mpa);



//关卡转跳
bool jump_map(std::fstream& fin_a, map_j& mpj, map_a& mpa, int map_num);
//跳过行
extern inline bool jump_line(std::fstream& fin_a, map_a& mpa, int num);
//跳至下一个地图
extern inline bool next_map(std::fstream& fin_a, map_a& mpa);



//读取关卡号
bool read_checkpoint(std::fstream& fin_a, map_a& mpa, map_j& mpj, int mpn);
//读取地图符号
bool read_symbol(std::fstream& fin_a, map_a& mpa);
//读取地图大小(x,y)
bool read_size(std::fstream& fin_a, map_a& mpa);
//分配地图内存
bool new_map(map_a& mpa);
//读取地图数据
bool read_map(std::fstream& fin_a, map_a& mpa);
//关卡个数读取并将每一关卡的文件随机访问位置储存
map_j read_map_all(std::fstream& fin_a);
//关卡选择菜单
int map_jump_menu(map_j& mp_jump);



//读取关卡
map_a read_mapCp(map_j& mpj, std::fstream& fin_a, int mpn);

#endif