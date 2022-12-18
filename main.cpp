#include<iostream>
#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<easyx.h>
//#define SNAKE 6
#pragma warning(disable : 4996)
using namespace std;

int SNAKE = 12;
int x = 50, y = 50, f_sh_max;//x:行数;y:列数;f_sh_max:最高分
long long money = 0;//money:金币
float speed = 0.1;//speed:速度
int y_j[505][505] = { 0 }, len[2] = { 3 }, f_x, f_y;//y_j:the map;len:玩家长度;f_x,f_y:查询坐标
short fx[2] = { 4 }, w_j_num;//fx:方向;w_j_num:玩家数量;;fx:up,down,left,right
bool jl = 0, len_j[2] = { 0 }, die, com = 1;//jl:奖励;len_j:长度加;die死亡;com:电脑
char m_m[100] = "         ", m_m_nc[100] = "pstd12354";//m_m:输入的密码;m_m_nc:内测密码
int j_m = 321;//j_m:加密
int num_huihe, cd[2] = { 0 }, jn_xz[2] = { 0 }, set_cd[2] = { 50,100 };//num_huihe:回合数;cd:玩家技能剩余cd;jn_xz:玩家选择的技能
bool use_jineng = 1;
FILE* fin, * fout;

int out_csh = 1, _csh_ = 0, w_b = 1, zh_ai = 1, m_m_c_sh = 1,dnjn = 1;
bool _zt;//暂停


int dif[2] = { 1,1 };

bool find(int l);


void _bar(int midx, int midy) {
	solidrectangle(midy - SNAKE / 3, midx - SNAKE / 3, midy + SNAKE / 3, midx + SNAKE / 3);
}

void g_x() {//更新说明
	cout << "更新说明(3.0.1)：\n";
	cout << "1,开放技能使用\n";
	cout << "2,现在可以将所有设置进行保存，无需每次重新设置\n";
	cout << "3,测试模式将会需要密码！\n";
	cout << "4,增加暂停功能，按空格可暂停\n";
	cout << "5,优化技能使用，详情见操作方式\n";
	cout << "6,游戏结束后保留画面，按任意键继续\n";
	cout << "7,新增一款人工智能\n";
	cout << "8,修复了一些已知的技能bug\n";
	cout << "9,优化了图像输出\n\n";

	

	cout << "10,正在设计第三款人工智能，敬请期待\n\n\n";
}


void out() {
	//int jlx[4] = { 0 }, jly[4] = { 0 };
	//int o1 = 0, o2 = 0, o3 = 0;

	BeginBatchDraw();
	cleardevice();

	for (int i = 0; i <= x + 1; i++) {
		for (int j = 0; j <= y + 1; j++) {
			if (y_j[i][j] > 2001 && y_j[i][j] < 3001) {
				setfillcolor(LIGHTRED);
				solidcircle((j + 1) * SNAKE, (i + 1) * SNAKE, SNAKE / 2);
				//setfillcolor(WHITE);
			}

			else if (y_j[i][j] > 1001 && y_j[i][j] < 2001) {
				setfillcolor(LIGHTCYAN);
				solidcircle((j + 1) * SNAKE, (i + 1) * SNAKE, SNAKE / 2);
				//setfillcolor(WHITE);
			}

			else if (y_j[i][j] == -8 || (use_jineng && (y_j[i][j] == 1001 && cd[0] == 0) || (y_j[i][j] == 2001 && cd[1] == 0))) {
				setfillcolor(RGB(255, 200, 0));

				_bar((i + 1) * SNAKE, (j + 1) * SNAKE);
				//setfillcolor(WHITE);
			}
			else if (y_j[i][j] == 1 || y_j[i][j] == 1001 || y_j[i][j] == 2001 || y_j[i][j] == 1000000) {
				setfillcolor(WHITE);
				_bar((i + 1) * SNAKE, (j + 1) * SNAKE);
			}
		}
	}

	EndBatchDraw();


	/*	BeginBatchDraw();
		cleardevice();


		setfillcolor(YELLOW);
		for (int i = 0; i < o3; i++) {
			_bar(jlx[i], jly[i]);
		}

		//solidrectangle(o_u_t[i].x - SNAKE / 2, o_u_t[i].y + SNAKE / 2, o_u_t[i].x + SNAKE / 2, o_u_t[i].y - SNAKE / 2);
		setfillcolor(WHITE);

		for (int i = 0; i < o1; i++) {
			solidcircle(snake_out[i].y, snake_out[i].x, SNAKE / 2);
		}

		for (int i = 0; i < o2; i++) {
			_bar(qiang_out[i].x, qiang_out[i].y);
		}
		EndBatchDraw();*/
		/*
			for (int i = 0; i < o; i++) {
				switch (o_u_t[i].lx) {
				case 2:
					_bar(o_u_t[i].x, o_u_t[i].y);
					break;
				case 1:
					solidcircle(o_u_t[i].y, o_u_t[i].x, SNAKE / 2);
					break;
				case 3: {
					setfillcolor(YELLOW);
					_bar(o_u_t[i].x, o_u_t[i].y);
					//solidrectangle(o_u_t[i].x - SNAKE / 2, o_u_t[i].y + SNAKE / 2, o_u_t[i].x + SNAKE / 2, o_u_t[i].y - SNAKE / 2);
					setfillcolor(WHITE);
					break;
				}

				default:
					break;
				}
			}*/
}

