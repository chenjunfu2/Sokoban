#pragma once

#ifndef _game
#define _game

#include <iostream>
#include <conio.h>
#include <stdlib.h>

#include "ConsoleAPI.h"
#include "linked_list.h"
#include "read_map.h"
#include "menu.h"
#include "error.h"

//直接处理
#define REDO		0//重做
#define MOVE		1//移动
#define UNDO		2//撤销
#define NODO		3//重绘
#define REGAME		4//重玩

//返回处理
#undef ERROR
#define ERROR		-1//可恢复错误
#define EXITERROR	-2//不可恢复错误
#define LASTCHECK	5//上一关
#define NEXTCHECK	6//下一关
#define SWITCH		7//选关
#define SAVE		8//保存残局
#define QUIT		9//退出
#define END			10//结束




//玩家坐标结构体
typedef struct peo
{
	int x = 0;
	int y = 0;
	ERR error;
}PEO;


//获取人坐标
extern inline PEO find_peo(unsigned int** map, int mx, int my);
//移动人
extern inline void move_p(const peo& pe, unsigned int** map);
//反向移动人
extern inline void reverse_move_p(const peo& pe, unsigned int** map, int list_x, int list_y);



//全局移动（用户操作）
bool move_user(unsigned int** map, int mx, int my, int x, int y, peo& pe, NODE& nodeR, NODE& nodeF);
//全局移动（重做）
bool move_f(unsigned int** map, int mx, int my, peo& pe, NODE& nodeR, NODE& nodeF);
//反向全局移动（撤销）
bool move_r(unsigned int** map, int mx, int my, peo& pe, NODE& nodeR, NODE& nodeF);



//绘制地图
template <typename T>
extern inline ERR init_map(unsigned int** map, int mx, int my, const T map_f);
//绘制人附近方块
template <typename T>
ERR init_peo(unsigned int** map, int mx, int my, const T map_f, const peo& pe);



//前后左右反转
extern inline void reverse_num(int& list_x, int& list_y);
//是否赢
extern inline bool win_g(unsigned int** map, int mx, int my);
//获取键盘输入
int get_keyb(unsigned int** map, int mx, int my, peo& pe, NODE& nodeR, NODE& nodeF);
//进行游戏
int game(map_a& mpa);

#endif