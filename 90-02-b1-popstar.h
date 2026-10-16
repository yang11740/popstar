#pragma once
/*2352475 ¼Æ¿Æ Ò×Ñô*/

#define ROW_MAX 10
#define COL_MAX 10
#define ROW_MIN 8
#define COL_MIN 8

void show_check(int row, int col, const char* row_sign, const char* col_sign, struct RAND str[10][10]);
int select_by_keyboard_and_mouse(int row, int col, struct RAND str[10][10], int divide, const char* frame[], const char* unit, char sel);
int game(int row, int col, struct RAND str[10][10], const char* frame[], const char* unit,int* sum);