bool find(int l) {
	for (int i = 1; i <= x; i++) {
		for (int j = 1; j <= y; j++) {
			if (y_j[i][j] == l) {
				f_x = i; f_y = j;
				return 0;
			}
		}
	}
}

bool yzh_m_m();
void w_b_out();

void sh_zh() {//设置 
	system("cls");


	printf("更改地图大小--按1\n");
	printf("更改游戏刻--按2\n");
	printf("更改障碍物--按3\n");
	printf("更改图像输出--按4\n");
	printf("进入测试模式--按5\n");
	printf("改变图像大小--按6\n");
	printf("电脑是否可用技能--按7\n");
	printf("技能无cd--按8\n");
	printf("更改人工智能--按9\n");
	printf("退出--按Esc\n");

	while (1) {
		if (_kbhit()) {
			int ch = _getch();
			if (ch == '1') {
				cout << "请输入行数：";
				cin >> x;
				cout << "请输入列数：";
				cin >> y;
			}
			else if (ch == '2') {
				cout << "请输入游戏刻（每一个游戏刻蛇移动一格，单位为秒，可以是小数）：";
				cin >> speed;
			}
			else if (ch == '3') {
				cout << "0为不使用障碍物，1为使用";
				cin >> zh_ai;
			}
			else if (ch == '4') {
				cout << "0为不输出图像，1为输出";
				cin >> out_csh;
			}
			else if (ch == '5') {
				if (m_m_c_sh) {
					if (yzh_m_m()) {
						cout << "0为不测试，1为测试";
						cin >> _csh_;
						if (_csh_)
						{
							speed = 0;
							money = 1000000;
						}
					}
					else break;
				}
				else {
					cout << "0为不测试，1为测试";
					cin >> _csh_;
					if (_csh_)
					{
						speed = 0;
						money = 1000000;
					}
				}
			}
			else if (ch == '6') {
				cout << "请输入图像大小：";
				cin >> SNAKE;
			}
			else if (ch == '7') {
				cout << "请输入电脑技能使用（0/1）：";
				cin >> dnjn;
			}
			else if (ch == '8') {
				if (m_m_c_sh) {
					if (!yzh_m_m()) {
						break;
					}
				}
				bool _b;
				cin >> _b;
				if(_b)
					set_cd[0] = set_cd[1] = 0;
				else {
					set_cd[0] = 50;
					set_cd[1] = 100;
				}
			}
			
			else if (ch == '9') {
				cout << "请输入人工智能分别为（1/2；1/2）：";
				cin >> dif[0] >> dif[1];
			}
			
			else if (ch == 27) {
				break;
			}
		}
	}
	//system("cls");
}

int random(int min, int max) {
	return rand() % (max - min + 1) + min;
}

