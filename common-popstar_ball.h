#pragma once

//结构体定义
struct RAND {
	char number;
	bool sign = 0;
	int color = 0;
	int zero_up = 0;
};

//共用函数声明

/*菜单*/
char menu(const char* Input[], const char* choice);

/*输入*/
void input(int* row, int* col, int row_min, int row_max, int col_min, int col_max);

/*产生随机数组*/
void produce(int row, int col, int figure, struct RAND str[10][10]);

/*打印初始数组*/
void print_table(int row, int col, const char* row_sign, const char* col_sign, struct RAND str[10][10]);

/*查找可消除项*/
void judge(int row, int col, int t_row, int t_col, struct RAND str[10][10]);

/*计算本次可消除项数*/
int cal_num(int row, int col, struct RAND str[10][10]);

/*标记可消除项，用其他颜色高亮显示*/
void mark(int row, int col, const char* row_sign, const char* col_sign, struct RAND str[10][10]);

/*消除可消除项后置0*/
void make_zero(int row, int col, struct RAND str[10][10]);

/*高亮显示值为0的项*/
void mark_zero(int row, int col, const char* row_sign, const char* col_sign, struct RAND str[10][10]);

/*将所有值为0的项移动至数组最前面，如果整列均为0则整体移动到数组最右面*/
void move_zero(int row, int col, struct RAND str[10][10]);

/*放弃消除可消除项，重置数组标记*/
void cancel_operation(int row, int col, struct RAND str[10][10]);

/*本功能项测试完毕，等待返回主菜单或进行下一项操作*/
void wait(const char* prompt, int choice);

/*打印初始外部框架*/
void print_frame(int row, int col, struct RAND str[10][10], int RowColSign, const char* frame[], bool divide, int high, int length);

/*打印全部单元格色块*/
void print_unit(int row, int col, struct RAND str[10][10], const char* frame[], const char* unit, int* high, int* length, int divide, int RowColSign, int color);

/*打印单个单元格色块*/
void print_single(int x, int y, const char* frame[], const char* unit, int b_color, int f_color, int length);

/*打印色块移动*/
void print_move(int row, int col, struct RAND str[10][10], const char* frame[], const char* unit, int high, int length, int divide, int RowColSign);

/*判断游戏是否结束*/
int finish(int row, int col, struct RAND str[10][10], int base);
