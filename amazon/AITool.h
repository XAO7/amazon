//AITool.h :包含了通信框架和AI共用的一些判断函数；

#ifndef TEST_AI_H
#define TEST_AI_H

#include"AmazonGame.h"
#include<cstdlib>

void AICompute_TEST(int Board[10][10], int computerSide, Step& final_step);
bool CanMoveOrShoot(int plate[10][10], SPosition posFrom, SPosition posTo);
void printBoard(int Board[10][10]);
double ValueOfStep(int Board[10][10], int computerSide, SPosition outPosSelected, SPosition outPosMoveTo, SPosition& outPosShootAt);
long ValueOfStep_TEST(int Board[10][10], int computerSide, SPosition outPosSelected, SPosition outPosMoveTo, SPosition& outPosShootAt);
double ValueOfShoot(int Board[10][10], SPosition outPosMoveTo, SPosition outPosShootAt);
double getFreeStand(int Board[10][10], SPosition position);
int getWinside(int Board[10][10], Step Book[92]); //通信框架获取获胜方

#endif
