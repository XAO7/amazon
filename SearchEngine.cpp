#include"SearchEngine.h"

int Offset[8][2] = { 0 };
int MoveCount = 0;
CHESSMOVE MoveList[8][2500] = { 0 };

void initOffset()
{
	Offset[0][0] = 0; Offset[0][1] = -1;//������ƫ�ƣ���������
	Offset[1][0] = -1; Offset[1][1] = -1;
	Offset[2][0] = -1; Offset[2][1] = 0;
	Offset[3][0] = -1; Offset[3][1] = 1;
	Offset[4][0] = 0; Offset[4][1] = 1;
	Offset[5][0] = 1; Offset[5][1] = 1;
	Offset[6][0] = 1; Offset[6][1] = 0;
	Offset[7][0] = 1; Offset[7][1] = -1;
}

int getPossibleMove(int Board[12][12], int depth, int Side)
{
	int i, j, k, l, t;
	int Position[12][12] = { 0 };   //��ʱ�洢�����̣���ֹ��ԭ����������
	initOffset();       //����ƫ����
	memcpy(Position, Board, 144 * sizeof(int));   //����������Ϣ
	MoveCount = 0;  //�Ʋ�������
	for (i = 1; i <= 10; i++)
	{
		for (j = 1; j <= 10; j++)
		{
			if (Position[i][j] == Side)//�ҵ�����
			{
				k = i;
				l = j;
				for (t = 0; t < 8; t++)//�����ӵ���Χ�˸���������ƫ��
				{
					//����ÿ��ƫ��·��
					k += Offset[t][0];//����ƫ��
					l += Offset[t][1];
					while (Position[k][l] == EMPTY)
					{
						getPossibleBar(Position, depth, Side, i, j, k, l);
						////�����ظ�·��ƫ��
						k += Offset[t][0];
						l += Offset[t][1];
					}
					k = i;//�ָ��������꣬Ϊ��һ��������ƫ����׼��
					l = j;
				}
			}
		}
	}
	return MoveCount;//�������ɵĲ�������
}

void getPossibleBar(int Board[12][12], int depth, int Side, int FromX, int FromY, int ToX, int ToY)
{
	int k, l;
	//ģ���������ӵĹ��̣����ڶԷ����ϰ��ж�
	Board[FromX][FromY] = EMPTY;
	Board[ToX][ToY] = Side;
	k = ToX;
	l = ToY;
	for (int t = 0; t < 8; t++)
	{
		k += Offset[t][0];
		l += Offset[t][1];
		while (Board[k][l] == EMPTY)
		{
			//���Ų���
			MoveList[depth][MoveCount].From.x = FromX;//������ʼλ������
			MoveList[depth][MoveCount].From.y = FromY;
			MoveList[depth][MoveCount].To.x = ToX;//��������λ������
			MoveList[depth][MoveCount].To.y = ToY;
			MoveList[depth][MoveCount].Bar.x = k;//�����ϰ�������
			MoveList[depth][MoveCount].Bar.y = l;
			MoveList[depth][MoveCount].ChessID = Side;
			MoveList[depth][MoveCount].score = 0;
			//�Ʋ�����������
			MoveCount++;

			//�����ظ�·��ƫ��
			k += Offset[t][0];
			l += Offset[t][1];
		}
		k = ToX;//�ָ����꣬Ϊ��һ��������ƫ����׼��
		l = ToY;
	}
	//�ָ����̣�����ģ��������
	Board[ToX][ToY] = EMPTY;
	Board[FromX][FromY] = Side;
}