bool yzh_m_m() {
	//验证密码 
	printf("请输入密码：");
	memset(m_m, 0, sizeof(m_m));
	for (int i = 0;;) {
		if (_kbhit()) {
			int ch = _getch();
			if (ch == 8) {
				if (i != 0)i--;
			}
			else if (ch == 13) {
				break;
			}
			else {
				m_m[i++] = ch;
			}
			system("cls");
			printf("请输入密码：");
			for (int j = 0; j < i; j++)cout << "*";
		}
	}

	//if (sizeof(m_m) != sizeof(m_m_nc))return false;

	for (int i = 0; m_m_nc[i] != 0; i++) {
		if (m_m[i] != m_m_nc[i]) {
			return false;
		}
	}

	/*printf("\n\n%s\n%s", m_m, m_m_nc);
	getch();*/

	//if (m_m == m_m_nc)return false;
	system("cls");
	cout << "密码正确";
	return true;
}

void w_b_in() {
	fin = fopen("./贪吃蛇数据.exe", "rb");

	fscanf(fin, "%d%d", &x, &y);
	fscanf(fin, "%f", &speed);
	if (x == 0 || y == 0)x = y = 50;
	if (speed == 0)speed = 0.1;
	fscanf(fin, "%d", &f_sh_max);
	fscanf(fin, "%d", &money);

	if (f_sh_max % j_m == 0)f_sh_max /= j_m;
	else f_sh_max = 0;

	if (money % j_m == 0)money /= j_m;
	else money = 0;

	/*if (y_j_t1 == 0)y_j_t1 = '1';
	if (y_j_t2 == 0)y_j_t1 = '2';
	if (y_j_sh == 0)y_j_t1 = 'A';
	if (y_j_x == 0)y_j_t1 = 'V';
	if (y_j_z == 0)y_j_t1 = '<';
	if (y_j_y == 0)y_j_t1 = '>';

	if (out_q == '\n')y_j_t1 = 1;
	if (out_jl == '\n')y_j_t1 = '*';*/

	fscanf(fin, "%d", &jn_xz[0]);
	fscanf(fin, "%d", &jn_xz[1]);

	fscanf(fin, "%d", &SNAKE);
	if (SNAKE == 0)SNAKE = 12;
	fscanf(fin, "%d", &dnjn);
	fscanf(fin, "%d", &zh_ai);
	fscanf(fin, "%d%d", &set_cd[0], &set_cd[1]);
	fscanf(fin, "%d%d", &dif[0], &dif[1]);
	fclose(fin);
}

void w_b_out() {
	fout = fopen("./贪吃蛇数据.exe", "wb");
	fprintf(fout, "%d %d\n", x, y);
	fprintf(fout, "%f\n", speed);
	fprintf(fout, "%d\n", f_sh_max * j_m);
	fprintf(fout, "%d\n", money * j_m);

	fprintf(fout, "%d\n", jn_xz[0]);
	fprintf(fout, "%d\n", jn_xz[1]);

	fprintf(fout, "%d\n", SNAKE);
	fprintf(fout, "%d\n", dnjn);
	fprintf(fout, "%d\n", zh_ai);
	fprintf(fout, "%d %d\n", set_cd[0], set_cd[1]);
	fprintf(fout, "%d %d\n", dif[0], dif[1]);
	
	fclose(fout);
}

void ch_sh() {
	//初始化
	_zt = 0;
	memset(y_j, 0, sizeof(y_j));
	//memset(y_j_out, 0, sizeof(y_j_out));
	y_j[1][1] = 1003; y_j[1][2] = 1002; y_j[1][3] = 1001;
	len[0] = 3;
	len[1] = 0;
	jl = 0;
	len_j[0] = 0;
	fx[0] = 4;
	die = 1;
	num_huihe = 0;
	for (int i = 0; i <= x; i++) {
		y_j[i][0] = y_j[i][y + 1] = 1000000;//1000000表示墙
	}
	for (int i = 0; i <= y + 1; i++) {
		y_j[0][i] = y_j[x + 1][i] = 1000000;//1000000表示墙
	}

	if (w_j_num == 2) {
		y_j[y][1] = 2003; y_j[y][2] = 2002; y_j[y][3] = 2001;
		len[1] = 3;
		len_j[1] = 0;
		fx[1] = 4;
	}

	if (zh_ai) {
		for (int j = 0; j < random(x / 10, x); j++) {
			int x1 = random(2, x - 1), y1 = random(2, y - 1);
			if (y_j[x1][y1] == 0)y_j[x1][y1] = 1;
			else j--;
		}
	}
	
	cd[0] = cd[1] = 0;
}

