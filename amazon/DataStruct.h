//DataStruct.h��AI�㷨ʹ�õĽṹ��Ķ���
//
#pragma once
#define BLACKCHESS 2
#define WHITECHESS 1
#define BARRIER -1//�ϰ�
#define EMPTY 0
#define INFI 9999 //�����

extern int Board[12][12];//ȫ�ֱ���

typedef struct Pos//λ������ṹ��
{
	int x;
	int y;
}CHESSPOS;

typedef struct Move  //�����ṹ��
{
	int ChessID;//���巽
	double score;//�����÷�
	CHESSPOS From;
	CHESSPOS To;
	CHESSPOS Bar;
}CHESSMOVE;
