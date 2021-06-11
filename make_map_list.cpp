#include "make_map_list.h"
#include "linked_list.cpp"

using namespace std;

extern inline void Get_Time(char lctime[])//sizeof(lctime) >= 28
{	
	time_t t = _time64(NULL);
	tm* local = _localtime64(&t);
	sprintf(lctime, "%04d-%02d-%02d-%02d-%02d-%02d.Sokoban", 1900 + local->tm_year, 1 + local->tm_mon, local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec);
}

bool Make_Mapf_BinFile(map_a& mpa, fstream& fout, streamoff& MapfPos)
{
	MapfPos = fout.tellp();
	if (!fout.write((const char*)(&mpa.map_f), sizeof(mpa.map_f)).good())
	{
		no_good(mpa.error, Bmapf_WriteFalse, MakeMapfBF_F);
		return false;
	}

	return true;
}

bool Make_Map_BinFile(map_a& mpa, fstream& fout, streamoff& MapPos, streamoff& LMapPos, bool M, bool L)//M true MapPos   L true LMapPos
{
	if (M)
	{
		MapPos = fout.tellp();
		for (unsigned int i = 0; i < mpa.mapy; ++i)
		{
			for (unsigned int j = 0; j < mpa.mapx; ++j)
			{
				if (!fout.write((const char*)(&mpa.map[i][j]), sizeof(char)).good())
				{
					no_good(mpa.error, Bmap_WriteFalse, MakeMapBF_F, 1);
					return false;
				}
			}
		}
	}
	if (L)
	{
		LMapPos = fout.tellp();
		for (unsigned int i = 0; i < mpa.mapy; ++i)
		{
			for (unsigned int j = 0; j < mpa.mapx; ++j)
			{
				if (!fout.write((const char*)(&mpa.lmap[i][j]), sizeof(char)).good())
				{
					no_good(mpa.error, Bmap_WriteFalse, MakeMapBF_F, 2);
					return false;
				}
			}
		}
	}

	return true;
}

bool Make_Link_BinFile(map_a& mpa, fstream& fout, streamoff& RLinkPos, streamoff& FLinkPos, bool R, bool F)//R true RLinkPos   F true FLinkPos
{
	if (R)
	{
		RLinkPos = fout.tellp();
		{
			mpa.error = See_All_G(mpa.nodeR,
				[&](const int& list_x, const int& list_y, const int& list_n) -> bool
				{
					LinkData LinkD = { list_x,list_y,list_n };
					//cout << endl << list_x << list_y << list_n << endl;
					if (fout.write((const char*)(&LinkD), sizeof(LinkData)).good())
						return true;
					else
					{
						no_good(mpa.error, Blink_WriteFalse, MakeLinkBF_F, 1);
						return false;
					}
				});
			if (mpa.error.no_good)
				return false;
		}
	}
	if (F)
	{
		FLinkPos = fout.tellp();
		{
			mpa.error = See_All_G(mpa.nodeF,
				[&](const int& list_x, const int& list_y, const int& list_n) -> bool
				{
					LinkData LinkD = { list_x,list_y,list_n };
					//cout << endl << list_x << list_y << list_n << endl;
					if (fout.write((const char*)(&LinkD), sizeof(LinkData)).good())
						return true;
					else
					{
						no_good(mpa.error, Blink_WriteFalse, MakeLinkBF_F, 2);
						return false;
					}
				});
			if (mpa.error.no_good)
				return false;
		}
	}

	return true;
}



ERR Make_MLD(map_a& mpa, bool playback)//playback true回放false残局
{
	fstream fout;
	BinFileHead binhead;
#ifndef _DEBUG
	char FileName[28];
	
	Get_Time(FileName);
	fout.open(FileName, ios_base::out |ios_base::binary);
#else
	fout.open("binfile", ios_base::out |ios_base::binary);
#endif
	if (!fout.good())
	{
		no_good(mpa.error, open_failed, Make_MLD_F);
		return mpa.error;
	}
	
	//初始化文件头
	binhead.STRULL = MAPBIN;
	binhead.size = sizeof(BinFileHead);
	binhead.flags = FLAG(!playback, 1, (mpa.nodeR.hpQueue != NULL), (mpa.nodeF.hpQueue != NULL), 0, 0, 0, playback);
	binhead.mapX = mpa.mapx;
	binhead.mapY = mpa.mapy;
	binhead.nodeRN = mpa.nodeRnum;
	binhead.nodeFN = mpa.nodeFnum;

	//binhead.flags = playback ? FLAG(1, 0, 1, 0, 0, 0, 0, 1) : FLAG(1, 1, 1, (mpa.nodeF.hpQueue != NULL), 0, 0, 0, 0);
	//fout.seekp(ios_base::beg, sizeof(BinFileHead));

	
	fout.seekp(ios_base::beg, 0);
	if (!fout.write((const char*)(&binhead), sizeof(BinFileHead)).good())//写入未初始化的结构体进行占位
	{
		no_good(mpa.error, binhead_WriteFalse, Make_MLD_F, 1);
		return mpa.error;
	}
	if (!Make_Mapf_BinFile(mpa, fout, binhead.mapF))//写入地图符号
	{
		fout.close();
		return mpa.error;
	}
	if (!Make_Map_BinFile(mpa, fout, binhead.map, binhead.lmap, ISB(binhead.flags, 8), ISB(binhead.flags, 7)))//写入地图（新旧）
	{
		fout.close();
		return mpa.error;
	}
	if (!Make_Link_BinFile(mpa, fout, binhead.nodeR, binhead.nodeF, ISB(binhead.flags, 6), ISB(binhead.flags, 5)))//写入链表（撤回重做）
	{
		fout.close();
		return mpa.error;
	}
	fout.seekp(ios_base::beg, 0);
	if (!fout.write((const char*)(&binhead), sizeof(BinFileHead)).good())//写入初始化的结构体
	{
		no_good(mpa.error, binhead_WriteFalse, Make_MLD_F, 2);
		return mpa.error;
	}

	fout.close();
	return mpa.error;
}