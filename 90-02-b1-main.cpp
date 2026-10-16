/* 2352475 计科 易阳 */
#include <iostream>
#include <conio.h>
#include "../include/cmd_console_tools.h"
#include "../include/common-popstar_ball.h"
#include "90-02-b1-popstar.h"
using namespace std;

int main()
{
	char sel, cur_row, cur_col, selection;
	int row, col, x, y, n, high, length, score = 0, sum = 0, ret;
	RAND popstar[10][10];
	const char* InputMenu[65] = {
		"A.命令行找出可消除项并标识",
		"B.命令行完成一次消除（分步骤显示）",
		"C.命令行完成一关（分步骤显示）",
		"D.伪图形界面下用鼠标选择一个色块（无分隔线）",
		"E.伪图形界面下用鼠标选择一个色块（有分隔线）",
		"F.伪图形界面完成一次消除（分步骤）",
		"G.伪图形界面完整版",
		"Q.退出",
		 NULL
	};
	const char* choice = "AaBbCcDdEeFfGgQq";
	const char* col_sign = "0123456789";
	const char* row_sign = "ABCDEFGHIJ";
	const char* unit = "★";
	const char* frame1[12] = { "╔","╦","╗","╠","╬","╣","╚","╩","╝","═","║" };
	const char* frame2[12] = { "┏","┳","┓","┣","╋","┫","┗","┻","┛","━","┃" };

	while (1) {
		cct_setconsoleborder(90, 30, 120, 9000);
		sel = menu(InputMenu, choice);
		n = 0;
		score = 0;
		sum = 0;
		if ('A' == sel || 'a' == sel || 'B' == sel || 'b' == sel || 'C' == sel || 'c' == sel) {
			cct_cls();
			input(&row, &col, ROW_MIN, ROW_MAX, COL_MIN, COL_MAX);
			produce(row, col, 5, popstar);
			while (1) {
				cout << "当前数组：" << endl;
				print_table(row, col, row_sign, col_sign, popstar);
				cout << endl;
				if (finish(row, col, popstar, 2)) {
					while (1) {
						cout << "请以字母+数字形式[例：c2]输入矩阵坐标：";
						cct_getxy(x, y);
						while (1) {
							cct_gotoxy(x, y);
							cout << "        ";
							cct_gotoxy(x, y);
							cin >> cur_row >> cur_col;
							if (cur_row >= 'a' && cur_row <= 'z') {
								cur_row -= 32;
							}
							if (strchr(row_sign, cur_row) != NULL && strchr(col_sign, cur_col) != NULL && cur_row <= row - 1 + 'A' && cur_col <= col - 1 + '0') {
								cout << "输入为" << cur_row << "行" << cur_col << "列                      " << endl;
								break;
							}
							else {
								cout << "输入错误，请重新输入" << endl;
							}
						}
						judge(row, col, cur_row - 'A', cur_col - '0', popstar);
						n = cal_num(row, col, popstar);
						if (n >= 2) {
							break;
						}
						else {
							cout << "输入的矩阵坐标位置处无连续相同值，请重新输入" << endl;
						}
					}
					cout << endl;
					cout << "查找结果数组：" << endl;
					show_check(row, col, row_sign, col_sign, popstar);
					cout << endl;
					cout << "当前数组(不同色标识):" << endl;
					mark(row, col, row_sign, col_sign, popstar);
					cout << endl;
					if ('A' == sel || 'a' == sel) {
						break;
					}
					cout << "请确认是否把" << cur_row << cur_col << "及周围的相同值消除(Y/N/Q)：";
					cin >> selection;
					if (selection == 'Y' || selection == 'y') {
						cout << "相同值归并后的数组(不同色标识)：" << endl;
						make_zero(row, col, popstar);
						mark(row, col, row_sign, col_sign, popstar);
						score = n * 5;
						sum += score;
						cout << "本次得分：" << score << "   总得分：" << sum << endl;
						wait("按回车键进行数组下落操作...", 1);
						cout << endl;
						cout << "下落后的数组：" << endl;
						move_zero(row, col, popstar);
						mark(row, col, row_sign, col_sign, popstar);
						if ('B' == sel || 'b' == sel) {
							break;
						}
						wait("本次消除结束，按回车键继续新一次的消除...", 1);
						cout << endl;
					}
					else if ('N' == selection || 'n' == selection) {
						cancel_operation(row, col, popstar);
						if ('B' == sel || 'b' == sel) {
							break;
						}
						continue;
					}
					else if ('Q' == selection || 'q' == selection) {
						break;
					}
				}
				else {
					cct_setcolor(COLOR_HYELLOW, COLOR_HPINK);
					cout << "剩余" << row * col - sum / 5 << "个不可消除项，本关结束！" << endl;
					cct_setcolor();
					break;
				}
			}
			wait(" ", 0);
		}
		else if ('D' == sel || 'd' == sel) {
			cct_cls();
			input(&row, &col, ROW_MIN, ROW_MAX, COL_MIN, COL_MAX);
			produce(row, col, 5, popstar);
			cct_cls();
			print_frame(row, col, popstar, 1, frame2, 0, 3, 6);
			print_unit(row, col, popstar, frame1, unit, &high, &length, 0, 1, COLOR_BLACK);
			select_by_keyboard_and_mouse(row, col, popstar, 0, frame1, unit, sel);
			wait(" ", 0);
		}
		else if ('E' == sel || 'e' == sel) {
			cct_cls();
			input(&row, &col, ROW_MIN, ROW_MAX, COL_MIN, COL_MAX);
			produce(row, col, 5, popstar);
			cct_cls();
			print_frame(row, col, popstar, 1, frame2, 1, 3, 6);
			print_unit(row, col, popstar, frame1, unit, &high, &length, 1, 1, COLOR_BLACK);
			select_by_keyboard_and_mouse(row, col, popstar, 1, frame1, unit, sel);
			wait(" ", 0);
		}
		else if ('F' == sel || 'f' == sel) {
			cct_cls();
			input(&row, &col, ROW_MIN, ROW_MAX, COL_MIN, COL_MAX);
			produce(row, col, 5, popstar);
			cct_cls();
			print_frame(row, col, popstar, 1, frame2, 0, 3, 6);
			print_unit(row, col, popstar, frame1, unit, &high, &length, 0, 1, COLOR_BLACK);
			select_by_keyboard_and_mouse(row, col, popstar, 0, frame1, unit, sel);
			cct_gotoxy(0, 8 + (row-1) * 3);
			wait(" ", 0);
		}
		else if ('G' == sel || 'g' == sel) {
			cct_cls();
			input(&row, &col, ROW_MIN, ROW_MAX, COL_MIN, COL_MAX);
			sum = 0;
			while (1) {
				produce(row, col, 5, popstar);
				cct_cls();
				print_frame(row, col, popstar, 1, frame2, 1, 3, 6);
				print_unit(row, col, popstar, frame1, unit, &high, &length, 1, 1, COLOR_BLACK);
				ret = game(row, col, popstar, frame1, unit, &sum);
				if (-1 == ret) {
					break;
				}
				else if (ret > 0) {
					cct_gotoxy(0, 8 + (row - 1) * 4);
					cct_setcolor(COLOR_HYELLOW, COLOR_HPINK);
					cout << "剩余" << row * col - ret / 5 << "个星星未消除，本关结束！";
					cct_setcolor();
					cout << "                  " << endl;
					wait("按回车键继续进行下一关...", 1);
				}
			}
			cct_gotoxy(0, 8 + (row - 1) * 4);
			wait(" ", 0);
		}
		else if ('Q' == sel || 'q' == sel) {
			cct_setcolor();
			return 0;
		}
	}
}
