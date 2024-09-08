//searchFunction.h：搜索所有可能的步数和障碍
//
#pragma once
#include"DataStruct.h"
#include"AlphaBeta.h"

extern CHESSMOVE MoveList[8][2500];     //用以存储步法,结构体数组
extern int MoveCount;       //记录步法总数
extern int Offset[8][2];      //定义偏移量，简化代码

void initOffset();
int getPossibleMove(int Board[12][12], int depth, int Side);
void getPossibleBar(int Board[12][12], int depth, int Side, int FromX, int FromY, int ToX, int ToY);
