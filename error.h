#pragma once

#ifndef _ERROR
#define _ERROR
#include <iostream>
using namespace std;

//ERROR_NUM_ALL
#define GOOD_ERR				0
#define delete_failed			-120
#define new_failed				-119
#define open_failed				-118
#define fst_eof					-117
#define map_PeopleNull			-116

//read_map
#define line_JumpFalse			-10
#define map_JumpFalse			-9
#define list_ReadFalse			-8
#define checkpoint_ReadFalse	-7
#define checkpoint_ERROR		-6
#define sizeX_ReadFalse			-5
#define sizeY_ReadFalse			-4
#define mapX_NewFalse			-3
#define mapY_NewFalse			-2
#define map_ReadFalse			-1


//linked_list
#define cpQueue_Null			-20

//make_map
#define description_WriteFalse	-19
#define checkpoint_WriteFalse	-18

//game
#define map_Default				-17



typedef struct err {
	bool no_good = false;
	int err_num = 0;
}ERR;


//错误
static inline void no_good(ERR& error, int error_num)
{
	error.no_good = true;
	error.err_num = error_num;
}
//撤销错误
static inline void are_good(ERR& error)
{
	error.no_good = false;
	error.err_num = GOOD_ERR;
}


bool error(ERR error)
{

	if (error.no_good == false && error.err_num == GOOD_ERR)
	{
		//cerr << "没有错误或自相矛盾";
		return error.no_good;
	}

	cerr << "error:";

	switch (error.err_num)
	{
	case GOOD_ERR:
		break;
	case delete_failed:
		cerr << "内存释放失败！" << endl << endl;
		break;
	case new_failed:
		cerr << "内存分配失败！" << endl << endl;
		break;
	case open_failed:
		cerr << "文件打开失败！" << endl << endl;
		break;
	case fst_eof:
		cerr << "意外遇到文件尾！" << endl << endl;
		break;
	case line_JumpFalse:
		cerr << "跳过行失败！" << endl << endl;
		break;
	case map_JumpFalse:
		cerr << "地图跳转失败！" << endl << endl;
		break;
	case checkpoint_ReadFalse:
		cerr << "关卡号读取失败！" << endl << endl;
		break;
	case checkpoint_ERROR:
		cerr << "关卡号超出范围！" << endl << endl;
		break;
	case list_ReadFalse:
		cerr << "地图符号读取错误！" << endl << endl;
		break;
	case sizeX_ReadFalse:
		cerr << "地图X大小读取错误！" << endl << endl;
		break;
	case sizeY_ReadFalse:
		cerr << "地图X大小读取错误！" << endl << endl;
		break;
	case mapX_NewFalse:
		cerr << "地图X内存分配错误！" << endl << endl;
		break;
	case mapY_NewFalse:
		cerr << "地图Y内存分配错误！" << endl << endl;
		break;
	case map_ReadFalse:
		cerr << "地图读取错误！" << endl << endl;
		break;
	case map_PeopleNull:
		cerr << "地图中不含有人！" << endl << endl;
		break;
	case cpQueue_Null:
		cerr << "链表尾指针为空！" << endl << endl;
		break;
	case description_WriteFalse:
		cerr << "地图说明写入错误！" << endl << endl;
		break;
	case checkpoint_WriteFalse:
		cerr << "关卡写入错误！" << endl << endl;
		break;
	case map_Default:
		cerr << "地图标记错误！" << endl << endl;
		break;
	default:
		cerr << "未知错误！";
		break;
	}

	return error.no_good;
}


#endif