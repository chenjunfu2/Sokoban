#include "play.h"

using namespace std;

int game_p(map_a& mpa, DWORD msec, bool playback)
{
	if (!playback)
		copy_lmapTOmap(mpa);
	peo pe = find_peo(mpa.map, mpa.mapx, mpa.mapy);
	if (error(pe.error))
		return ERROR;

	unsigned int nodenum = 0;
	//NODE nodeR = mpa.nodeF, nodeF = mpa.nodeR;
	

	if (error(init_map(mpa.map, mpa.mapx, mpa.mapy, mpa.map_f)))//绘制全地图
		return ERROR;
	cout << "第" << nodenum << "步" << "  ";

	while (nodenum < mpa.nodeRnum)
	{
		Sleep(msec);
		move_p_f(mpa.map, mpa.mapx, mpa.mapy, pe, mpa.nodeR, mpa.nodeF);
		++nodenum;

		see_cursor_hide_show(false);

		if (error(init_peo(mpa.map, mpa.mapx, mpa.mapy, mpa.map_f, pe)))//绘制更新后的地图
		{
			return ERROR;
		}
		cout << "第" << nodenum << "步" << "  ";
	}

	cout << endl << "The End!" << endl << endl;

	return END - 5;//8->3
}

bool move_p_f(unsigned int** map, int mx, int my, peo& pe, NODE& nodeR, NODE& nodeF)
{
	int list_x, list_y, list_n;
	if (See_HpQueue(nodeR, list_x, list_y, list_n).no_good)
		return false;
	Move_HpQueue_To_HpQueue(nodeF, nodeR);

	switch (list_n)
	{
	case 0:
		map[pe.y + list_y][pe.x + list_x] = 2;
		move_p(pe, map);
		break;
	case 1:
		map[pe.y + list_y][pe.x + list_x] = 6;
		move_p(pe, map);
		break;
	case 2:
		map[pe.y + (list_y * 2)][pe.x + (list_x * 2)] = 3;
		map[pe.y + list_y][pe.x + list_x] = 2;
		move_p(pe, map);
		break;
	case 3:
		map[pe.y + (list_y * 2)][pe.x + (list_x * 2)] = 5;
		map[pe.y + list_y][pe.x + list_x] = 2;
		move_p(pe, map);
		break;
	case 4:
		map[pe.y + (list_y * 2)][pe.x + (list_x * 2)] = 3;
		map[pe.y + list_y][pe.x + list_x] = 6;
		move_p(pe, map);
		break;
	case 5:
		map[pe.y + (list_y * 2)][pe.x + (list_x * 2)] = 5;
		map[pe.y + list_y][pe.x + list_x] = 6;
		move_p(pe, map);
		break;
	default:
		return false;
		break;
	}

	pe.x += list_x;
	pe.y += list_y;
	return true;
}