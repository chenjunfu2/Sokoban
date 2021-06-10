#pragma once

#ifndef _ConsoleAPI
#define _ConsoleAPI

#include <Windows.h>

//改变光标
extern inline void move_g(short x, short y);
//得到当前光标设置
extern inline bool get_show(void);//return true代表光标可见
//光标隐藏||显示
extern inline void ShowCursor(bool Show);//Show=false代表光标不可见
//检查是否隐藏光标
extern inline void see_cursor_hide_show(bool Show);//false隐藏 true显示

#endif