//--------------------------------------------------------------------------------
//computer opration

/*

short find_wall_2(int wx, int wy);

short find_wall_1(int wx, int wy) {//help the computer find the wall in left and right
	bool w1 = 1, w2 = 1;
	if (y_j[wx][wy - 1] > 0 && y_j[wx][wy + 1] > 0)return 0;
	for (int i = wy + 2; i <= y + 2; i++) {
		if (y_j[wx][i] == 1000000)break;
		if (y_j[wx][i] > 0) {
			if (find_wall_2(wx, i - 1) == 0) {
				w1 = 0;
				break;
			}
		}
	}
	for (int i = wy - 2; i >= 0; i--) {
		if (y_j[wx][i] == 1000000)break;
		if (y_j[wx][i] > 0) {
			if (find_wall_2(wx, i+1) == 0) {
				w2 = 0;
				break;
			}
		}
	}
	if (w1 && w2)return 3;
	if (w1)return 1;
	if (w2)return 2;
	return 0;
}

short find_wall_2(int wx, int wy) {//help the computer find the wall in up and down
	bool w1 = 1, w2 = 1;
	if ((y_j[wx - 1][wy] > 0 && y_j[wx - 1][wy] != 1000000) && (y_j[wx + 1][wy] > 0 && y_j[wx + 1][wy] != 1000000))return 0;
	for (int i = wx + 2; i <= x + 2; i++) {
		if (y_j[i][wy] == 1000000)break;
		if (y_j[i][wy] > 0) {
			if (find_wall_1(i - 1, wy) == 0) {
				w1 = 0;
				break;
			}
		}
	}
	for (int i = wx - 2; i >= 0; i--) {
		if (y_j[i][wy] == 1000000)break;
		if (y_j[i][wy] > 0) {
			if (find_wall_1(i + 1, wy) == 0) {
				w2 = 0;
				break;
			}
		}
	}
	if (w1 && w2)return 3;
	if (w1)return 1;
	if (w2)return 2;
	return 0;
}

*/

/*

short find_wall(int wx, int wy, int step) {//Depth First Search to find the wall

	//if (step > (int)(len[0] * len[0] / 15) && step > (int)(len[1] * len[1] / 15) && step > 10)return 5;
	if (step > 100)return 5;
	short fw;
	int cunchu;

	if (y_j[wx - 1][wy] <= 0) {
		cunchu = y_j[wx][wy];
		y_j[wx][wy] = 1;
		fw = find_wall(wx - 1, wy, step + 1);
		y_j[wx][wy] = cunchu;
		if (fw != 0) {
			return 1;
		}
	}
	if (y_j[wx + 1][wy] <= 0) {
		cunchu = y_j[wx][wy];
		y_j[wx][wy] = 1;
		fw = find_wall(wx + 1, wy, step + 1);
		y_j[wx][wy] = cunchu;
		if (fw != 0) {
			return 2;
		}
	}
	if (y_j[wx][wy - 1] <= 0) {
		cunchu = y_j[wx][wy];
		y_j[wx][wy] = 1;
		fw = find_wall(wx, wy - 1, step + 1);
		y_j[wx][wy] = cunchu;
		if (fw != 0) {
			return 3;
		}
	}
	if (y_j[wx][wy + 1] <= 0) {
		cunchu = y_j[wx][wy];
		y_j[wx][wy] = 1;
		fw = find_wall(wx, wy + 1, step + 1);
		y_j[wx][wy] = cunchu;
		if (fw != 0) {
			return 4;
		}
	}
	return 0;
}
*/

short find_wall(short wfx, int wx, int wy) {
	if (wfx == 1)wx--;
	else if (wfx == 2)wx++;
	else if (wfx == 3)wy--;
	else wy++;

	if (wfx == 1 || wfx == 2) {
		if (y_j[wx][wy - 1] == y_j[wx][wy] - 1 || y_j[wx][wy + 1] == y_j[wx][wy] + 1)
			return 4;
		return 3;
	}
	if (y_j[wx - 1][wy] == y_j[wx][wy] - 1 || y_j[wx + 1][wy] == y_j[wx][wy] + 1)
		return 2;
	return 1;
}

