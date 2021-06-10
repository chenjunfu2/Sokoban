#include "read_map.h"

using namespace std;

//打开地图
extern inline ERR open_map_r(fstream& fin_a)//, map_a& mpa
{
	ERR error;
	fin_a.open("game.ini", ios_base::in);
	if (!fin_a.is_open())
	{
		fin_a.close();
		fin_a.clear();
		no_good(error, open_failed, open_map_F);
	}
	return error;
}

//关闭地图
extern inline void close_map_fin(fstream& fin_a)
{
	fin_a.clear();
	fin_a.close();
}

//重置部分地图数据
extern inline void init_map_data(map_a& mpa)
{
	mpa.nodeRnum = 0;
	mpa.nodeFnum = 0;
	Del_AllQueue(mpa.nodeR);
	Del_AllQueue(mpa.nodeF);
}

//清理地图
bool delete_map(map_a& mpa)
{
	//删除地图
	if (mpa.map == NULL || mpa.lmap == NULL)
		return true;

	try {
		for (unsigned int i = 0; i < mpa.mapy; ++i)
		{
			delete[] mpa.map[i];
			delete[] mpa.lmap[i];
			mpa.map[i] = NULL;
			mpa.lmap[i] = NULL;
		}
		delete[] mpa.map;
		delete[] mpa.lmap;
		mpa.map = NULL;
		mpa.lmap = NULL;
	}
	catch (...) {
		mpa.map = NULL;
		mpa.lmap = NULL;
		no_good(mpa.error, delete_failed, delete_map_F);
		return false;
	}

	//重置地图
	init_map_data(mpa);

	return true;
}

//重玩拷贝旧地图到新地图
extern inline void copy_lmapTOmap(map_a& mpa)
{
	for (unsigned int i = 0; i < mpa.mapy; ++i)
	{
		for (unsigned int j = 0; j < mpa.mapx; ++j)
		{
			mpa.map[i][j] = mpa.lmap[i][j];
		}
	}

	return;
}



//关卡转跳
bool jump_map(fstream& fin_a, map_j& mpj, map_a& mpa, int map_num)
{
	if (map_num <= 0 || map_num > mpj.map_num)
	{
		no_good(mpa.error, checkpoint_ERROR, jump_map_F);
		return false;
	}
	if (map_num == mpa.checkpoint)
		return true;

	fin_a.clear();
	fin_a.seekg(mpj.map_checkpoint[map_num - 1], ios::beg);

	if (!fin_a.good())
	{
		if (fin_a.eof())
		{
			fin_a.clear();
			no_good(mpa.error, fst_eof, jump_map_F);
			return false;
		}
		no_good(mpa.error, map_JumpFalse, jump_map_F);
		return false;
	}

	return true;
}

//跳过行
extern inline bool jump_line(fstream& fin_a, map_a& mpa, int num)
{
	for (int i = 0; i < num; ++i)
	{
		while (fin_a.get() != '\n')
		{
			if (!fin_a.good())
			{
				if (fin_a.eof())
					no_good(mpa.error, fst_eof, jump_line_F);
				else
					no_good(mpa.error, line_JumpFalse, jump_line_F);

				return false;
			}
		}
	}
	return true;
}

//跳至下一个地图
extern inline bool next_map(fstream& fin_a, map_a& mpa)
{
	while (fin_a.get() != '\n')
	{
		if (!fin_a.good())
		{
			if (fin_a.eof())
				no_good(mpa.error, fst_eof, next_map_F);
			else
				no_good(mpa.error, map_JumpFalse, next_map_F);

			return false;
		}
	}
	return true;
}



//读取关卡号
bool read_checkpoint(fstream& fin_a, map_a& mpa, map_j& mpj, int mpn)
{
	//map_j mpj = read_map_all();
//conti:
	fin_a.ignore(6, ':');
	fin_a >> mpa.checkpoint;

	if (!fin_a.good())
	{
		if (fin_a.eof())
			no_good(mpa.error, fst_eof, read_checkpoint_F);//goto jump;
		else
			no_good(mpa.error, checkpoint_ReadFalse, read_checkpoint_F);
		return false;
	}
	if (mpa.checkpoint != mpn && mpn <= mpj.map_num && mpj.map_num > 0)
	{
		no_good(mpa.error, checkpoint_ERROR, read_checkpoint_F);
		return false;
	}

	return true;
}

//读取地图符号
bool read_symbol(fstream& fin_a, map_a& mpa)
{
	fin_a.ignore(14, ':');
	for (int i = 0; i < 7; ++i)
	{
		fin_a.ignore(3, ':');
		fin_a.get(mpa.map_f[i], 3);
		mpa.map_f[i][2] = '\0';

		if (!fin_a.good())
		{
			if (fin_a.eof())
			{
				no_good(mpa.error, fst_eof, read_symbol_F);
			}
			no_good(mpa.error, list_ReadFalse, read_symbol_F);

			fin_a.clear();
			return false;
		}
	}
	return true;
}

