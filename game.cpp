#include "game.h"

using namespace std;


//获取人坐标
extern inline PEO find_peo(unsigned int** map, int mx, int my)
{
	PEO peo;
	int pen = 0;
	for (int i = 0; i < my; ++i)
	{
		for (int j = 0; j < mx; ++j)
		{
			if (map[i][j] == 2 || map[i][j] == 6)
			{
				peo.x = j;
				peo.y = i;
				++pen;
			}
		}
	}

	if (pen == 0)
		no_good(peo.error, map_PeopleNull, find_peo_F);
	else if (pen > 1)
		no_good(peo.error, map_PeopleOverFlow, find_peo_F);
	//pen == 1
	return peo;
}

//移动人
extern inline void move_p(const peo& pe, unsigned int** map)
{
	if (map[pe.y][pe.x] == 6)
		map[pe.y][pe.x] = 4;
	else
		map[pe.y][pe.x] = 0;

	return;
}

//反向移动人
extern inline void reverse_move_p(const peo& pe, unsigned int** map, int list_x, int list_y)
{
	if (map[pe.y + list_y][pe.x + list_x] == 4)
		map[pe.y + list_y][pe.x + list_x] = 6;
	else
		map[pe.y + list_y][pe.x + list_x] = 2;
}



//全局移动（用户操作）
bool move_user(unsigned int** map, int mx, int my, int x, int y, peo& pe, NODE& nodeR, NODE& nodeF)
{
	bool mov = false;

	if (pe.x + x < 0 || pe.x + x >= mx || pe.y + y < 0 || pe.y + y >= my)//越界判断
		return mov;
	{
		if (map[pe.y + y][pe.x + x] == 0)//人前面是空地
		{
			map[pe.y + y][pe.x + x] = 2;
			move_p(pe, map);
			mov = true;//移动标记
			Add_CpQueue(nodeR, x, y, 0);
		}
		else if (map[pe.y + y][pe.x + x] == 4)//人前面是目的地
		{
			map[pe.y + y][pe.x + x] = 6;
			move_p(pe, map);
			mov = true;//移动标记
			Add_CpQueue(nodeR, x, y, 1);
		}
	}
	if (mov == true)
	{
		pe.x += x;
		pe.y += y;
		return mov;
	}


	if (pe.x + (x * 2) < 0 || pe.x + (x * 2) >= mx || pe.y + (y * 2) < 0 || pe.y + (y * 2) >= my)//越界判断
		return mov;
	{
		if (map[pe.y + y][pe.x + x] == 3)//人前面是箱子
		{
			if (map[pe.y + (y * 2)][pe.x + (x * 2)] == 0)//箱子前面是空地
			{
				map[pe.y + (y * 2)][pe.x + (x * 2)] = 3;
				map[pe.y + y][pe.x + x] = 2;
				move_p(pe, map);
				mov = true;//移动标记
				Add_CpQueue(nodeR, x, y, 2);
			}
			else if (map[pe.y + (y * 2)][pe.x + (x * 2)] == 4)//箱子前面是目的地
			{
				map[pe.y + (y * 2)][pe.x + (x * 2)] = 5;
				map[pe.y + y][pe.x + x] = 2;
				move_p(pe, map);
				mov = true;//移动标记
				Add_CpQueue(nodeR, x, y, 3);
			}
		}
		else if (map[pe.y + y][pe.x + x] == 5)//人的前面是箱子
		{
			if (map[pe.y + (y * 2)][pe.x + (x * 2)] == 0)//箱子在目的地
			{
				map[pe.y + (y * 2)][pe.x + (x * 2)] = 3;
				map[pe.y + y][pe.x + x] = 6;
				move_p(pe, map);
				mov = true;//移动标记
				Add_CpQueue(nodeR, x, y, 4);
			}
			else if (map[pe.y + (y * 2)][pe.x + (x * 2)] == 4)//箱子在目的地的前面是目的地
			{
				map[pe.y + (y * 2)][pe.x + (x * 2)] = 5;
				map[pe.y + y][pe.x + x] = 6;
				move_p(pe, map);
				mov = true;//移动标记
				Add_CpQueue(nodeR, x, y, 5);
			}
		}
	}
	if (mov == true)
	{
		pe.x += x;
		pe.y += y;
		return mov;
	}

	return mov;
}

