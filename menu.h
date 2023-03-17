#pragma once

#ifndef _menu
#define _menu

#include <iostream>
#include <string>
#include <conio.h>

#define Cooder				"小陈"
#define VersionNumber		"3.6"
#define CopyRightYearBeg	"2021"
#define CopyRightYearEnd	"2023"

//主菜单
extern inline int menu_page(void);
//开始游戏
extern inline int menu_game(void);
//游戏说明
extern inline void menu_explain(void);
//关于应用
extern inline void menu_about(void);



//等待用户的一个输入
extern inline void sypose(void);
//让用户确定是否做某事
extern inline bool sure(const char* be);

#endif