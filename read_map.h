#pragma once

#ifndef READ_MAP
#define READ_MAP
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "error.h"
using namespace std;

//地图及符号数组结构体
struct map_a {
	//地图大小及指针
	int mapx = 0;
	int mapy = 0;
	int** map = nullptr;
	//对应地图符号
	char map_f[7][3] = { {0} };
	//关卡号
	int checkpoint = 0;
	//是否错误及报错码
	ERR error;
};

//关卡选择结构体
struct map_j {
	//关卡个数
	int map_num;
	//关卡文件位置
	vector<streampos> map_checkpoint;
	//是否错误及报错码
	ERR error;
};




//打开地图
inline bool open_map(fstream& fin_b, map_a& mpa)
{
	fin_b.open("game.ini", ios_base::in | ios_base::binary);
	if (!fin_b.is_open())
	{
		fin_b.close();
		fin_b.clear();
		no_good(mpa.error, open_failed);
		return false;
	}
	return true;
}

//关闭地图
inline void close_map_fin(fstream& fin_b)
{
	fin_b.clear();
	fin_b.close();
}

//清理地图
inline bool delete_map(struct map_a& mpa)
{
	try {
		for (int i = 0; i < mpa.mapx; ++i)
		{
			delete[] mpa.map[i];
			mpa.map[i] = nullptr;
		}
		delete[] mpa.map;
		mpa.map = nullptr;
	}
	catch (...) {
		mpa.map = nullptr;
		no_good(mpa.error, delete_failed);
		return false;
	}

	return true;
}

//关卡转跳
static inline int jump_map(map_j& mpj, int map_num, fstream& fin_b)
{
	if (map_num <= 0 || map_num > mpj.map_num)
	{
		return checkpoint_ERROR;
	}

	fin_b.clear();
	fin_b.seekg(mpj.map_checkpoint[map_num - 1], ios::beg);
	if (!fin_b.good())
	{
		if (fin_b.eof())
		{
			fin_b.clear();
			return fst_eof;
		}
		return map_JumpFalse;
	}

	return GOOD_ERR;
}

//跳过行
static inline bool jump_line(fstream& fin_b, map_a& mpa, int num)
{
	for (int i = 0; i < num; ++i)
	{
		while (fin_b.get() != '\n')
		{
			if (!fin_b.good())
			{
				if (fin_b.eof())
					no_good(mpa.error, fst_eof);
				else
					no_good(mpa.error, line_JumpFalse);

				return false;
			}
		}
	}
	return true;
}

//跳至下一个地图
static inline bool next_map(fstream& fin_b, map_a& mpa)
{
	while (fin_b.get() != '\n')
	{
		if (!fin_b.good())
		{
			if (fin_b.eof())
				no_good(mpa.error, fst_eof);
			else
				no_good(mpa.error, map_JumpFalse);

			return false;
		}
	}
	return true;
}

//读取关卡号
bool read_checkpoint(fstream& fin_b, map_a& mpa, map_j& mpj, int mpn)
{
	//map_j mpj = read_map_all();
conti:
	fin_b.ignore(6, ':');
	fin_b >> mpa.checkpoint;
	if (!fin_b.good())
	{
		if (fin_b.eof())
			goto jump;//no_good(mpa.error, fst_eof);
		else
			no_good(mpa.error, checkpoint_ReadFalse);
		return false;
	}

	if (mpa.checkpoint != mpn && mpn <= mpj.map_num && mpj.map_num > 0)
	{
	jump:
		int rt = 0;
		if ((rt = jump_map(mpj, mpn, fin_b)) != GOOD_ERR)
		{
			no_good(mpa.error, rt);
			return false;
		}
		else
			goto conti;
	}

	return true;
}

//读取地图符号
static inline bool read_symbol(fstream& fin_b, map_a& mpa)
{
	fin_b.ignore(14, ':');
	for (int i = 0; i < 7; ++i)
	{
		fin_b.ignore(3, ':');
		fin_b.get(mpa.map_f[i], 3);
		mpa.map_f[i][2] = '\0';

		if (!fin_b.good())
		{
			if (fin_b.eof())
			{
				no_good(mpa.error, fst_eof);
			}
			no_good(mpa.error, list_ReadFalse);

			fin_b.clear();
			return false;
		}
	}
	return true;
}

//读取地图大小(x,y)
static inline bool read_size(fstream& fin_b, map_a& mpa)
{
	fin_b.ignore(10, ':');
	fin_b >> mpa.mapx;
	if (!fin_b.good())
	{
		if (fin_b.eof())
			no_good(mpa.error, fst_eof);
		else
			no_good(mpa.error, sizeX_ReadFalse);
		return false;
	}

	fin_b.ignore(2, '*');
	fin_b >> mpa.mapy;
	if (!fin_b.good())
	{
		if (fin_b.eof())
			no_good(mpa.error, fst_eof);
		else
			no_good(mpa.error, sizeY_ReadFalse);
		return false;
	}
	return true;
}