//全局移动（重做）
bool move_f(unsigned int** map, int mx, int my, peo& pe, NODE& nodeR, NODE& nodeF)
{
	int list_x, list_y, list_n;
	if (See_CpQueue(nodeF, list_x, list_y, list_n).no_good)
		return false;
	Move_CpQueue_To_CpQueue(nodeR, nodeF);

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

//反向全局移动（撤销）
bool move_r(unsigned int** map, int mx, int my, peo& pe, NODE& nodeR, NODE& nodeF)//reserve_move_a
{
	int list_x, list_y, list_n;
	if (See_CpQueue(nodeR, list_x, list_y, list_n).no_good)
		return false;
	Move_CpQueue_To_CpQueue(nodeF, nodeR);


	reverse_num(list_x, list_y);

	switch (list_n)
	{
	case 0:
	case 1:
		if (map[pe.y + list_y][pe.x + list_x] == 0)
		{
			move_p(pe, map);
			map[pe.y + list_y][pe.x + list_x] = 2;
		}
		else if (map[pe.y + list_y][pe.x + list_x] == 4)
		{
			move_p(pe, map);
			map[pe.y + list_y][pe.x + list_x] = 6;
		}
		break;
	case 2:
		reverse_move_p(pe, map, list_x, list_y);
		map[pe.y - list_y][pe.x - list_x] = 0;
		map[pe.y][pe.x] = 3;
		break;
	case 3:
		reverse_move_p(pe, map, list_x, list_y);
		map[pe.y - list_y][pe.x - list_x] = 4;
		map[pe.y][pe.x] = 3;
		break;
	case 4:
		reverse_move_p(pe, map, list_x, list_y);
		map[pe.y - list_y][pe.x - list_x] = 0;
		map[pe.y][pe.x] = 5;
		break;
	case 5:
		reverse_move_p(pe, map, list_x, list_y);
		map[pe.y - list_y][pe.x - list_x] = 4;
		map[pe.y][pe.x] = 5;
		break;
	default:
		return false;
		break;
	}

	pe.x += list_x;
	pe.y += list_y;
	return true;
}



//绘制地图
template <typename T>
extern inline ERR init_map(unsigned int** map, int mx, int my, const T map_f)
{
	ERR error;

	move_g(0, 0);//清屏
	for (int i = 0; i < my; ++i)
	{
		for (int j = 0; j < mx; ++j)
		{
			if (map[i][j] >= 0 && map[i][j] <= 6)
				cout << map_f[map[i][j]];
			//cout << map[i][j];
			else
			{
				system("cls");
				no_good(error, map_Default, init_map_F);
				return error;
			}
		}
		cout << endl;
	}
	return error;
}

//绘制人附近方块
template <typename T>
ERR init_peo(unsigned int** map, int mx, int my, const T map_f, const peo& pe)//, const NODE& nodeR, const NODE& nodeF
{
	ERR error;
	//COORD OldCur = get_g();
	//int list_xR, list_yR, list_nR;
	//int list_xF, list_yF, list_nF;

	//if ((Find_CpQueue(nodeR, list_xR, list_yR, list_nR).no_good)&&(Find_CpQueue(nodeF, list_xF, list_yF, list_nF).no_good))
		//return error;


	//竖画
	for (int i = pe.y - 2, j = pe.x; i < pe.y + 3; ++i)
	{
		if (i < 0 || i >= my) continue;
		if (map[i][j] >= 0 && map[i][j] <= 6)
		{
			move_g(j * 2, i);
			cout << map_f[map[i][j]];
			//cout << map[i][j];
		}
		else
		{
			system("cls");
			no_good(error, map_Default, init_peo_F);
			return error;
		}
	}

	//横画
	for (int i = pe.y, j = pe.x - 2; j < pe.x + 3; ++j)
	{
		if (j < 0 || j >= mx) continue;
		if (map[i][j] >= 0 && map[i][j] <= 6)
		{
			move_g(j * 2, i);
			cout << map_f[map[i][j]];
			//cout << map[i][j];
		}
		else
		{
			system("cls");
			no_good(error, map_Default, init_peo_F);
			return error;
		}
	}

	//move_g(OldCur.X, OldCur.Y);
	move_g(0, my);
	return error;
}



//前后左右反转
extern inline void reverse_num(int& list_x, int& list_y)
{
	list_x = -list_x;
	list_y = -list_y;
}

//是否赢
extern inline bool win_g(unsigned int** map, int mx, int my)
{
	for (int i = 0; i < my; ++i)
	{
		for (int j = 0; j < mx; ++j)
		{
			if (map[i][j] == 3)
			{
				return false;
			}
		}
	}
	return true;
}

//获取键盘输入
int get_keyb(unsigned int** map, int mx, int my, peo& pe, NODE& nodeR, NODE& nodeF)
{
	//int ch, mov;
	int mov = NODO;

start1:
	//{
		//ch = tolower(_getch());
		//if (ch != 'w' && ch != 'a' && ch != 's' && ch != 'd' && ch != 'q' && ch != 'r')
			//ch = _getch();
	//}

	switch (_getch())
	{
	case 72://up
	case 'w':
	case 'W':
		if ((mov = move_user(map, mx, my, 0, -1, pe, nodeR, nodeF)) == false)goto start1;
		break;
	case 75://left
	case 'a':
	case 'A':
		if ((mov = move_user(map, mx, my, -1, 0, pe, nodeR, nodeF)) == false)goto start1;
		break;
	case 77://right
	case 'd':
	case 'D':
		if ((mov = move_user(map, mx, my, +1, 0, pe, nodeR, nodeF)) == false)goto start1;
		break;
	case 80://down
	case 's':
	case 'S':
		if ((mov = move_user(map, mx, my, 0, +1, pe, nodeR, nodeF)) == false)goto start1;
		break;
	case 'r'://revoke
	case 'R':
		mov = REVOKE;
		if (!move_r(map, mx, my, pe, nodeR, nodeF))
			goto start1;
		break;
	case 'f'://redo
	case 'F':
		mov = REDO;
		if (!move_f(map, mx, my, pe, nodeR, nodeF))
			goto start1;
		break;
	case 'e'://regame
	case 'E':
		ShowCursor(true);
		if (sure("重玩"))
		{
			mov = REGAME;
		}
		else
			mov = NODO;
		ShowCursor(false);
		break;
	case 'c':
	case 'C':
		ShowCursor(true);
		if (sure("进入选关"))
		{
			mov = SWITCH;
		}
		else
			mov = NODO;
		ShowCursor(false);
		break;
	case 'z'://last checkpoint
	case 'Z':
		ShowCursor(true);
		if (sure("上一关"))
		{
			mov = LASTCHECK;
		}
		else
			mov = NODO;
		ShowCursor(false);
		break;
	case 'x'://next checkpoint
	case 'X':
		ShowCursor(true);
		if (sure("下一关"))
		{
			mov = NEXTCHECK;
		}
		else
			mov = NODO;
		ShowCursor(false);
		break;
	case 'v':
	case 'V':
		ShowCursor(true);
		if (sure("保存残局"))
		{
			mov = SAVE;
		}
		else
			mov = NODO;
		ShowCursor(false);
		break;
	case 'q'://quit
	case 'Q':
		ShowCursor(true);
		if (sure("退出"))
		{
			mov = QUIT;
		}
		else
			mov = NODO;
		ShowCursor(false);
		break;
	default:
		goto start1;
		break;
	}

	return mov;
}

//进行游戏
int game(map_a& mpa)
{
	peo pe = find_peo(mpa.map, mpa.mapx, mpa.mapy);
	if (error(pe.error))
		return ERROR;
	int keyb = 0;
	//NODE nodeR, nodeF;

	if (error(init_map(mpa.map, mpa.mapx, mpa.mapy, mpa.map_f)))//绘制全地图
		return ERROR;
	cout << "第" << mpa.nodeRnum << "步" << "  ";

	while (true)
	{
		if (win_g(mpa.map, mpa.mapx, mpa.mapy))//win game判断
		{
			cout << endl << "You Win!";
			break;
		}

	con1:
		switch (keyb = get_keyb(mpa.map, mpa.mapx, mpa.mapy, pe, mpa.nodeR, mpa.nodeF))//得到键盘输入并进行游戏
		{
		case REDO:
			++mpa.nodeRnum;//撤销链表节点数递增
			--mpa.nodeFnum;//重做链表节点数递减
			break;
		case MOVE:
			++mpa.nodeRnum;//撤销链表节点数递增
			if (mpa.nodeF.hpQueue != NULL)
			{
				Del_AllQueue(mpa.nodeF);
				mpa.nodeFnum = 0;//重做链表节点数置零
			}
			break;
		case REVOKE:
			--mpa.nodeRnum;//撤销链表节点数递减
			++mpa.nodeFnum;//重做链表节点数递增
			break;
		case NODO:
			system("cls");
			init_map(mpa.map, mpa.mapx, mpa.mapy, mpa.map_f);//如果不操作则重绘全部地图
			cout << "第" << mpa.nodeRnum << "步" << "  ";
			goto con1;
			break;
		case REGAME:
			system("cls");
			cout << "第" << mpa.checkpoint << "关";
			Sleep(1100);
			copy_lmapTOmap(mpa);
			init_map_data(mpa);
			pe = find_peo(mpa.map, mpa.mapx, mpa.mapy);
			if (error(pe.error)) return ERROR;
			if (error(init_map(mpa.map, mpa.mapx, mpa.mapy, mpa.map_f))) return ERROR;
			cout << "第" << mpa.nodeRnum << "步" << "  ";
			goto con1;
		default:
			return keyb - 5;//56789->012345
			break;
		}

		see_cursor_hide_show(false);

		if (error(init_peo(mpa.map, mpa.mapx, mpa.mapy, mpa.map_f, pe)))//绘制更新后的地图
		{
			return ERROR;//-1
		}
		cout << "第" << mpa.nodeRnum << "步" << "  ";
	}

	return END - 5;//8->3
}


