//AlphaBeta.h��ʹ�æ��¼�֦�㷨��������
//
#pragma once
#include"DataStruct.h"
#include"AmazonGame.h"
#include"SearchEngine.h"
#include"evaluateFunction.h"
#include<string.h>

extern int SearchDepth;//�����������
extern int a_step;//��¼�����߹��Ĳ���
extern int mode;//AI����ģʽ
extern int CurPosition[12][12];//��ʵ�ʲ��������̸��Ƶ��������������Ͻ���ģ�����������
extern CHESSMOVE BestMove;

void SearchAGoodMove(int Board[12][12],int computerSide);
double AlphaBetaSearch(int depth, double alpha = -INFI, double beta = INFI);//��������Ĭ�ϲ���alpha��beta
int JudgeWin(int Board[12][12]); //AI�жϻ�ʤ��
// ��CurPosition���в���
void MakeMove(CHESSMOVE * move);
void UndoMakeMove(CHESSMOVE* move);
