#include "make_map.h"

using namespace std;

extern inline bool open_map_m(fstream& fout_a)
{
	fout_a.open("game.ini", ios_base::out | ios_base::trunc);
	if (!fout_a.is_open())
	{
		fout_a.close();
		fout_a.clear();
		return false;
	}
	return true;
}

extern inline void close_map_fout(fstream& fout_a)
{
	fout_a.clear();
	fout_a.close();
}

extern inline bool description(fstream& fout_a)
{
	fout_a << "地图表现型:" << "0:空地 1:墙壁 2:人 3:箱子 4:目的地 5:箱子在目的地 6:人在目的地" << endl;
	fout_a << "注意事项:" << "请严格按照模板进行修改，否则会导致不必要的麻烦！  "
		<< "1.关卡号不可断续，必须按照顺序从1开始，接着2、3、4...以此类推，且至少有一个关卡  "
		<< "2.每一关卡的对应地图符号可以不一样，只有每一个数字冒号后面的两个字节可以修改  "
		<< "3.每一关卡地图大小可以不一样，当地图大小修改后，下面的地图标记请根据大小对齐，每一列数字之间请使用空格分开，每一行数字之间只可使用一个换行符  "
		<< "4.多个关卡请每一个关卡使用两个换行符隔开  "
		<< "5.请不要增加无意义的空行  "
		<< "6.地图内有且只能有一个\"人\"(地图表现型2)  "
		<< "7.如果再次需要模板请移走或删除当前文件夹下的地图文件并再次运行此应用。" << endl << endl;

	if (!fout_a.good())
		return false;
	return true;
}

extern inline bool checkpoint(fstream& fout_a)
{
	for (int k = 0, l = 0; k < MAX_MAP; ++k, l = 0)
	{
		//3
		fout_a << "关卡:" << k + 1 << endl;

		//4
		fout_a << "对应地图符号:";
		for (auto mp : map_f[k])
			fout_a << l++ << ":" << mp;

		//5
		fout_a << endl << "地图大小:" << MAP_X << "*" << MAP_Y << endl;

		//6
		fout_a << "地图标记:" << endl;
		for (int i = 0; i < MAP_Y; ++i)
		{
			for (int j = 0; j < MAP_X; ++j)
			{
				fout_a << map[k][i][j] << " ";
			}
			fout_a << endl;
		}
		fout_a << endl;
	}
	if (!fout_a.good())
		return false;
	return true;
}



extern inline ERR make_map(void)
{
	fstream fout_a;
	ERR error;

	if (!open_map_m(fout_a))
	{
		no_good(error, open_failed, make_map_F);
		return error;
	}
	if (!description(fout_a))
	{
		no_good(error, description_WriteFalse, make_map_F);
		return error;
	}
	if (!checkpoint(fout_a))
	{
		no_good(error, checkpoint_WriteFalse, make_map_F);
		return error;
	}
	close_map_fout(fout_a);

	return error;
}