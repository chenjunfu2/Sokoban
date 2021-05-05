#pragma once

#ifndef _SWITCH
#define _SWITCH
#include <stdlib.h>
#include "menu.h"
#include "game.h"
#include "read_map.h"

using namespace std;

int game_switch(map_j& mpj, fstream& fin_a)
{
ctu_s:
	int game_switch = '3';
	switch (menu_page())
	{
	case '1':
	game_i:
		system("cls");
		see_cursor_hide_show(false);
		game_switch = menu_game();
		break;
	case '2':
		system("cls");
		see_cursor_hide_show(false);
		menu_explain();
		break;
	case '3':
		system("cls");
		see_cursor_hide_show(false);
		menu_about();
		break;
	case '4':
		system("cls");
		see_cursor_hide_show(false);
		//goto end;
		return 0;
		break;
	default:
		system("cls");
		cerr << "menu_page error!\n";
		sypose();
		//goto end;
		return -1;
		break;
	}


	switch (game_switch)
	{
	case '1':
		system("cls");
		see_cursor_hide_show(false);
		{
			int gme = 0, mpn = 1;

			 map_a mpa = read_mapCp(mpj, fin_a, mpn);
			while (!error(mpa.error))
			{
				system("cls");
				cout << "第" << mpa.checkpoint << "关";
				Sleep(1100);

				gme = game(mpa.map, mpa.mapx, mpa.mapy, mpa.map_f);
				delete_map(mpa);

				switch (gme)
				{
				case REGAME - 4:
					system("cls");
					mpa = read_mapCp(mpj, fin_a, mpn);
					break;
				case LASTCHECK - 4:
					system("cls");
					if (mpn > 1)
						mpa = read_mapCp(mpj, fin_a, --mpn);
					else
					{
						cout << "已经是第一关！" << endl << endl;
						sypose();
						mpa = read_mapCp(mpj, fin_a, mpn);
					}
					break;
				case NEXTCHECK - 4:
					system("cls");
					if (mpn < mpj.map_num)
						mpa = read_mapCp(mpj, fin_a, ++mpn);
					else
					{
						cout << "已经是最后一关！" << endl << endl;
						sypose();
						mpa = read_mapCp(mpj, fin_a, mpn);
					}
					break;
				case QUIT - 4:
					goto game_i;
					break;
				case END - 4:
					cout << endl << endl;
					sypose();
					system("cls");
					mpa = read_mapCp(mpj, fin_a, ++mpn);
					break;
				default:
					goto br1;
					break;
				}
			}
		br1:
			cout << "游戏结束！" << endl << endl << flush;//换行并刷新缓冲区
		}
		break;
	case '2':
	gme_se:
		system("cls");
		{
			ShowCursor(true);//显示光标
			int gme = 0, mpn = map_jump_menu(mpj);
			ShowCursor(false);//隐藏光标
			if (mpn == -1) goto game_i;

			map_a mpa = read_mapCp(mpj, fin_a, mpn);
			while (!error(mpa.error))
			{
				system("cls");
				cout << "第" << mpa.checkpoint << "关";
				Sleep(1100);

				gme = game(mpa.map, mpa.mapx, mpa.mapy, mpa.map_f);
				delete_map(mpa);


				switch (gme)
				{
				case REGAME - 4:
					system("cls");
					mpa = read_mapCp(mpj, fin_a, mpn);
					break;
				case LASTCHECK - 4:
					system("cls");
					if (mpn > 1)
						mpa = read_mapCp(mpj, fin_a, --mpn);
					else
					{
						cout << "已经是第一关！" << endl << endl;
						sypose();
						mpa = read_mapCp(mpj, fin_a, mpn);
					}
					break;
				case NEXTCHECK - 4:
					system("cls");
					if (mpn < mpj.map_num)
						mpa = read_mapCp(mpj, fin_a, ++mpn);
					else
					{
						cout << "已经是最后一关！" << endl << endl;
						sypose();
						mpa = read_mapCp(mpj, fin_a, mpn);
					}
					break;
				case QUIT - 4:
					goto gme_se;
					break;
				case END - 4:
					cout << endl << endl;
					sypose();
					system("cls");
					goto gme_se;
					break;
				default:
					goto br2;
					break;
				}
			}
		br2:
			cout << "游戏结束！" << endl << endl << flush;//换行并刷新缓冲区
		}
		break;
	case '3':
		system("cls");
		see_cursor_hide_show(false);
		goto ctu_s;
		break;
	case '4':
		system("cls");
		see_cursor_hide_show(false);
		//goto end;
		return 0;
		break;
	default:
		system("cls");
		cerr << "menu_game error!\n";
		sypose();
		//goto end;
		return -1;
		break;
	}

	return 0;
}

#endif