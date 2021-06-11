#pragma once

#ifndef _error
#define _error

#include <stdio.h>

//ERROR_NUM_ALL		0 ~ 10
#define GOOD_ERR				0x0000
#define delete_failed			0x0001
#define new_failed				0x0002
#define open_failed				0x0003
#define fst_eof					0x0004
#define map_PeopleNull			0x0005
#define map_PeopleOverFlow		0x0006

//read_map		11 ~ 20
#define line_JumpFalse			0x000B
#define map_JumpFalse			0x000C
#define list_ReadFalse			0x000D
#define checkpoint_ReadFalse	0x000E
#define checkpoint_ERROR		0x000F
#define sizeX_ReadFalse			0x0010
#define sizeY_ReadFalse			0x0011
#define mapX_NewFalse			0x0012
#define mapY_NewFalse			0x0013
#define map_ReadFalse			0x0014

//linked_list	21 ~ 30
#define cpQueue_Null			0x0015
#define hpQueue_Null			0x0016
#define cpQueue_Have			0x0017
#define hpQueue_Have			0x0018

//make_map		31 ~ 40
#define description_WriteFalse	0x001F
#define checkpoint_WriteFalse	0x0020

//game			41 ~ 50
#define map_Default				0x0029

//make_map_list	51 ~ 60
#define binhead_WriteFalse		0x0033
#define Bmapf_WriteFalse		0x0034
#define Bmap_WriteFalse			0x0035
#define Blink_WriteFalse		0x0036

//read_map_list 61 ~ 70
#define binhead_ReadFalse		0x0037
#define bhStrFalse				0x0038
#define bhSizeFalse				0x0039
#define Bmapf_SeekFalse			0x0040
#define Bmapf_ReadFalse			0x0041
#define Bmap_SeekFalse			0x0042
#define Bmap_ReadFalse			0x0043
#define Blink_SeekFalse			0x0044
#define Blink_ReadFalse			0x0045



//FUNTION		101 ~ 136	(0x0065 ~ 0x0088)
#define init_map_F				0x0065
#define init_peo_F				0x0066
#define find_peo_F				0x0067

#define Add_CpQueue_F			0x0068
#define Add_HpQueue_F			0x0069
#define Del_CpQueue_F			0x006A
#define Del_AllQueue_F			0x006B
#define Find_CpQueue_F			0x006C
#define Find_HpQueue_F			0x006D
#define See_All_F				0x006E
#define Add_All_F				0x006F
#define Move_CpQ_To_CpQ_F		0x0070
#define Move_HpQ_To_HpQ_F		0x0071
								
#define make_map_F				0x0072
								
#define open_map_F				0x0073
#define delete_map_F			0x0074
#define jump_map_F				0x0075
#define jump_line_F				0x0076
#define next_map_F				0x0077
#define read_checkpoint_F		0x0078
#define read_symbol_F			0x0079
#define read_size_F				0x007A
#define new_map_F				0x007B
#define read_map_F				0x007C
#define read_map_all_F			0x007D
#define read_mapCp_F			0x007E
								
#define fSee_P_F				0x007F
#define fAdd_P_F				0x0080

#define MakeMapfBF_F			0x0081
#define MakeMapBF_F				0x0082
#define MakeLinkBF_F			0x0083
#define Make_MLD_F				0x0084

#define ReadMapfBF_F			0x0085
#define ReadMapBF_F				0x0086
#define ReadLinkBF_F			0x0087
#define Read_MLD_F				0x0088

static const char* reason[] =
{
	//0
	"没有错误（自相矛盾）",

	//1 ~ 10
	"内存释放失败",
	"内存分配失败",
	"文件打开失败",
	"意外遇到文件尾",
	"地图中不含有人",
	"地图中人数过多",
	"",
	"",
	"",
	"",

	//11 ~ 20
	"跳过行失败",
	"地图跳转失败",
	"地图符号读取失败",
	"关卡号读取失败",
	"关卡号超出范围或不正确",
	"地图X大小读取失败",
	"地图Y大小读取失败",
	"地图X内存分配失败",
	"地图Y内存分配失败",
	"地图读取失败",
	
	//21 ~ 30
	"链表尾指针为空",
	"链表头指针为空",
	"链表尾指针含有内容",
	"链表头指针含有内容",
	"",
	"",
	"",
	"",
	"",
	"",

	//31 ~ 40
	"地图说明写入失败",
	"关卡写入失败",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",

	//41 ~ 50
	"地图标记错误",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",

	//51 ~ 60
	"二进制文件头写入失败",
	"二进制地图符号写入失败",
	"二进制地图写入失败",
	"二进制链表写入失败",
	"",
	"",
	"",
	"",
	"",
	"",

	//61 ~ 70
	"二进制文件头读取失败",
	"二进制文件头校验信息不符",
	"二进制文件头大小不符",
	"二进制地图符号定位失败",
	"二进制地图符号读取失败",
	"二进制地图定位失败",
	"二进制地图读取失败",
	"二进制链表定位失败",
	"二进制链表读取失败",
	"",
};

typedef struct err {
	bool no_good = false;
	unsigned err_num = GOOD_ERR;//错误码
	unsigned err_fun = 0x0000;//报错函数
	unsigned err_msg = 000000;//附加的报错信息
}ERR;


//错误
extern inline void no_good(ERR& error, unsigned err_num, unsigned err_fun, unsigned err_msg = 0);
//撤销错误
extern inline void are_good(ERR& error);
//报错函数
extern inline bool error(ERR error);

#endif