//分配地图内存
static inline bool new_map(map_a& mpa)
{
	try {
		mpa.map = new int* [mpa.mapx];//throw bad_alloc;
	}
	catch (bad_alloc) {
		mpa.map = nullptr;
		no_good(mpa.error, mapX_NewFalse);
		return false;
	}

	for (int i = 0; i < mpa.mapy; ++i)
	{
		try {
			mpa.map[i] = new int[mpa.mapy];//throw bad_alloc;
		}
		catch (bad_alloc) {
			delete_map(mpa);
			mpa.map = nullptr;
			no_good(mpa.error, mapY_NewFalse);
			return false;
		}
	}
	return true;
}

//读取地图数据
static inline bool read_map(fstream& fin_b, map_a& mpa)
{
	bool have_people = false;

	for (int i = 0; i < mpa.mapx; ++i)//read
	{
		for (int j = 0; j < mpa.mapy; ++j)
		{
			fin_b >> mpa.map[i][j];
			have_people = have_people || (mpa.map[i][j] == 2) || (mpa.map[i][j] == 6);

			if (!fin_b.good())
			{
				if ((i < (mpa.mapx - 1) || j < (mpa.mapy - 1)) || !fin_b.eof())
				{
					delete_map(mpa);
					no_good(mpa.error, fst_eof);
				}
				else
					no_good(mpa.error, map_ReadFalse);//9 地图读取错误
				return false;
			}
		}
		jump_line(fin_b, mpa, 1);
	}

	if (!have_people)
	{
		no_good(mpa.error, map_PeopleNull);
		return false;
	}

	return true;
}

/*
for (int i = 0; i < mpa.mapy; ++i)
{
	string flag;
	getline(fin_b, flag, '\n');
	cout << flag << endl;
}
*/


//关卡个数读取并将每一关卡的文件随机访问位置储存
inline map_j read_map_all(fstream& fin_b)
{
	fin_b.seekg(0, ios::beg);
	map_j mpj = { 0 };
	string str, aims = "关卡:";

	while (true)
	{
		getline(fin_b, str, '\n');

		if (!fin_b.good())
		{
			if (fin_b.eof())
			{
				//no_good(mpj.error, fst_eof);
				fin_b.clear();
				fin_b.seekg(0, ios::beg);
				break;
			}
			no_good(mpj.error, checkpoint_ReadFalse);
			fin_b.clear();
			fin_b.seekg(0, ios::beg);
			break;
		}

		if (str.find(aims) != string::npos)
		{
			//cout << str << endl;
			fin_b.seekg(-(long)(str.size() + 1), ios_base::cur);//返回上一行

			mpj.map_checkpoint.push_back(fin_b.tellg());//储存当前文件位置

			while (fin_b.get() != '\n')//跳过此行防止重复记录
			{
				if (!fin_b.good())
				{
					if (fin_b.eof())
						no_good(mpj.error, fst_eof);
					else
						no_good(mpj.error, line_JumpFalse);
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
inline int map_jump_menu(map_j& mp_jump)
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
		while (cin.get() != '\n')
			continue;
		cin >> input;
	}

	return input;
}

//读取关卡
inline map_a read_mapCp(map_j& mpj, fstream& fin_b, int mpn)
{
	static int n_mpn = 0;
	map_a mpa;
	delete_map(mpa);

	//1
	if (mpn <= 0 || mpn > mpj.map_num)
	{
		no_good(mpa.error, checkpoint_ERROR);
		return mpa;
	}
	else if (mpn == 1)
	{
		fin_b.seekg(0, ios::beg);
		if (!jump_line(fin_b, mpa, 3))
			return mpa;
	}
	else if (mpj.map_num != mpn)
	{
		if (!next_map(fin_b, mpa))
			return mpa;
	}
	else
	{
		fin_b.clear();
		jump_map(mpj, mpj.map_num - 1, fin_b);
	}

	//2
	n_mpn = mpn;

	//3
	if (!read_checkpoint(fin_b, mpa, mpj, mpn))
		return mpa;

	//4
	if (!read_symbol(fin_b, mpa))
		return mpa;

	//5
	if (!read_size(fin_b, mpa))
		return mpa;

	//6
	if (!jump_line(fin_b, mpa, 2))
		return mpa;

	//7
	if (!new_map(mpa))
		return mpa;

	//8
	if (!read_map(fin_b, mpa))
		return mpa;
	

	return mpa;
}

#endif