void npc(int a, int b) {//电脑运算
	find(a * 1000 + 2);
	if (b == 2 && cd[a - 1] == 0 && num_huihe > a + 1)
	{
		y_j[f_x][f_y] = 0;

		find(-8);
		y_j[f_x][f_y] = a * 1000 + 2;

		cd[a - 1] = set_cd[1];

		len[a - 1]++; jl = 0; len_j[a - 1] = 1;

		if (y_j[f_x - 1][f_y] == 0)fx[a - 1] = 1;
		else if (y_j[f_x + 1][f_y] == 0)fx[a - 1] = 2;
		else if (y_j[f_x][f_y - 1] == 0)fx[a - 1] = 3;
		else if (y_j[f_x][f_y + 1] == 0)fx[a - 1] = 4;
		return;
	}

	find(-8);
	int x_x, x_y, y_j_x, y_j_y;
	x_x = f_x; x_y = f_y;
	find(a * 1000 + 2);
	int f_pd[5] = { 0 };
	short fw = 1;
	bool do_fw = 0;

	//find the wall:

	
	if ((fx[a - 1] == 1 && y_j[f_x - 1][f_y] > 1000 && y_j[f_x - 1][f_y] <= 3000) || \
		(fx[a - 1] == 2 && y_j[f_x + 1][f_y] > 1000 && y_j[f_x + 1][f_y] <= 3000) || \
		(fx[a - 1] == 3 && y_j[f_x][f_y - 1] > 1000 && y_j[f_x][f_y - 1] <= 3000) || \
		(fx[a - 1] == 4 && y_j[f_x][f_y + 1] > 1000 && y_j[f_x][f_y + 1] <= 3000)) {
		
		do_fw = 1;
		fw = find_wall(fx[a - 1], f_x, f_y);
	}
	
	/*
	if ((fx[a - 1] == 3 && y_j[f_x][f_y - 1] > 0 && y_j[f_x][f_y - 1] != 1000000) || \
		((fx[a - 1] == 4 && y_j[f_x][f_y + 1] > 0 && y_j[f_x][f_y + 1] != 1000000))) {
		short lsh = find_wall_2(f_x, f_y);
		if (lsh == 1) {
			fx[a - 1] = 2;
			return;
		}
		if (lsh == 2) {
			fx[a - 1] = 1;
			return;
		}
		
	}
	*/

	//-------------------------------------------------------------------------------------
	

	for (int t = 1; t <= 4; t++) {
		int h;
		if (t == 1) {
			h = y_j[f_x - 1][f_y];
		}

		else if (t == 2) {
			h = y_j[f_x + 1][f_y];
		}

		else if (t == 3) {
			h = y_j[f_x][f_y - 1];
		}

		else if (t == 4) {
			h = y_j[f_x][f_y + 1];
		}
		
		if (h > 0) {
			f_pd[t] = -100;
		}

		else if (h == -8) {
			f_pd[t] = 100;
		}
		else if (h == 0) {
			y_j_x = f_x; y_j_y = f_y;

			f_pd[t] = 0;
			if (t == 1 && y_j_x > x_x) {
				f_pd[1] = 1;
			}
			else if (t == 3 && y_j_y > x_y) {
				f_pd[3] = 1;
			}
			if (t == 2 && y_j_x < x_x) {
				f_pd[2] = 1;
			}
			else if (t == 4 && y_j_y < x_y) {
				f_pd[4] = 1;
			}

		}
	}

	//--------------------------
	
	int _max = max(max(f_pd[1], f_pd[2]), max(f_pd[3], f_pd[4]));

	if (do_fw && f_pd[fw] != -100)fx[a - 1] = fw;

	else if (b == 1 && dnjn && use_jineng && _max == -100 && cd[a - 1] == 0) {
		y_j[f_x][f_y] = 0;
		
		find(-8);
		y_j[f_x][f_y] = a * 1000 + 2;

		cd[a - 1] = set_cd[1];

		len[a - 1]++; jl = 0; len_j[a - 1] = 1;

		if (y_j[f_x - 1][f_y] == 0)fx[a - 1] = 1;
		else if (y_j[f_x + 1][f_y] == 0)fx[a - 1] = 2;
		else if (y_j[f_x][f_y - 1] == 0)fx[a - 1] = 3;
		else if (y_j[f_x][f_y + 1] == 0)fx[a - 1] = 4;
	}

	

	else if (f_pd[4] == _max)fx[a - 1] = 4;
	else if (f_pd[3] == _max)fx[a - 1] = 3;
	else if (f_pd[2] == _max)fx[a - 1] = 2;
	else if (f_pd[1] == _max)fx[a - 1] = 1;
}
//--------------------------------------------------------------------------------------


