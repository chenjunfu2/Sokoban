#pragma once

#ifndef _Game
#define _Game
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include "linked_list.h"
#include "error.h"
using namespace std;

//玩家坐标结构体
typedef struct peo {
	int x = 0;
	int y = 0;
	ERR error;
}PEO;

//获取玩家坐标
template <typename T>
static inline PEO find_peo(const T map, int mx, int my)
{
	PEO peo;
	for (int i = 0; i < mx; ++i)
	{
		for (int j = 0; j < my; ++j)
		{
			if (map[i][j] == 2 || map[i][j] == 6)
			{
				peo.x = i;
				peo.y = j;
				return peo;
			}
		}
	}

	no_good(peo.error, map_PeopleNull);

	return peo;
}

//移动人
template <typename T>
static inline void move_p(struct peo& pe, T map)
{
	if (map[pe.x][pe.y] == 6)
		map[pe.x][pe.y] = 4;
	else
		map[pe.x][pe.y] = 0;

	return;
}

//全局移动
template <typename T>
static inline bool move_a(T map, int mx, int my, int x, int y, NODE* node)
{
	bool mov = false;
	peo pe = find_peo(map, mx, my);
	if (error(pe.error))
		return false;

	if (pe.x + x < 0 || pe.x + x >= mx)//越界判断
		return mov;
	if (pe.y + y < 0 || pe.y + y >= my)//越界判断
		return mov;

	if (map[pe.x + x][pe.y + y] == 0)//人前面是空地
	{
		map[pe.x + x][pe.y + y] = 2;
		move_p(pe, map);
		mov = true;//移动标记
		Add_CpQueue(node, x, y, 1);
	}
	else if (map[pe.x + x][pe.y + y] == 4)//人前面是目的地
	{
		map[pe.x + x][pe.y + y] = 6;
		move_p(pe, map);
		mov = true;//移动标记
		Add_CpQueue(node, x, y, 2);
	}


	if (pe.x + (x * 2) < 0 || pe.x + (x * 2) >= mx)//越界判断
		return mov;
	if (pe.y + (y * 2) < 0 || pe.y + (y * 2) >= my)//越界判断
		return mov;

	if (map[pe.x + x][pe.y + y] == 3)//人前面是箱子
	{
		if (map[pe.x + (x * 2)][pe.y + (y * 2)] == 0)//箱子前面是空地
		{
			map[pe.x + (x * 2)][pe.y + (y * 2)] = 3;
			map[pe.x + x][pe.y + y] = 2;
			move_p(pe, map);
			mov = true;//移动标记
			Add_CpQueue(node, x, y, 3);
		}
		else if (map[pe.x + (x * 2)][pe.y + (y * 2)] == 4)//箱子前面是目的地
		{
			map[pe.x + (x * 2)][pe.y + (y * 2)] = 5;
			map[pe.x + x][pe.y + y] = 2;
			move_p(pe, map);
			mov = true;//移动标记
			Add_CpQueue(node, x, y, 4);
		}
	}
	else if (map[pe.x + x][pe.y + y] == 5)//人的前面是箱子
	{
		if (map[pe.x + (x * 2)][pe.y + (y * 2)] == 0)//箱子在目的地
		{
			map[pe.x + (x * 2)][pe.y + (y * 2)] = 3;
			map[pe.x + x][pe.y + y] = 6;
			move_p(pe, map);
			mov = true;//移动标记
			Add_CpQueue(node, x, y, 5);
		}
		else if (map[pe.x + (x * 2)][pe.y + (y * 2)] == 4)//箱子在目的地的前面是目的地
		{
			map[pe.x + (x * 2)][pe.y + (y * 2)] = 5;
			map[pe.x + x][pe.y + y] = 6;
			move_p(pe, map);
			mov = true;//移动标记
			Add_CpQueue(node, x, y, 6);
		}
	}

	return mov;
}

//前后左右反转
static inline void reverse_num(int& list_x, int& list_y)
{
	list_x = -list_x;
	list_y = -list_y;
}

//反向移动人
template <typename T>
static inline void reverse_move_p(struct peo& pe, T map, int list_x, int list_y)
{
	if (map[pe.x + list_x][pe.y + list_y] == 4)
		map[pe.x + list_x][pe.y + list_y] = 6;
	else
		map[pe.x + list_x][pe.y + list_y] = 2;
}

