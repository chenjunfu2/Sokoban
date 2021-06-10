#include "ConsoleAPI.h"

//改变光标
extern inline void move_g(short x, short y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ x,y });//同步到控制台(Set设置)（Console控制台）（Cursor光标） （Position位置）
}

//得到当前光标设置
extern inline bool get_show(void)//return true代表光标可见
{
	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//STD_OUTPUT_HANDLE  STD_INPUT_HANDLE
	return cursor_info.bVisible;
}

//光标隐藏||显示
extern inline void ShowCursor(bool Show)//Show=false代表光标不可见
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, Show };//x,y  x代表光标个数？？
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//STD_OUTPUT_HANDLE  STD_INPUT_HANDLE
}

//检查是否隐藏光标
extern inline void see_cursor_hide_show(bool Show)//false隐藏 true显示
{
	if (get_show() != Show)//如果因为调整控制台导致光标重新显示则重新设置为不显示
		ShowCursor(Show);
}