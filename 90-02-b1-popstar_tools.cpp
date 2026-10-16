#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "cmd_console_tools.h"
#include "common-popstar_ball.h"
#include "90-02-b1-popstar.h"
using namespace std;

/*用'*'显示可消除项，其余项显示0*/
void show_check(int row, int col, const char* row_sign, const char* col_sign, struct RAND str[10][10])
{
	int i, j;
	cout << "  |";
	for (i = 0; i < col; i++) {
		cout << "  " << col_sign[i];
	}
	cout << endl;
	cout << "--+";
	for (i = 0; i < 3 * col; i++) {
		cout << "-";
	}
	cout << endl;
	for (i = 0; i < row; i++) {
		cout << row_sign[i] << " |";
		for (j = 0; j < col; j++) {
			cout << "  " ;
			if (str[i][j].sign && str[i][j].number != '0') {
				cout << "*";
			}
			else {
				cout << '0';
			}
		}
		cout << endl;
	}
	cout << endl;
}
/*用键盘或鼠标选择“当前”色块*/
int select_by_keyboard_and_mouse(int row,int col, struct RAND str[10][10],int divide, const char* frame[], const char* unit,char sel)
{
	int x0 = 4, y0 = 3, x = x0, y = y0, i = 0, j = 0, X = 0, Y = 0, n = 0;
	int maction, keycode1, keycode2, select = 0, disappear = 0, down = 0;
	int MAX_X, MAX_Y, former_x = x0, former_y = y0, x_base, y_base;
	bool locate = 0;

	if (divide) {
		MAX_X = x0 + 5 + (col - 1) * 2 * 4;
		MAX_Y = y0 + 2 + (row - 1) * 4;
		X = 8;
		Y = 4;
		x_base = 8;
		y_base = 4;
	}
	else {
		MAX_X = x0 + 5 + (col - 1) * 2 * 3;
		MAX_Y = y0 + 2 + (row - 1) * 3;
		X = 6;
		Y = 3;
		x_base = 6;
		y_base = 3;
	}
	cct_setcursor(CURSOR_INVISIBLE);
	for (i = 0; i < row; i++) {
		if (str[i][0].number != '0') {
			print_single(x0 + X * j, y0 + Y * i, frame, unit, str[i][j].number, COLOR_HWHITE, 6);
			str[i][j].color = COLOR_HWHITE;
			former_x = x0 + X * j;
			former_y = y0 + Y * i;
			break;
		}
	}
	while (1) {
		cct_enable_mouse();
		locate = 0;
		cct_read_keyboard_and_mouse(x, y, maction, keycode1, keycode2);
		if (1 == select && ((y - y0) / y_base != (former_y - y0) / y_base || (x - x0) / x_base != (former_x - x0) / x_base)) {
			for (i = 0; i < row; i++) {
				for (j = 0; j < col; j++) {
					if (str[i][j].sign == 1 && str[i][j].number != '0') {
						print_single(x0 + X * j, y0 + Y * i, frame, unit, str[i][j].number, COLOR_BLACK, 6);
						str[i][j].color = COLOR_BLACK;
						str[i][j].sign = 0;
					}
				}
			}
			select = 0;
		}
		if (x == x0 && y == y0) {
			x = former_x;
			y = former_y;
		}
		if (divide) {
			if (x >= x0 + X * ((x - x0) / x_base)            &&
				y >= y0 + Y * ((y - y0) / y_base)            &&
				x <= x0 + X * ((x - x0) / x_base) + 6        &&
				y < y0 + Y * ((y - y0) / y_base) + 3         &&
				str[(y - y0) / y_base][(x - x0) / x_base].number != '0' &&
				x >= x0 && y >= y0 && x <= MAX_X && y <= MAX_Y) {
				locate = 1;
			}
		}
		else {
			if (x >= x0 && y >= y0 && x <= MAX_X && y <= MAX_Y) {
				locate = 1;
			}
		}
		if (locate) {
			cct_setcolor();
			if (keycode1 == 0xe0) {
				x = x0 + X * ((x - x0) / x_base);
				y = y0 + Y * ((y - y0) / y_base);
				cct_disable_mouse();
				cct_gotoxy(0, MAX_Y + 3);
				cout << "[当前键盘]  " << (char)('A' + (y - y0) / y_base) << "行" << (x - x0) / x_base << "列                    " << endl;
				if (1 == select) {
					for (i = 0; i < row; i++) {
						for (j = 0; j < col; j++) {
							if (str[i][j].sign == 1 && str[i][j].number != '0') {
								print_single(x0 + X * j, y0 + Y * i, frame, unit, str[i][j].number, COLOR_BLACK, 6);
								str[i][j].color = COLOR_BLACK;
								str[i][j].sign = 0;
							}
						}
					}
					select = 0;
				}
				if (KB_ARROW_UP == keycode2) {
					if (y != y0 && str[(y - Y - y0) / y_base][(x - x0) / x_base].number != '0') {
						print_single(x, y, frame, unit, str[(y - y0) / y_base][(x - x0) / x_base].number, COLOR_BLACK, 6);
						cct_gotoxy(x, y -= Y);
						print_single(x, y, frame, unit, str[(y - y0) / y_base][(x - x0) / x_base].number, COLOR_HWHITE, 6);
						str[(y - y0) / y_base][(x - x0) / x_base].color = COLOR_HWHITE;
						former_x = x;
						former_y = y;
					}
					else {
						print_single(x, y, frame, unit, str[(y - y0) / y_base][(x - x0) / x_base].number, COLOR_BLACK, 6);
						cct_gotoxy(x, y = MAX_Y - 2);
						print_single(x, y, frame, unit, str[(y - y0) / y_base][(x - x0) / x_base].number, COLOR_HWHITE, 6);
						str[(y - y0) / y_base][(x - x0) / x_base].color = COLOR_HWHITE;
						former_x = x;
						former_y = y;
					}
				}
				else if (KB_ARROW_DOWN == keycode2) {
					if (y != MAX_Y - 2) {
						print_single(x, y, frame, unit, str[(y - y0) / y_base][(x - x0) / x_base].number, COLOR_BLACK, 6);
						cct_gotoxy(x, y += Y);
						print_single(x, y, frame, unit, str[(y - y0) / y_base][(x - x0) / x_base].number, COLOR_HWHITE, 6);
						str[(y - y0) / y_base][(x - x0) / x_base].color = COLOR_HWHITE;
						former_x = x;
						former_y = y;
					}
					else {
						print_single(x, y, frame, unit, str[(y - y0) / y_base][(x - x0) / x_base].number, COLOR_BLACK, 6);
						cct_gotoxy(x, y = y0);
						while (str[(y - y0) / y_base][(x - x0) / x_base].number == '0') {
							cct_gotoxy(x, y += Y);
						}
						print_single(x, y, frame, unit, str[(y - y0) / y_base][(x - x0) / x_base].number, COLOR_HWHITE, 6);
						str[(y - y0) / y_base][(x - x0) / x_base].color = COLOR_HWHITE;
						former_x = x;
						former_y = y;
					}
				}
				else if (KB_ARROW_LEFT == keycode2) {
					if (x != x0 && str[(y - y0) / y_base][(x - X - x0) / x_base].number != '0') {
						print_single(x, y, frame, unit, str[(y - y0) / y_base][(x - x0) / x_base].number, COLOR_BLACK, 6);
						cct_gotoxy(x -= X, y);
						print_single(x, y, frame, unit, str[(y - y0) / y_base][(x - x0) / x_base].number, COLOR_HWHITE, 6);
						str[(y - y0) / y_base][(x - x0) / x_base].color = COLOR_HWHITE;
						former_x = x;
						former_y = y;
					}
					else {
						print_single(x, y, frame, unit, str[(y - y0) / y_base][(x - x0) / x_base].number, COLOR_BLACK, 6);
						cct_gotoxy(x = MAX_X - 5, y);
						while (str[(y - y0) / y_base][(x - x0) / x_base].number == '0') {
							cct_gotoxy(x -= X, y);
						}
						print_single(x, y, frame, unit, str[(y - y0) / y_base][(x - x0) / x_base].number, COLOR_HWHITE, 6);
						str[(y - y0) / y_base][(x - x0) / x_base].color = COLOR_HWHITE;
						former_x = x;
						former_y = y;
					}
				}
				else if (KB_ARROW_RIGHT == keycode2) {
					if (x != MAX_X - 5 && str[(y - y0) / y_base][(x + X - x0) / x_base].number != '0') {
						print_single(x, y, frame, unit, str[(y - y0) / y_base][(x - x0) / x_base].number, COLOR_BLACK, 6);
						cct_gotoxy(x += X, y);
						print_single(x, y, frame, unit, str[(y - y0) / y_base][(x - x0) / x_base].number, COLOR_HWHITE, 6);
						str[(y - y0) / y_base][(x - x0) / x_base].color = COLOR_HWHITE;
						former_x = x;
						former_y = y;
					}
					else {
						print_single(x, y, frame, unit, str[(y - y0) / y_base][(x - x0) / x_base].number, COLOR_BLACK, 6);
						cct_gotoxy(x = x0, y);
						while (str[(y - y0) / y_base][(x - x0) / x_base].number == '0') {
							cct_gotoxy(x += X, y);
						}
						print_single(x, y, frame, unit, str[(y - y0) / y_base][(x - x0) / x_base].number, COLOR_HWHITE, 6);
						str[(y - y0) / y_base][(x - x0) / x_base].color = COLOR_HWHITE;
						former_x = x;
						former_y = y;
					}
				}
			}
			else if ('Q' == keycode1 || 'q' == keycode1) {
				return -1;
			}
			else if (13 == keycode1) {
				cct_disable_mouse();
				if (sel == 'E' || sel == 'e' || sel == 'D' || sel == 'd') {
					cct_gotoxy(0, MAX_Y + 3);
					cout << "选择" << (char)('A' + (y - y0) / y_base) << "行" << (x - x0) / x_base << "列                   " << endl;
					return 0;
				}
				else if (sel == 'F' || sel == 'f' || sel == 'G' || sel == 'g') {
					if (select == 0) {
						judge(row, col, (y - y0) / y_base, (x - x0) / x_base, str);
						n = cal_num(row, col, str);
						if (n >= 2) {
							for (i = 0; i < row; i++) {
								for (j = 0; j < col; j++) {
									if (str[i][j].sign == 1 && str[i][j].number != '0') {
										print_single(x0 + X * j, y0 + Y * i, frame, unit, str[i][j].number, COLOR_HWHITE, 6);
										str[i][j].color = COLOR_HWHITE;
									}
								}
							}
							cct_setcolor();
							cct_gotoxy(0, MAX_Y + 3);
							cout << "箭头键/鼠标移动取消当前选择，回车键/单击左键合成" << endl;
							select = 1;
							continue;
						}
						else {
							cct_setcolor();
							cct_gotoxy(0, MAX_Y + 3);
							cout << "周围无相同值，箭头键/鼠标移动重新进行选择          " << endl;
							continue;
						}
					}
					if (0 == disappear && 1 == select) {
						make_zero(row, col, str);
						for (i = 0; i < row; i++) {
							for (j = 0; j < col; j++) {
								if (str[i][j].number == '0') {
									print_single(x0 + X * j, y0 + Y * i, frame, unit, COLOR_HWHITE, COLOR_HWHITE, 6);
								}
							}
						}
						disappear = 1;
						if (sel == 'F' || sel == 'f') {
							cct_setcolor();
							cct_gotoxy(0, MAX_Y + 3);
							cout << "合成完成，回车键/单击左键下落0                        " << endl;
							continue;
						}
					}
					if (0 == down && 1 == disappear && 1 == select) {
						print_move(row, col, str, frame, unit, 3, 6, divide, 1);
						select = 0;
						disappear = 0;
						return n;
					}
				}
			}
			else {
				cct_enable_mouse();
				if (select == 0) {
					cct_gotoxy(0, MAX_Y + 3);
					cout << "[当前鼠标]  " << (char)('A' + (y - y0) / y_base) << "行" << (x - x0) / x_base << "列                                          " << endl;
					if ((y - y0) / y_base != (former_y - y0) / y_base || (x - x0) / x_base != (former_x - x0) / x_base) {
						print_single(x0 + X * ((former_x - x0) / x_base), y0 + Y * ((former_y - y0) / y_base), frame, unit, str[(former_y - y0) / y_base][(former_x - x0) / x_base].number, COLOR_BLACK, 6);
					}
					print_single(x0 + X * ((x - x0) / x_base), y0 + Y * ((y - y0) / y_base), frame, unit, str[(y - y0) / y_base][(x - x0) / x_base].number, COLOR_HWHITE, 6);
					str[(y - y0) / y_base][(x - x0) / x_base].color = COLOR_HWHITE;
					former_x = x;
					former_y = y;
				}
				switch (maction) {
					case MOUSE_LEFT_BUTTON_CLICK:
						cct_setcolor();
						if (sel == 'E' || sel == 'e' || sel == 'D' || sel == 'd') {
							cct_gotoxy(0, MAX_Y + 3);
							cout << "选择" << (char)('A' + (y - y0) / y_base) << "行" << (x - x0) / x_base << "列                      " << endl;
							return 0;
						}
						else if (sel == 'F' || sel == 'f' || sel == 'G' || sel == 'g') {
							if (select == 0) {
								judge(row, col, (y - y0) / y_base, (x - x0) / x_base, str);
								n = cal_num(row, col, str);
								if (n >= 2) {
									for (i = 0; i < row; i++) {
										for (j = 0; j < col; j++) {
											if (str[i][j].sign == 1 && str[i][j].number != '0') {
												print_single(x0 + X * j, y0 + Y * i, frame, unit, str[i][j].number, COLOR_HWHITE, 6);
												str[i][j].color = COLOR_HWHITE;
											}
										}
									}
									cct_setcolor();
									cct_gotoxy(0, MAX_Y + 3);
									cout << "箭头键/鼠标移动取消当前选择，回车键/单击左键合成" << endl;
									select = 1;
									continue;
								}
								else {
									cct_setcolor();
									cct_gotoxy(0, MAX_Y + 3);
									cout << "周围无相同值，箭头键/鼠标移动重新进行选择         " << endl;
									Sleep(300);
									continue;
								}
							}
							if (0 == disappear && 1 == select) {
								make_zero(row, col, str);
								for (i = 0; i < row; i++) {
									for (j = 0; j < col; j++) {
										if (str[i][j].number == '0') {
											print_single(x0 + X * j, y0 + Y * i, frame, unit, COLOR_HWHITE, COLOR_HWHITE, 6);
										}
									}
								}
								disappear = 1;
								if (sel == 'F' || sel == 'f') {
									cct_setcolor();
									cct_gotoxy(0, MAX_Y + 3);
									cout << "合成完成，回车键/单击左键下落0                 " << endl;
									continue;
								}
							}
							if (0 == down && 1 == disappear && 1 == select) {
								print_move(row, col, str, frame, unit, 3, 6, divide, 1);
								select = 0;
								disappear = 0;
								return n;
							}
						}
						break;
					case MOUSE_RIGHT_BUTTON_CLICK:
						cct_setcursor(CURSOR_VISIBLE_NORMAL);
						return -1;
						break;
					default:
						break;
				}
			}
		}
		else {
			cct_setcolor();
			cct_gotoxy(0, MAX_Y + 3);
			cout << "[当前鼠标]  位置非法                                         " << endl;
			for (i = 0; i < row; i++) {
				for (j = 0; j < col; j++) {
					if (COLOR_HWHITE == str[i][j].color && str[i][j].number != '0') {
						print_single(x0 + X * j, y0 + Y * i, frame, unit, str[i][j].number, COLOR_BLACK, 6);
						str[i][j].color = COLOR_BLACK;
					}
				}
			}
		}
	}
}
/*进行完整版游戏*/
int game(int row, int col, struct RAND str[10][10], const char* frame[], const char* unit, int* sum)
{
	int score = 0, n = 0, s = 0, t = 0;
	while (finish(row, col, str, 2)) {
		cct_setcolor();
		cct_gotoxy(0, 0);
		cout << "本次得分：" << score << "  总得分：" << *sum << "         " << endl;
		n = select_by_keyboard_and_mouse(row, col, str, 1, frame, unit, 'G');
		if (n == -1) {
			return -1;
		}
		score = n * 5;
		*sum += score;
		s += score;
	}
	if (row * col - s / 5 < 10) {
		t = (10 - (row * col - s / 5)) * 100;
		*sum += t;
		cct_setcolor();
		cct_gotoxy(0, 0);
		cout << "奖励得分：" << t << "  总得分：" << *sum << "         " << endl;
	}
	return s;
}
