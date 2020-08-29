#pragma once

#ifndef _Menu
#define _Menu
#include <iostream>
#include <conio.h>
using namespace std;


//主菜单
inline int menu_page(void)
{
	cout << "------------目录-----------\n";
	cout << " 1.开始游戏\t2.游戏说明\n";
	cout << " 3.关于应用\t4.退出应用\n";
	cout << "---------------------------\n";
	cout << "\n请按下对应按键选择\n";
	int input = _getch();
	while (input < '1' || input > '4')
		input = _getch();

	return input;
}

//开始游戏
inline int menu_game(void)
{
	cout << "------------游戏-----------\n";
	cout << " 1.顺序模式\t2.选关模式\n";
	cout << " 3.返回上层\t4.退出应用\n";
	cout << "---------------------------\n";
	cout << "\n请按下对应按键选择\n";
	int input = _getch();
	while (input < '1' || input > '4')
		input = _getch();

	return input;
}

//游戏说明
inline void menu_explain(void)
{
	cout << "游戏说明：\n";
	cout << "请使用 w(上) a(左) s(下) d(右) 或 ↑(上) ←(左) ↓(下) →(右) 操控人物\n";
	cout << "在游戏时按q键将退出游戏并返回上一界面，按r键则撤销上一操作\n";
	cout << "游戏地图在第一次打开时会生成，需要重启游戏\n";
	cout << "游戏地图可编辑，可增删，但请严格遵守地图注意事项并根据地图表现型对应修改\n";
	cout << "感谢您的理解与支持，如有BUG还请及时反馈哦\n";
	cout << "\n按任意键返回...\n";
	_getch();

	return;
}

//关于应用
inline void menu_about(void)
{
	cout << "--------------关于-------------\n";
	cout << " 编 写 者：小 陈\n";
	cout << " 编写日期：2020/8/28\n";
	cout << " 版权所有：CopyRight (C) 2020\n";
	cout << "-------------------------------\n";
	cout << "\n按任意键返回...\n";
	_getch();

	return;
}


#endif