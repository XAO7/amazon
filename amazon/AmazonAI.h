#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include"AmazonGame.h"
#include"AlphaBeta.h"

void 	AICompute(int Board[10][10],int computerSide,Step& step);//通信框架的AI接口函数
void InitBoard(int Board[12][12]); //初始化棋盘
