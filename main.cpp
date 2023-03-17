#include "main.h"

using namespace std;

int main(int argc, char* argv[])//以Sokoban后缀文件参数启动直接进入播放
{
	system("cls");//清理命令行界面
	ShowCursor(false);//隐藏光标

	if (argc == 2 || argc == 3)
	{
		bool p;
		map_a mpa;

		//打开并读取文件
		if (error((mpa = Read_MLD(argv[1], p)).error))
		{
			sypose();
			return 1;
		}

		//判断是否是残局文件
		if (!p)
		{
			ShowCursor(true);
			if (!sure("播放残局文件"))
				return 0;
			ShowCursor(false);
		}
			
		//判断是否有命令行参数,给予不同的播放间隔（有则指定无则默认100ms）
		if (argc >= 2)
			game_p(mpa, 100, p);
		else
			game_p(mpa, atol(argv[2]), p);

		//清理并等待
		delete_map(mpa);
		sypose();
		return 0;
	}


	//打开地图
	fstream fin_a;
retry1:
	if (error(open_map_r(fin_a)))
	{
		if (!error(make_map()))
			cerr << "地图模板写入成功！" << endl << endl;
		else
		{
			cerr << "地图模板写入失败！" << endl << endl;
			close_map_fin(fin_a);
			sypose();
			return 1;
		}
		close_map_fin(fin_a);
		sypose();
		system("cls");
		goto retry1;
	}


	//读取地图
	map_j mpj;
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
			Sleep(500);
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


