//searchFunction.h���������п��ܵĲ������ϰ�
//
#pragma once
#include"DataStruct.h"
#include"AlphaBeta.h"

extern CHESSMOVE MoveList[8][2500];     //���Դ洢����,�ṹ������
extern int MoveCount;       //��¼��������
extern int Offset[8][2];      //����ƫ�������򻯴���

void initOffset();
int getPossibleMove(int Board[12][12], int depth, int Side);
void getPossibleBar(int Board[12][12], int depth, int Side, int FromX, int FromY, int ToX, int ToY);