//读取地图大小(x,y)
bool read_size(fstream& fin_a, map_a& mpa)
{
	fin_a.ignore(10, ':');
	fin_a >> mpa.mapx;
	if (!fin_a.good())
	{
		if (fin_a.eof())
			no_good(mpa.error, fst_eof, read_size_F);
		else
			no_good(mpa.error, sizeX_ReadFalse, read_size_F);
		return false;
	}

	fin_a.ignore(2, '*');
	fin_a >> mpa.mapy;
	if (!fin_a.good())
	{
		if (fin_a.eof())
			no_good(mpa.error, fst_eof, read_size_F);
		else
			no_good(mpa.error, sizeY_ReadFalse, read_size_F);
		return false;
	}
	return true;
}

//分配地图内存
bool new_map(map_a& mpa)
{
	try {
		mpa.map = new unsigned int* [mpa.mapy];//throw bad_alloc;
		mpa.lmap = new unsigned int* [mpa.mapy];//throw bad_alloc;
	}
	catch (bad_alloc) {
		mpa.map = NULL;
		mpa.lmap = NULL;
		no_good(mpa.error, mapY_NewFalse, new_map_F);
		return false;
	}

	for (unsigned int i = 0; i < mpa.mapy; ++i)
	{
		try {
			mpa.map[i] = new unsigned int[mpa.mapx];//throw bad_alloc;
			mpa.lmap[i] = new unsigned int[mpa.mapx];//throw bad_alloc;
		}
		catch (bad_alloc) {
			delete_map(mpa);
			mpa.map = NULL;
			mpa.lmap = NULL;
			no_good(mpa.error, mapX_NewFalse, new_map_F);
			return false;
		}
	}
	return true;
}

//读取地图数据
bool read_map(fstream& fin_a, map_a& mpa)
{
	//bool have_people = false;

	for (unsigned int i = 0; i < mpa.mapy; ++i)//read
	{
		for (unsigned int j = 0; j < mpa.mapx; ++j)
		{
			fin_a >> mpa.map[i][j];
			mpa.lmap[i][j] = mpa.map[i][j];
			//cout << mpa.map[i][j];
			//have_people = have_people || (mpa.map[i][j] == 2) || (mpa.map[i][j] == 6);

			if (!fin_a.good())
			{
				if (i < (mpa.mapx - 1) || j < (mpa.mapy - 1))
				{
					if (fin_a.eof())
						no_good(mpa.error, fst_eof, read_map_F);
					else
						no_good(mpa.error, map_ReadFalse, read_map_F);
					delete_map(mpa);
				}
				fin_a.clear();

				return false;
			}
		}
		jump_line(fin_a, mpa, 1);//错误检查使用
		//cout << endl;
	}

	return true;
}

//关卡个数读取并将每一关卡的文件随机访问位置储存
map_j read_map_all(fstream& fin_a)
{
	fin_a.seekg(0, ios::beg);
	map_j mpj = { 0 };
	string str, aims = "关卡:";

	while (true)
	{
		getline(fin_a, str, '\n');

		if (!fin_a.good())
		{
			if (fin_a.eof())
			{
				//no_good(mpj.error, fst_eof);
				fin_a.clear();
				fin_a.seekg(0, ios::beg);
				break;
			}
			no_good(mpj.error, checkpoint_ReadFalse, read_map_all_F);
			fin_a.clear();
			fin_a.seekg(0, ios::beg);
			break;
		}

		if (str.find(aims) != string::npos)
		{
			//cout << str << endl;
			fin_a.seekg(-(long)(str.size() + 1), ios_base::cur);//返回上一行

			mpj.map_checkpoint.push_back(fin_a.tellg());//储存当前文件位置

			while (fin_a.get() != '\n')//跳过此行防止重复记录
			{
				if (!fin_a.good())
				{
					if (fin_a.eof())
						no_good(mpj.error, fst_eof, read_map_all_F);
					else
						no_good(mpj.error, line_JumpFalse, read_map_all_F);
					goto end;
				}
			}
		}
	}
end:
	mpj.map_num = mpj.map_checkpoint.size();

	return mpj;
}

//关卡选择菜单
int map_jump_menu(map_j& mp_jump)
{
	cout << "选择关卡：" << "1--" << mp_jump.map_num << endl;

	cout << "返回上层：-1" << endl << endl;

	int input;
	cout << "请选择\n";
	cin >> input;
	while (!cin.good() || (input <= 0 || input > mp_jump.map_num) && input != -1)
	{
		cin.clear();
		cout << "请重新输入\n";
		while (getchar() != '\n')continue;
		cin >> input;
	}
	while (getchar() != '\n')continue;

	return input;
}



//读取关卡
map_a read_mapCp(map_j& mpj, fstream& fin_a, int mpn)
{
	map_a mpa;

	//1
	if (mpn < 1 || mpn > mpj.map_num)
	{
		no_good(mpa.error, checkpoint_ERROR, read_mapCp_F);
		return mpa;
	}

	//2
	fin_a.clear();
	if (!jump_map(fin_a, mpj, mpa, mpn))
		return mpa;

	//3
	if (!read_checkpoint(fin_a, mpa, mpj, mpn))
		return mpa;

	//4
	if (!read_symbol(fin_a, mpa))
		return mpa;

	//5
	if (!read_size(fin_a, mpa))
		return mpa;

	//6
	if (!jump_line(fin_a, mpa, 2))
		return mpa;

	//7
	if (!new_map(mpa))
		return mpa;

	//8
	if (!read_map(fin_a, mpa))
		return mpa;


	return mpa;
}