//反向全局移动
template <typename T>
static inline bool reverse_move_a(T map, int mx, int my, NODE* node)
{
	int list_x, list_y, list_n;
	if (Del_CpQueue(node, list_x, list_y, list_n).no_good)
		return false;
	else
		reverse_num(list_x, list_y);

	peo pe = find_peo(map, mx, my);
	if (error(pe.error))
		return false;

	if (list_n == 1 || list_n == 2)//人前面不是箱子
	{
		if (map[pe.x + list_x][pe.y + list_y] == 0)//人前面是空地
		{
			move_p(pe, map);
			map[pe.x + list_x][pe.y + list_y] = 2;
		}
		else if (map[pe.x + list_x][pe.y + list_y] == 4)//人前面是目的地
		{
			move_p(pe, map);
			map[pe.x + list_x][pe.y + list_y] = 6;
		}
	}
	else if (list_n == 3 || list_n == 4)//人前面是箱子
	{
		if (list_n == 3)//箱子前面是空地
		{
			reverse_move_p(pe, map, list_x, list_y);
			map[pe.x - list_x][pe.y - list_y] = 0;
			map[pe.x][pe.y] = 3;
		}
		else if (list_n == 4)//箱子前面是目的地
		{
			reverse_move_p(pe, map, list_x, list_y);
			map[pe.x - list_x][pe.y - list_y] = 4;
			map[pe.x][pe.y] = 3;
		}
	}
	else if (list_n == 5 || list_n == 6)//人的前面是箱子
	{
		if (list_n == 5)//箱子在目的地
		{
			reverse_move_p(pe, map, list_x, list_y);
			map[pe.x - list_x][pe.y - list_y] = 0;
			map[pe.x][pe.y] = 5;
		}
		else if (list_n == 6)//箱子在目的地的前面是目的地
		{
			reverse_move_p(pe, map, list_x, list_y);
			map[pe.x - list_x][pe.y - list_y] = 4;
			map[pe.x][pe.y] = 5;
		}
	}

	return true;
}




//改变光标
static inline void move_g(short x, short y)
{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//找到控制台窗口
		COORD coord = { x,y };//光标的结构体设置坐标
		SetConsoleCursorPosition(handle, coord);//同步到控制台(Set设置)（Console控制台）（Cursor光标） （Position位置）
}

//光标隐藏||显示
static inline void HideCursor(DWORD x,bool y)//x=1，y=0代表光标不可见
{
	CONSOLE_CURSOR_INFO cursor_info = { x, y };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}





//绘制地图
template <typename T , typename D>
static inline ERR init_map(const T map, int mx, int my,const D map_f)
{
	ERR error;

	move_g(0, 0);//清屏
	for (int i = 0; i < mx; ++i)
	{
		for (int j = 0; j < my; ++j)
		{
			if (map[i][j] >= 0 && map[i][j] <= 6)
			cout << map_f[map[i][j]];
			//cout << map[i][j];
			else
			{
				system("cls");
				no_good(error, map_Default);
				return error;
			}
		}
		cout << endl;
	}
	return error;
}

//获取键盘输入，并进行游戏
template <typename T>
static inline int get_keyb(T map, int mx, int my, NODE* node)
{
	int ch;
	int mov = 0;
	ch = _getch();
	{
		int n = tolower(ch);
		if (n != 'w' && n != 'a' && n != 's' && n != 'd' && n != 'q' && n != 'r')
			ch = _getch();
	}
	

	switch (ch)
	{
	case 72://up
	case 'w':
	case 'W':
		mov = move_a(map, mx, my, -1, 0, node);
		break;
	case 75://left
	case 'a':
	case 'A':
		mov = move_a(map, mx, my, 0, -1, node);
		break;
	case 77://right
	case 'd':
	case 'D':
		mov = move_a(map, mx, my, 0, +1, node);
		break;
	case 80://down
	case 's':
	case 'S':
		mov = move_a(map, mx, my, +1, 0, node);
		break;
	case 'q'://quit
	case 'Q':
		mov = -1;
		Del_AllQueue(node);
		break;
	case 'r'://revoke
	case 'R':
		mov = 2;
		if (!reverse_move_a(map, mx, my, node))
			mov = 0;
		//anything
		break;
	default:
		mov = 0;
		break;
	}

	return mov;
}

//是否赢
template <typename T>
static inline bool win_g(const T map,int mx,int my)
{
	for (int i = 0; i < mx; ++i)
	{
		for (int j = 0; j < my; ++j)
		{
			if (map[i][j]==3)
			{
				return false;
			}
		}
	}
	return true;
}





//进行游戏
template <typename T, typename D>
inline int game(T map, int mx, int my, D map_f)
{
	int num = 0, keyb = 0;
	NODE node;
	while (true)
	{
		if (error(init_map(map, mx, my, map_f)))//绘制地图
			return false;
		cout << "第" << num << "步" << "  ";

		if (win_g(map, mx, my))//win game判断
		{
			cout << endl << "You Win!";
			Del_AllQueue(&node);
			break;
		}

		keyb = get_keyb(map, mx, my, &node);//得到键盘输入并进行游戏
		if (keyb == 1)//如果有移动步数递增
			++num;
		else if (keyb == 2)//如果撤销步数递减
			--num;
		else if (keyb == -1)//退出游戏并返回上层
			return keyb;
	}

	return true;
}


#endif