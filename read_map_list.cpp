#include "read_map_list.h"
#include "linked_list.cpp"

using namespace std;

bool Read_Mapf_BinFile(map_a& mpa, fstream& fin, streamoff& MapfPos)
{
	if (!fin.seekg(MapfPos).good())
	{
		no_good(mpa.error, Bmapf_SeekFalse, ReadMapfBF_F);
		return false;
	}

	if (!fin.read((char*)(&mpa.map_f), sizeof(mpa.map_f)).good())
	{
		no_good(mpa.error, Bmapf_ReadFalse, ReadMapfBF_F);
		return false;
	}

	return true;
}

bool Read_Map_BinFile(map_a& mpa, fstream& fin, streamoff& MapPos, streamoff& LMapPos, bool M, bool L)
{
	if (M)
	{
		if (!fin.seekg(MapPos).good())
		{
			no_good(mpa.error, Bmap_SeekFalse, ReadMapBF_F, 1);
			return false;
		}
		unsigned char c;
		for (unsigned int i = 0; i < mpa.mapy; ++i)
		{
			for (unsigned int j = 0; j < mpa.mapx; ++j)
			{
				if (!fin.read((char*)(&c), sizeof(char)).good())
				{
					no_good(mpa.error, Bmap_ReadFalse, ReadMapBF_F, 1);
					return false;
				}
				mpa.map[i][j] = c;
			}
		}
	}
	if (L)
	{
		if (!fin.seekg(LMapPos).good())
		{
			no_good(mpa.error, Bmap_SeekFalse, ReadMapBF_F, 2);
			return false;
		}
		unsigned char c;
		for (unsigned int i = 0; i < mpa.mapy; ++i)
		{
			for (unsigned int j = 0; j < mpa.mapx; ++j)
			{
				if (!fin.read((char*)(&c), sizeof(char)).good())
				{
					no_good(mpa.error, Bmap_ReadFalse, ReadMapBF_F, 2);
					return false;
				}
				mpa.lmap[i][j] = c;
			}
		}
	}

	return true;
}

bool Read_Link_BinFile(map_a& mpa, fstream& fin, streamoff& RLinkPos, streamoff& FLinkPos, bool R, bool F)
{
	unsigned int i = 0;
	if (R)
	{
		if (!fin.seekg(RLinkPos).good())
		{
			no_good(mpa.error, Blink_SeekFalse, ReadLinkBF_F, 1);
			return false;
		}
		{
			mpa.error = Add_All_B(mpa.nodeR,
				[&fin, &mpa, &i](int& list_x, int& list_y, int& list_n) -> bool
				{
					LinkData LinkD;
					if (i < mpa.nodeRnum)
					{
						if (fin.read((char*)(&LinkD), sizeof(LinkData)).good())
						{
							++i;
							list_x = LinkD.list_x;
							list_y = LinkD.list_y;
							list_n = LinkD.list_n;
							return true;
						}
						else
						{
							no_good(mpa.error, Blink_ReadFalse, ReadLinkBF_F, 1);
							return false;
						}
					}
					else
						return false;
				});
			if (mpa.error.no_good)
				return false;
		}
	}

	i = 0;
	if (F)
	{
		if (!fin.seekg(FLinkPos).good())
		{
			no_good(mpa.error, Blink_SeekFalse, ReadLinkBF_F, 2);
			return false;
		}
		{
			mpa.error = Add_All_B(mpa.nodeF,
				[&fin, &mpa, &i](int& list_x, int& list_y, int& list_n) -> bool
				{
					LinkData LinkD;
					if (i < mpa.nodeFnum)
					{
						if (fin.read((char*)(&LinkD), sizeof(LinkData)).good())
						{
							++i;
							list_x = LinkD.list_x;
							list_y = LinkD.list_y;
							list_n = LinkD.list_n;
							return true;
						}
						else
						{
							no_good(mpa.error, Blink_ReadFalse, ReadLinkBF_F, 2);
							return false;
						}
					}
					else
						return false;
				});
			if (mpa.error.no_good)
				return false;
		}
	}

	return true;
}



map_a Read_MLD(const char* FileName, bool& playback)
{
	fstream fin;
	map_a mpa;
	BinFileHead binhead = { 0 };

#ifdef _DEBUG
	fin.open("binfile", ios_base::in | ios_base::binary);
#else
	fin.open(FileName, ios_base::in | ios_base::binary);
#endif
	if (!fin.good())
	{
		no_good(mpa.error, open_failed, Read_MLD_F);
		return mpa;
	}

	fin.seekg(ios_base::beg, 0);
	if (!fin.read((char*)&binhead, sizeof(BinFileHead)).good())
	{
		no_good(mpa.error, binhead_ReadFalse, Read_MLD_F);
		return mpa;
	}

	if (binhead.STRULL != MAPBIN)
	{
		no_good(mpa.error, bhStrFalse, Read_MLD_F);
		return mpa;
	}
	if (binhead.size != sizeof(BinFileHead))
	{
		no_good(mpa.error, bhSizeFalse, Read_MLD_F);
		return mpa;
	}

	mpa.mapx = binhead.mapX;
	mpa.mapy = binhead.mapY;
	mpa.nodeRnum = binhead.nodeRN;
	mpa.nodeFnum = binhead.nodeFN;
	playback = ISB(binhead.flags, 1);
	new_map(mpa);

	if (!Read_Mapf_BinFile(mpa, fin, binhead.mapF))
	{
		fin.close();
		return mpa;
	}
	if (!Read_Map_BinFile(mpa, fin, binhead.map, binhead.lmap, ISB(binhead.flags, 8), ISB(binhead.flags, 7)))
	{
		fin.close();
		return mpa;
	}
	if (!Read_Link_BinFile(mpa, fin, binhead.nodeR, binhead.nodeF, ISB(binhead.flags, 6), ISB(binhead.flags, 5)))
	{
		fin.close();
		return mpa;
	}

	if (!ISB(binhead.flags, 8) && ISB(binhead.flags, 7))
		copy_lmapTOmap(mpa);

	fin.close();
	return mpa;
}