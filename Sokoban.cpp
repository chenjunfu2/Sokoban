#include "error.h"
#include "menu.h"
#include "game.h"
#include "read_map.h"
#include "make_map.h"
#include "switch.h"

int main(void)
{
	ShowCursor(false);//隐藏光标

	map_j mpj;
	fstream fin_a;

	//打开地图
	if (error(open_map_r(fin_a)))
	{
		if (!error(make_map()))
			cerr << "地图模板写入成功,重启后生效！" << endl << endl;
		else
		{
			cerr << "地图模板写入失败！" << endl << endl;
			close_map_fin(fin_a);
			sypose();
			return 1;
		}
		close_map_fin(fin_a);
		sypose();
		return 0;
	}

	//读取地图
	{
		cout << "地图读取中..." << endl;
		mpj = read_map_all(fin_a);
		Sleep(500);

		if (error(mpj.error))//读取判断
		{
			close_map_fin(fin_a);
			sypose();
			return 1;
		}
		else
		{
			cout << "读取成功！" << endl;
			Sleep(510);
			system("cls");
		}
	}
	

	//关卡选择、进行游戏
	game_switch(mpj, fin_a);

	
//end:
	//delete_map(mpa);
	close_map_fin(fin_a);
	sypose();//等待函数

	return 0;
}


