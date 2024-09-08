//AlphaBeta.h：使用αβ剪枝算法搜索步数
//
#pragma once
#include"DataStruct.h"
#include"AmazonGame.h"
#include"SearchEngine.h"
#include"evaluateFunction.h"
#include<string.h>

extern int SearchDepth;//设置搜索深度
extern int a_step;//记录交替走过的步数
extern int mode;//AI决策模式
extern int CurPosition[12][12];//将实际操作的棋盘复制到这里，在这个棋盘上进行模拟行棋和评估
extern CHESSMOVE BestMove;

void SearchAGoodMove(int Board[12][12],int computerSide);
double AlphaBetaSearch(int depth, double alpha = -INFI, double beta = INFI);//传入两个默认参数alpha和beta
int JudgeWin(int Board[12][12]); //AI判断获胜方
// 对CurPosition进行操作
void MakeMove(CHESSMOVE * move);
void UndoMakeMove(CHESSMOVE* move);
