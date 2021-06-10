#include "menu.h"

using namespace std;


//主菜单
extern inline int menu_page(void)
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
extern inline int menu_game(void)
{
	cout << "------------游戏-----------\n";
	cout << " 1.正常模式\t2.残局模式\n";
	cout << " 3.回放模式\t4.返回上层\n";
	cout << "---------------------------\n";
	cout << "\n请按下对应按键选择\n";
	int input = _getch();
	while (input < '1' || input > '4')
		input = _getch();

	return input;
}

//游戏说明
extern inline void menu_explain(void)
{
	cout << "游戏说明：\n\n";
	cout << "1.请使用:\n"\
		"  W (上) A (左) S (下) D (右) 或\n"\
		"  ↑(上) ←(左) ↓(下) →(右) 操控人物\n";
	cout << "2.在游戏时:\n"\
		"  按Q键则返回上一界面\n"\
		"  按R键则撤销上一操作\n"\
		"  按F键则重做上一操作\n"\
		"  按E键则重玩当前关卡\n"\
		"  按Z键则转跳上一关卡\n"\
		"  按X键则转跳下一关卡\n"\
		"  按C键则进入选关模式\n"\
		"  按V键则保存当前残局\n";
	cout << "3.按键不分大小写，但要注意可能需要使用英文输入法，否则按键会被输入法优先抓走导致无法及时输入\n";
	cout << "4.游戏地图在第一次打开时会生成，需要重启游戏\n";
	cout << "5.游戏地图可编辑，可增删，但请严格遵守地图注意事项并根据地图表现型对应修改\n\n";
	cout << "感谢您的理解与支持，如有BUG还请及时反馈哦~\n";
	cout << "\n按任意键返回...\n";
	_getch();

	return;
}

//关于应用
extern inline void menu_about(void)
{
	cout << "--------------关于-------------\n";
	cout << " 编 写 者：" << Cooder << "\n";
	cout << " 编写日期：" << __DATE__<< " " << __TIME__ << "\n";//CoodingDay
	cout << " 版 本 号：" << VersionNumber << "\n";
	cout << " 版权所有：CopyRight (C) " << CopyRightYear << "\n";
	cout << "-------------------------------\n";
	cout << "\n按任意键返回...\n";
	_getch();

	return;
}



//等待用户的一个输入
extern inline void sypose(void)
{
	cout << "请按任意键继续. . .";
	_getch();
}

//让用户确定是否做某事
extern inline bool sure(const char* be)
{
	cout << "\n确认要" << be << "吗？(y/n)\n";

	int input;
	while ((input = tolower(getchar())) != 'y' && input != 'n')
	{
		if (input != '\n')
			while (getchar() != '\n')continue;
	}
	if (input != '\n')
		while (getchar() != '\n')continue;

	if (input == 'y')
		return true;
	else
		return false;
}