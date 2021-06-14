#include "switch.h"

using namespace std;

int game_switch(map_j& mpj, fstream& fin_a)
{
ctu_s:
	int game_switch = '4';
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
	case '1'://正常模式
		system("cls");
		see_cursor_hide_show(false);
		{
			int mpn = 1;
			map_a mpa;

			mpa = read_mapCp(mpj, fin_a, mpn);
			while (!error(mpa.error))
			{
				system("cls");
				cout << "第" << mpa.checkpoint << "关";
				Sleep(1100);


				switch (game(mpa))
				{
				case ERROR:
					delete_map(mpa);
					goto br1;
					break;
				case LASTCHECK - 5:
					system("cls");
					delete_map(mpa);
					if (mpn > 1)
						mpa = read_mapCp(mpj, fin_a, --mpn);
					else
					{
						cout << "已经是第一关！" << endl << endl;
						sypose();
						mpa = read_mapCp(mpj, fin_a, mpn);
					}
					break;
				case NEXTCHECK - 5:
					system("cls");
					delete_map(mpa);
					if (mpn < mpj.map_num)
						mpa = read_mapCp(mpj, fin_a, ++mpn);
					else
					{
						cout << "已经是最后一关！" << endl << endl;
						sypose();
						mpa = read_mapCp(mpj, fin_a, mpn);
					}
					break;
				case SWITCH - 5:
					system("cls");
					delete_map(mpa);
					ShowCursor(true);//显示光标
					mpn = map_jump_menu(mpj);
					ShowCursor(false);//隐藏光标
					if (mpn == -1) goto game_i;
					mpa = read_mapCp(mpj, fin_a, mpn);
					break;
				case SAVE - 5:
					if (error(Make_MLD(mpa, false))) goto br1;
					delete_map(mpa);
					cout << endl << endl << "残局保存成功！" << endl;
					sypose();

					goto game_i;
					break;
				case QUIT - 5:
					delete_map(mpa);
					goto game_i;
					break;
				case END - 5:
					if (error(Make_MLD(mpa, true))) goto br1;
					delete_map(mpa);
					cout << endl << endl << "回放保存成功！" << endl;
					sypose();
					system("cls");

					if (mpn == mpj.map_num)
					{
						cout << "你已通过最后一关，游戏结束！" << endl;
						sypose();
						goto game_i;
					}
					else
						mpa = read_mapCp(mpj, fin_a, ++mpn);
					break;
				default:
					delete_map(mpa);
					goto br1;
					break;
				}
			}
		br1:
			cout << "游戏结束！" << endl << endl << flush;//换行并刷新缓冲区
		}
		break;
		
	case '2'://残局模式
		system("cls");
		{
			bool p;
			string str;
			map_a mpa;

			ShowCursor(true);//显示光标
			{
				cout << "请输入文件名(输入\\q或\\Q返回上层)：";
				getline(cin, str, '\n');
				if (str == "\\q" || str == "\\Q")
				{
					ShowCursor(false);//隐藏光标
					goto game_i;
				}
			}
			ShowCursor(false);//隐藏光标

			if(error((mpa = Read_MLD(str.c_str(), p)).error))
				goto br2;
			if (p)
			{
				cout << "不是残局文件！" << endl;
				delete_map(mpa);
				sypose();
				goto game_i;
			}

			system("cls");
			switch (game(mpa) - 3)
			{
			case SAVE - 5 - 3:
				if (error(Make_MLD(mpa, false))) goto br2;
				delete_map(mpa);
				cout << endl << endl << "残局保存成功！" << endl;
				sypose();
				goto game_i;
				break;
			case QUIT - 5 - 3:
				delete_map(mpa);
				goto game_i;
				break;
			case END - 5 - 3:
				if (error(Make_MLD(mpa, true))) goto br2;
				delete_map(mpa);
				cout << endl << endl << "回放保存成功！" << endl;
				sypose();
				break;
			default:
				delete_map(mpa);
				goto br2;
				break;
			}
			goto game_i;
		br2:
			cout << "游戏结束！" << endl << endl << flush;//换行并刷新缓冲区
		}
		break;
	case '3'://回放模式
		system("cls");
		{
			bool p;
			int iptn;
			string str;
			map_a mpa;

			ShowCursor(true);//显示光标
			{
				cout << "请输入文件名(输入\\q或\\Q返回上层)：";
				getline(cin, str, '\n');
				if (str == "\\q" || str == "\\Q")
				{
					ShowCursor(false);//隐藏光标
					goto game_i;
				}

				cout << "请输入操作间隔(输入-1返回上层)：";
				while (!(cin >> iptn))
				{
					cout << "请重新输入" << endl;
					cin.clear();
				}
				while (getchar() != '\n') continue;
				if (iptn == -1)
				{
					ShowCursor(false);//隐藏光标
					goto game_i;
				}
			}
			ShowCursor(false);//隐藏光标
			
				

			if (error((mpa = Read_MLD(str.c_str(), p)).error))
				goto br3;
			if (!p)
			{
				ShowCursor(true);
				if (!sure("播放残局文件"))
					break;
				ShowCursor(false);
			}

			system("cls");
			game_p(mpa, iptn, p);
			delete_map(mpa);

			sypose();
			system("cls");
			see_cursor_hide_show(false);
			goto game_i;

		br3:
			cout << "游戏结束！" << endl << endl << flush;//换行并刷新缓冲区
		}
		break;
	case '4'://返回上层
		system("cls");
		see_cursor_hide_show(false);
		goto ctu_s;
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