void jn_buy() {
	system("cls");
	cout << "1、放置障碍物=>cd:50游戏刻=>0金币=>按1" << endl;
	cout << "2、瞬移蛇头=>cd:100游戏刻=>0金币=>按2" << endl;
	//cout << "注：新购买技能将会覆盖以前技能，并会永久保留，直到下次更改" << endl;
	//cout<<"2、=>1000金币=>按2"<<endl;
	cout << "按Esc退出" << endl;

	while (1) {
		//cout<<endl;
		if (_kbhit()) {
			int ch1 = _getch();
			if (ch1 == '1') {
				if (money >= 0) {
					cout << "购买成功" << endl;
					money -= 0;
					cout << "给玩家1装备=>按1\n";
					cout << "给玩家2装备=>按2\n";
					cout << "给玩家1和2装备=>按3\n";
					while (1) {
						if (_kbhit()) {
							int ch2 = _getch();
							if (ch2 == '1') {
								jn_xz[0] = 1;
								break;
							}
							else if (ch2 == '2') {
								jn_xz[1] = 1;
								break;
							}
							else if (ch2 == '3') {
								jn_xz[0] = jn_xz[1] = 1;
								break;
							}
						}
					}
					//jn_xz[0] = jn_xz[1] = 1;
					cout << "装备成功\n";
				}

				else {
					cout << "金币不足" << endl;
				}
			}
			else if (ch1 == '2') {
				if (money >= 0) {
					cout << "购买成功" << endl;
					money -= 0;
					cout << "给玩家1装备=>按1\n";
					cout << "给玩家2装备=>按2\n";
					cout << "给玩家1和2装备=>按3\n";
					while (1) {
						if (_kbhit()) {
							int ch2 = _getch();
							if (ch2 == '1') {
								jn_xz[0] = 2;
								break;
							}
							else if (ch2 == '2') {
								jn_xz[1] = 2;
								break;
							}
							else if (ch2 == '3') {
								jn_xz[0] = jn_xz[1] = 2;
								break;
							}
						}
					}

					//jn_xz[0] = jn_xz[1] = 2;
					cout << "装备成功\n";
				}

				else {
					cout << "金币不足" << endl;
				}

					//return 0; 
				}
			else if (ch1 == 27) {
				break;
			}
		}
	}
}

void shop() {
	system("cls");
	cout << "购买技能——按1" << endl;
	cout << "按Esc退出";

	while (1) {
		if (_kbhit()) {
			int ch = _getch();
			if (ch == '1') {
				jn_buy();
				system("cls");
				cout << "购买技能——按1" << endl;
				cout << "按Esc退出";
				//break;
			}
			else if (ch == 27) {
				break;
			}
		}
	}
}

void _jn(short nnn) {//技能
	find(1000 * nnn + 1001);
	int x1 = f_x, y1 = f_y;

	out();
	setfillcolor(RED);
	solidcircle((y1 + 1) * SNAKE, (x1 + 1) * SNAKE, SNAKE / 2);
	setfillcolor(WHITE);

	while (1) {
		if (_kbhit()) {
			int ch = _getch();
			if (ch == 'w' && nnn == 0)x1--;
			else if (ch == 's' && nnn == 0)x1++;
			else if (ch == 'a' && nnn == 0)y1--;
			else if (ch == 'd' && nnn == 0)y1++;

			else if (ch == 'i' && nnn == 1)x1--;
			else if (ch == 'k' && nnn == 1)x1++;
			else if (ch == 'j' && nnn == 1)y1--;
			else if (ch == 'l' && nnn == 1)y1++;
			else if ((ch == 'e' && nnn == 0) || (ch == 'u' && nnn == 1)) {
				if (jn_xz[nnn] == 1 && y_j[x1][y1] == 0) {

					//closegraph();
					break;
				}
				if (jn_xz[nnn] == 2 && (y_j[x1][y1] == 0 || y_j[x1][y1] == -8)) {
					//closegraph();
					break;
				}
			}

			out();
			setfillcolor(RED);
			solidcircle((y1 + 1) * SNAKE, (x1 + 1) * SNAKE, SNAKE / 2);
			setfillcolor(WHITE);
		}
	}

	if (jn_xz[nnn] == 1) {
		y_j[x1][y1] = 1;
		cd[nnn] = set_cd[0];
		//closegraph();
	}

	else if (jn_xz[nnn] == 2) {
		if (y_j[x1][y1] == -8) {
			len[nnn]++; jl = 0; len_j[nnn] = 1;
		}

		find((nnn + 1) * 1000 + 1);
		y_j[x1][y1] = (nnn + 1) * 1000 + 1;
		y_j[f_x][f_y] = 0;
		cd[nnn] = set_cd[1];
	}

}

