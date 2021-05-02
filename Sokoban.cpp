#include "error.h"
#include "menu.h"
#include "game.h"
#include "read_map.h"
#include "make_map.h"

int main(void)
{
	ShowCursor(false);//隐藏光标

	map_a mpa;
	map_j mpj;
	fstream fin_a;

	if (!open_map(fin_a, mpa))
	{
		cerr << "地图打开失败！" << endl;
		if (!error(make_map()))
			cerr << "地图模板写入成功,重启后生效！" << endl << endl;
		else
		{
			sypose();
			return 1;
		}
		close_map_fin(fin_a);
		sypose();
		return 0;
	}

	cout << "地图读取中..." << endl;
	mpj = read_map_all(fin_a);
	//mpa = read_mapCp(mpj, fin_a, 1); || error(mpa.error)
	Sleep(500);
	
	if (error(mpj.error))//读取判断
	{
		close_map_fin(fin_a);
		sypose();
		return 1;
	}
	else
	{
		cout << "读取成功！" << endl;
		Sleep(510);
		system("cls");
	}
		


	//关卡选择
	int game_switch = '3';
	{
	ctu_s:
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
			goto end;
			break;
		default:
			system("cls");
			cerr << "menu_page error!\n";
			sypose();
			goto end;
			break;
		}
		switch (game_switch)
		{
		//case 0:
			//system("cls");
			//goto ctu_s;
			//break;
		case '1':
			system("cls");
			see_cursor_hide_show(false);
			{
				//进行游戏
				int gme = 0, gme_n = 1;
				mpa = read_mapCp(mpj, fin_a, gme_n);

				while (!error(mpa.error))
				{
					cout << "第" << mpa.checkpoint << "关";
					Sleep(1100);

					gme = game(mpa.map, mpa.mapx, mpa.mapy, mpa.map_f);

					if (gme == 1)
					{
						cout << endl << endl;
						sypose();
						system("cls");
						mpa = read_mapCp(mpj, fin_a, ++gme_n);
					}
					else if (gme == -1)
						goto game_i;
					else
						break;
				}
				cout << "游戏结束！" << endl << endl << flush;//换行并刷新缓冲区
			}
			break;
		case '2':
		gme_se:
			system("cls");
			{
				ShowCursor(true);//显示光标
				int mpn = map_jump_menu(mpj);
				ShowCursor(false);//隐藏光标
				if (mpn == -1)
					goto game_i;

				mpa = read_mapCp(mpj, fin_a, mpn);
				int gme = 0;
				if (!error(mpa.error))
				{
					system("cls");
					cout << "第" << mpa.checkpoint << "关";
					Sleep(1100);

					gme = game(mpa.map, mpa.mapx, mpa.mapy, mpa.map_f);

					if (gme == 1)
					{
						cout << endl << endl;
						sypose();
						system("cls");
						goto gme_se;
					}
						
					else if (gme == -1)
						goto gme_se;
					else
						break;
				}
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
			goto end;
			break;
		default:
			system("cls");
			cerr << "menu_game error!\n";
			sypose();
			goto end;
			break;
		}
	}

		
end:
	delete_map(mpa);
	close_map_fin(fin_a);
	sypose();//等待函数

	return 0;
}


