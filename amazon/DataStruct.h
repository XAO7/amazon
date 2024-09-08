//DataStruct.h：AI算法使用的结构体的定义
//
#pragma once
#define BLACKCHESS 2
#define WHITECHESS 1
#define BARRIER -1//障碍
#define EMPTY 0
#define INFI 9999 //无穷大

extern int Board[12][12];//全局变量

typedef struct Pos//位置坐标结构体
{
	int x;
	int y;
}CHESSPOS;

typedef struct Move  //步法结构体
{
	int ChessID;//行棋方
	double score;//评估得分
	CHESSPOS From;
	CHESSPOS To;
	CHESSPOS Bar;
}CHESSMOVE;