int main() {
	if (!_csh_ && w_b)w_b_in();
	//ch_sh();

	if (_csh_ && m_m_c_sh) {
		if (!yzh_m_m()) {
			return 0;
		}
	}

	if (_csh_)money = 10000000;

	if (_csh_) {
		speed = 0;
	}

	while (1) {

		srand(time(0));




		system("cls");
		g_x();
		printf("按Esc键进入设置\n按Enter键进入游戏\n\n\
注：请不要在游玩期间强制退出，\n否则存档将不会保存！\n金币：%d\n\
按s进入商店", money);
		while (1) {
			if (_kbhit()) {
				int ch = _getch();
				if (ch == 13) {
					break;
				}
				else if (ch == 27) {
					sh_zh();
					w_b_out();
					//g_x();
					system("cls");
					printf("按Esc键进入设置\n按Enter键进入游戏\n\n\
注：请不要在游玩期间强制退出，\n否则存档将不会保存！\n金币：%d\n\
按s进入商店", money);
				}
				else if (ch == 's' && use_jineng) {
					shop();
					system("cls");
					printf("按Esc键进入设置\n按Enter键进入游戏\n\n\
注：请不要在游玩期间强制退出，\n否则存档将不会保存！\n金币：%d\n\
按s进入商店", money);
				}
			}
		}
		//getch();

		//y_j[1][1]=3;y_j[1][2]=2;y_j[1][3]=1;


		system("cls");
		printf("玩家1：w/s/a/d移动，e释放技能\n玩家2：i/k/j/l移动，u释放技能\n再按u/e确认技能位置\n按空格暂停\n\n");
		printf("单人模式--按1\n双人模式--按2\n与电脑对战--按3");
		while (1) {
			int ch = _getch();
			if (ch == '1') {
				w_j_num = 1;
				com = 0;
				break;
			}
			if (ch == '2') {
				w_j_num = 2;
				com = 0;
				break;
			}
			if (ch == '3') {
				w_j_num = 2;
				com = 1;
				break;
			}
		}


		double time_js = (double)clock() / CLOCKS_PER_SEC;
		double time_1 = time_js;
		ch_sh();
		initgraph((y + 3) * SNAKE, (x + 3) * SNAKE);
		//f_x=2;
		//out();
		while (die && len[0] < 1000 && len[1] < 1000 && len[0] + len[1] < x * y - 1) {

			time_js = (double)clock() / CLOCKS_PER_SEC;

			if (!_csh_)
			{
				if (_kbhit())
				{
					int ch = _getch();
					if ((ch == 'w' || ch == 'W') && fx[0] != 2)fx[0] = 1;
					else if ((ch == 's' || ch == 'S') && fx[0] != 1)fx[0] = 2;
					else if ((ch == 'a' || ch == 'A') && fx[0] != 4)fx[0] = 3;
					else if ((ch == 'd' || ch == 'D') && fx[0] != 3)fx[0] = 4;
					else if ((ch == 'e' || ch == 'E') && jn_xz[0] != 0 && cd[0] == 0 && use_jineng)_jn(0);

					if (!com) {
						if ((ch == 'i' || ch == 'I') && fx[1] != 2)fx[1] = 1;
						else if ((ch == 'k' || ch == 'K') && fx[1] != 1)fx[1] = 2;
						else if ((ch == 'j' || ch == 'J') && fx[1] != 4)fx[1] = 3;
						else if ((ch == 'l' || ch == 'L') && fx[1] != 3)fx[1] = 4;
						else if ((ch == 'u' || ch == 'U') && jn_xz[1] != 0 && cd[1] == 0 && use_jineng)_jn(1);
					}

					if (ch == 32)
					{
						_zt = 1;
					}
				}
			}

			if (_csh_)
			{
				if (_kbhit())
				{
					int ch = _getch();
					if (ch == 32)
					{
						_zt = 1;
					}
				}
			}
			
			while (_zt)
			{
				if (_kbhit())
				{
					int ch = _getch();
					if (ch == 32)
					{
						_zt = 0;
						break;
					}
				}
			}


			if (time_js >= time_1 + speed) {
				num_huihe++;

				if (cd[0] > 0) {
					cd[0]--;
				}
				if (cd[1] > 0) {
					cd[1]--;
				}




				time_1 = time_js;


				for (int i = 0; i <= x; i++) {//项目前移
					for (int j = 0; j <= y; j++) {
						if (y_j[i][j] > 0 && y_j[i][j] != 1000000 && y_j[i][j] != 1)y_j[i][j]++;
					}
				}

				for (int l = 0; l < w_j_num; l++) {


					if (len_j[l] == 0) {
						find(len[l] + 1 + (l + 1) * 1000);//销毁最后一项 
						y_j[f_x][f_y] = 0;
					}
					len_j[l] = 0;
				}


				for (int l = 0; l < w_j_num; l++) {
					if (_csh_)npc(l + 1, dif[l]);
					else if (com && l)npc(2, dif[1]);



					//查找第一项 
					find(2 + (l + 1) * 1000);
					int h;
					if (fx[l] == 1) {
						h = y_j[f_x - 1][f_y];
					}

					else if (fx[l] == 2) {
						h = y_j[f_x + 1][f_y];
					}

					else if (fx[l] == 3) {
						h = y_j[f_x][f_y - 1];
					}

					else if (fx[l] == 4) {
						h = y_j[f_x][f_y + 1];
					}

					if (h == -8) {
						len[l]++; jl = 0; len_j[l] = 1;
					}
					else if (h > 0) {
						die = 0;
						if (w_j_num != 1 && !_csh_) {
							len[l] = 0;
						}
					}



					if (fx[l] == 1) {
						y_j[f_x - 1][f_y] = 1 + (l + 1) * 1000;
					}

					else if (fx[l] == 2) {
						y_j[f_x + 1][f_y] = 1 + (l + 1) * 1000;
					}

					else if (fx[l] == 3) {
						y_j[f_x][f_y - 1] = 1 + (l + 1) * 1000;
					}

					else if (fx[l] == 4) {
						y_j[f_x][f_y + 1] = 1 + (l + 1) * 1000;
					}

				}
				if (out_csh)out();
				//else printf("第%d步\n",num_huihe);



//----------------------------------------------------------------------------


				//设置奖励
				if (jl == 0) {
					while (jl == 0) {
						int jl_x = random(1, x), jl_y = random(1, y);
						if (y_j[jl_x][jl_y] == 0) {
							y_j[jl_x][jl_y] = -8;
							jl = 1;
						}
					}
				}
			}
		}

		//if (_csh_) {
		out();
		if (!_csh_ && w_b)w_b_out();
		_getch();
		//}

		closegraph();
		system("cls");

		if (w_j_num == 1) {
			if (len[0] > f_sh_max)f_sh_max = len[0];

			money += (len[0] - 3) * 100;

			printf("你得了%d分\n历史最高%d分\n", len[0], f_sh_max);

		}


		else {
			printf("玩家1:%d分\n玩家2:%d分\n", len[0], len[1]);
		}
		printf("共经过%d个游戏刻\n\n按Enter继续游戏，按Esc退出\n", num_huihe);


		while (1) {
			if (_kbhit()) {
				int ch = _getch();
				if (ch == 13) {
					system("cls");
					ch_sh();
					//f_x=2;
					break;
				}
				else if (ch == 27) {
					return 0;
				}
			}
		}

	}
	return 0;
}
