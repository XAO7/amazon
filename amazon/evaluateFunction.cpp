#include"evaluateFunction.h"

double t1 = 0;
double t2 = 0;
double c1 = 0;
double c2 = 0;
double w = 0;
double s = 0;
int KingmoveBlack[12][12] = { 0 };
int KingmoveWhite[12][12] = { 0 };
int QueenmoveBlack[12][12] = { 0 };
int QueenmoveWhite[12][12] = { 0 };
int Mobility[12][12] = { 0 };
int aBlack[4] = { 0 };
int aWhite[4] = { 0 };

///////����KingMove//////
void SearchKingMove()
{
	register int i, j; //����Ĵ����������������Ч��
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			KingmoveBlack[i][j] = 0;  //��ģ���KingMove���̳�ʼ��
			KingmoveWhite[i][j] = 0;
		}
	}
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			if (CurPosition[i][j] == BLACKCHESS)//���������ҵ����壬��KingmoveBlack���̴洢KingMove�߷�
			{
				if (CurPosition[i][j - 1] == EMPTY)//����
				{
					KingmoveBlack[i][j - 1] = 1;
				}
				if (CurPosition[i - 1][j - 1] == EMPTY)//���Ϸ�
				{
					KingmoveBlack[i - 1][j - 1] = 1;
				}
				if (CurPosition[i - 1][j] == EMPTY)//���Ϸ�
				{
					KingmoveBlack[i - 1][j] = 1;
				}
				if (CurPosition[i - 1][j + 1] == EMPTY)//���Ϸ�
				{
					KingmoveBlack[i - 1][j + 1] = 1;
				}
				if (CurPosition[i][j + 1] == EMPTY)//���ҷ�
				{
					KingmoveBlack[i][j + 1] = 1;
				}
				if (CurPosition[i + 1][j + 1] == EMPTY)//���·�
				{
					KingmoveBlack[i + 1][j + 1] = 1;
				}
				if (CurPosition[i + 1][j] == EMPTY)//���·�
				{
					KingmoveBlack[i + 1][j] = 1;
				}
				if (CurPosition[i + 1][j - 1] == EMPTY)//���·�
				{
					KingmoveBlack[i + 1][j - 1] = 1;
				}
			}
			if (CurPosition[i][j] == WHITECHESS)//���������ҵ����壬��KingmoveWhite���̴洢KingMove�߷�
			{
				if (CurPosition[i][j - 1] == EMPTY)//����
				{
					KingmoveWhite[i][j - 1] = 1;
				}
				if (CurPosition[i - 1][j - 1] == EMPTY)//���Ϸ�
				{
					KingmoveWhite[i - 1][j - 1] = 1;
				}
				if (CurPosition[i - 1][j] == EMPTY)//���Ϸ�
				{
					KingmoveWhite[i - 1][j] = 1;
				}
				if (CurPosition[i - 1][j + 1] == EMPTY)//���Ϸ�
				{
					KingmoveWhite[i - 1][j + 1] = 1;
				}
				if (CurPosition[i][j + 1] == EMPTY)//���ҷ�
				{
					KingmoveWhite[i][j + 1] = 1;
				}
				if (CurPosition[i + 1][j + 1] == EMPTY)//���·�
				{
					KingmoveWhite[i + 1][j + 1] = 1;
				}
				if (CurPosition[i + 1][j] == EMPTY)//���·�
				{
					KingmoveWhite[i + 1][j] = 1;
				}
				if (CurPosition[i + 1][j - 1] == EMPTY)//���·�
				{
					KingmoveWhite[i + 1][j - 1] = 1;
				}
			}
		}
	}
	for (register int n = 1; n < 11; n++)//������������ͨ��KingMove�߷������10��
	{
		for (i = 0; i < 12; i++)
		{
			for (j = 0; j < 12; j++)
			{
				if (KingmoveBlack[i][j] == n)//�ҵ�����KingMove��Ӧ�Ĳ�����
				{
					if (CurPosition[i][j - 1] == EMPTY && KingmoveBlack[i][j - 1] == 0)
					{
						KingmoveBlack[i][j - 1] = n + 1;
					}
					if (CurPosition[i - 1][j - 1] == EMPTY && KingmoveBlack[i - 1][j - 1] == 0)
					{
						KingmoveBlack[i - 1][j - 1] = n + 1;
					}
					if (CurPosition[i - 1][j] == EMPTY && KingmoveBlack[i - 1][j] == 0)
					{
						KingmoveBlack[i - 1][j] = n + 1;
					}
					if (CurPosition[i - 1][j + 1] == EMPTY && KingmoveBlack[i - 1][j + 1] == 0)
					{
						KingmoveBlack[i - 1][j + 1] = n + 1;
					}
					if (CurPosition[i][j + 1] == EMPTY && KingmoveBlack[i][j + 1] == 0)
					{
						KingmoveBlack[i][j + 1] = n + 1;
					}
					if (CurPosition[i + 1][j + 1] == EMPTY && KingmoveBlack[i + 1][j + 1] == 0)
					{
						KingmoveBlack[i + 1][j + 1] = n + 1;
					}
					if (CurPosition[i + 1][j] == EMPTY && KingmoveBlack[i + 1][j] == 0)
					{
						KingmoveBlack[i + 1][j] = n + 1;
					}
					if (CurPosition[i + 1][j - 1] == EMPTY && KingmoveBlack[i + 1][j - 1] == 0)
					{
						KingmoveBlack[i + 1][j - 1] = n + 1;
					}
				}
				if (KingmoveWhite[i][j] == n) //�ҵ�����KingMove��Ӧ�Ĳ�����
				{
					if (CurPosition[i][j - 1] == EMPTY && KingmoveWhite[i][j - 1] == 0)
					{
						KingmoveWhite[i][j - 1] = n + 1;
					}
					if (CurPosition[i - 1][j - 1] == EMPTY && KingmoveWhite[i - 1][j - 1] == 0)
					{
						KingmoveWhite[i - 1][j - 1] = n + 1;
					}
					if (CurPosition[i - 1][j] == EMPTY && KingmoveWhite[i - 1][j] == 0)
					{
						KingmoveWhite[i - 1][j] = n + 1;
					}
					if (CurPosition[i - 1][j + 1] == EMPTY && KingmoveWhite[i - 1][j + 1] == 0)
					{
						KingmoveWhite[i - 1][j + 1] = n + 1;
					}
					if (CurPosition[i][j + 1] == EMPTY && KingmoveWhite[i][j + 1] == 0)
					{
						KingmoveWhite[i][j + 1] = n + 1;
					}
					if (CurPosition[i + 1][j + 1] == EMPTY && KingmoveWhite[i + 1][j + 1] == 0)
					{
						KingmoveWhite[i + 1][j + 1] = n + 1;
					}
					if (CurPosition[i + 1][j] == EMPTY && KingmoveWhite[i + 1][j] == 0)
					{
						KingmoveWhite[i + 1][j] = n + 1;
					}
					if (CurPosition[i + 1][j - 1] == EMPTY && KingmoveWhite[i + 1][j - 1] == 0)
					{
						KingmoveWhite[i + 1][j - 1] = n + 1;
					}
				}
			}
		}
	}
}

///////����QueenMove/////
void SearchQueenMove()
{
	register int i, j, k, l;
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			QueenmoveBlack[i][j] = 0;//��queenmove���̳�ʼ��
			QueenmoveWhite[i][j] = 0;
		}
	}
	for (k = 0; k < 12; k++)
	{
		for (l = 0; l < 12; l++)
		{
			if (CurPosition[k][l] == BLACKCHESS)//�����Queenmove
			{
				i = k;
				j = l;
				while (CurPosition[i][j - 1] == EMPTY)
				{
					QueenmoveBlack[i][j - 1] = 1;
					j--;
				}
				i = k;
				j = l;
				while (CurPosition[i - 1][j - 1] == EMPTY)
				{
					QueenmoveBlack[i - 1][j - 1] = 1;
					i--;
					j--;
				}
				i = k;
				j = l;
				while (CurPosition[i - 1][j] == EMPTY)
				{
					QueenmoveBlack[i - 1][j] = 1;
					i--;
				}
				i = k;
				j = l;
				while (CurPosition[i - 1][j + 1] == EMPTY)
				{
					QueenmoveBlack[i - 1][j + 1] = 1;
					i--;
					j++;
				}
				i = k;
				j = l;
				while (CurPosition[i][j + 1] == EMPTY)
				{
					QueenmoveBlack[i][j + 1] = 1;
					j++;
				}
				i = k;
				j = l;
				while (CurPosition[i + 1][j + 1] == EMPTY)
				{
					QueenmoveBlack[i + 1][j + 1] = 1;
					i++;
					j++;
				}
				i = k;
				j = l;
				while (CurPosition[i + 1][j] == EMPTY)
				{
					QueenmoveBlack[i + 1][j] = 1;
					i++;
				}
				i = k;
				j = l;
				while (CurPosition[i + 1][j - 1] == EMPTY)
				{
					QueenmoveBlack[i + 1][j - 1] = 1;
					i++;
					j--;
				}
			}
			if (CurPosition[k][l] == WHITECHESS)//�����QueenMove
			{
				i = k;
				j = l;
				while (CurPosition[i][j - 1] == EMPTY)
				{
					QueenmoveWhite[i][j - 1] = 1;
					j--;
				}
				i = k;
				j = l;
				while (CurPosition[i - 1][j - 1] == EMPTY)
				{
					QueenmoveWhite[i - 1][j - 1] = 1;
					i--;
					j--;
				}
				i = k;
				j = l;
				while (CurPosition[i - 1][j] == EMPTY)
				{
					QueenmoveWhite[i - 1][j] = 1;
					i--;
				}
				i = k;
				j = l;
				while (CurPosition[i - 1][j + 1] == EMPTY)
				{
					QueenmoveWhite[i - 1][j + 1] = 1;
					i--;
					j++;
				}
				i = k;
				j = l;
				while (CurPosition[i][j + 1] == EMPTY)
				{
					QueenmoveWhite[i][j + 1] = 1;
					j++;
				}
				i = k;
				j = l;
				while (CurPosition[i + 1][j + 1] == EMPTY)
				{
					QueenmoveWhite[i + 1][j + 1] = 1;
					i++;
					j++;
				}
				i = k;
				j = l;
				while (CurPosition[i + 1][j] == EMPTY)
				{
					QueenmoveWhite[i + 1][j] = 1;
					i++;
				}
				i = k;
				j = l;
				while (CurPosition[i + 1][j - 1] == EMPTY)
				{
					QueenmoveWhite[i + 1][j - 1] = 1;
					i++;
					j--;
				}
			}
		}
	}
	for (register int n = 1; n < 6; n++)
	{
		for (k = 0; k < 12; k++)
		{
			for (l = 0; l < 12; l++)
			{
				if (QueenmoveBlack[k][l] == n)
				{
					i = k;
					j = l;
					while (CurPosition[i][j - 1] == EMPTY && QueenmoveBlack[i][j - 1] == 0)
					{
						QueenmoveBlack[i][j - 1] = n + 1;
						j--;
					}
					i = k;
					j = l;
					while (CurPosition[i - 1][j - 1] == EMPTY && QueenmoveBlack[i - 1][j - 1] == 0)
					{
						QueenmoveBlack[i - 1][j - 1] = n + 1;
						i--;
						j--;
					}
					while (CurPosition[i - 1][j] == EMPTY && QueenmoveBlack[i - 1][j] == 0)
					{
						QueenmoveBlack[i - 1][j] = n + 1;
						i--;
					}
					i = k;
					j = l;
					while (CurPosition[i - 1][j + 1] == EMPTY && QueenmoveBlack[i - 1][j + 1] == 0)
					{
						QueenmoveBlack[i - 1][j + 1] = n + 1;
						i--;
						j++;
					}
					i = k;
					j = l;
					while (CurPosition[i][j + 1] == EMPTY && QueenmoveBlack[i][j + 1] == 0)
					{
						QueenmoveBlack[i][j + 1] = n + 1;
						j++;
					}
					i = k;
					j = l;
					while (CurPosition[i + 1][j + 1] == EMPTY && QueenmoveBlack[i + 1][j + 1] == 0)
					{
						QueenmoveBlack[i + 1][j + 1] = n + 1;
						i++;
						j++;
					}
					i = k;
					j = l;
					while (CurPosition[i + 1][j] == EMPTY && QueenmoveBlack[i + 1][j] == 0)
					{
						QueenmoveBlack[i + 1][j] = n + 1;
						i++;
					}
					i = k;
					j = l;
					while (CurPosition[i + 1][j - 1] == EMPTY && QueenmoveBlack[i + 1][j - 1] == 0)
					{
						QueenmoveBlack[i = 1][j - 1] = n + 1;
						i++;
						j--;
					}
				}
				if (QueenmoveWhite[k][l] == n)//����
				{
					i = k;
					j = l;
					while (CurPosition[i][j - 1] == EMPTY && QueenmoveWhite[i][j - 1] == 0)
					{
						QueenmoveWhite[i][j - 1] = n + 1;
						j--;
					}
					i = k;
					j = l;
					while (CurPosition[i - 1][j - 1] == EMPTY && QueenmoveWhite[i - 1][j - 1] == 0)
					{
						QueenmoveWhite[i - 1][j - 1] = n + 1;
						i--;
						j--;
					}
					while (CurPosition[i - 1][j] == EMPTY && QueenmoveWhite[i - 1][j] == 0)
					{
						QueenmoveWhite[i - 1][j] = n + 1;
						i--;
					}
					i = k;
					j = l;
					while (CurPosition[i - 1][j + 1] == EMPTY && QueenmoveWhite[i - 1][j + 1] == 0)
					{
						QueenmoveWhite[i - 1][j + 1] = n + 1;
						i--;
						j++;
					}
					i = k;
					j = l;
					while (CurPosition[i][j + 1] == EMPTY && QueenmoveWhite[i][j + 1] == 0)
					{
						QueenmoveWhite[i][j + 1] = n + 1;
						j++;
					}
					i = k;
					j = l;
					while (CurPosition[i + 1][j + 1] == EMPTY && QueenmoveWhite[i + 1][j + 1] == 0)
					{
						QueenmoveWhite[i + 1][j + 1] = n + 1;
						i++;
						j++;
					}
					i = k;
					j = l;
					while (CurPosition[i + 1][j] == EMPTY && QueenmoveWhite[i + 1][j] == 0)
					{
						QueenmoveWhite[i + 1][j] = n + 1;
						i++;
					}
					i = k;
					j = l;
					while (CurPosition[i + 1][j - 1] == EMPTY && QueenmoveWhite[i + 1][j - 1] == 0)
					{
						QueenmoveWhite[i = 1][j - 1] = n + 1;
						i++;
						j--;
					}
				}
			}
		}
	}
}
/////��������t1////////
void t1account()
{
	t1 = 0;//�ȹ���
	int i, j;

	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			if (CurPosition[i][j] == EMPTY)//ɨ�����̣�ͨ��queenmove�������ϵĿո�Ŀ���Ȩ���бȽ�
			{
				if (QueenmoveBlack[i][j] == QueenmoveWhite[i][j] != 0)//�Ըÿո�Ŀ���Ȩ�����˫�����ܵ���
				{
					t1 = t1 + 0.1;   //��ʱ�Ըÿո�Ŀ���Ȩ�������巽����ֵ��-1��1֮�䣬�������巽�����ƣ����Խ��е������ڷ�����
				}
				if (QueenmoveWhite[i][j] < QueenmoveBlack[i][j])//�׷�����ÿո�Ĳ�������
				{
					if (QueenmoveWhite[i][j] == 0)   //�׷�����ȥ
					{
						t1 = t1 + 1;     //���ڷ���һ��
					}
					if (QueenmoveWhite[i][j] != 0)
					{
						t1 = t1 - 1;
					}
				}
				if (QueenmoveWhite[i][j] > QueenmoveBlack[i][j])    //�ڷ�����ÿո�Ĳ�������
				{
					if (QueenmoveBlack[i][j] == 0)//�ڷ�����ȥ
					{
						t1 = t1 - 1;  //���ڷ���һ��
					}
					if (QueenmoveBlack[i][j] != 0)
					{
						t1 = t1 + 1;
					}
				}
			}
		}
	}
}
/////��������t2////////
void t2account()//����kingmove,��t1����ԭ������
{
	t2 = 0;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (CurPosition[i][j] == EMPTY)
			{
				if (KingmoveBlack[i][j] == KingmoveWhite[i][j] != 0)
				{
					t2 = t2 + 0.1;
				}
				if (KingmoveWhite[i][j] < KingmoveBlack[i][j])//�׷�����ÿո�������
				{
					if (KingmoveWhite[i][j] == 0)
					{
						t2 = t2 + 1;  //���ڷ���һ��
					}
					if (KingmoveWhite[i][j] != 0)
					{
						t2 = t2 - 1;
					}
				}
				if (KingmoveBlack[i][j] < KingmoveWhite[i][j])//�ڷ�����ÿո�Ĳ�������
				{
					if (KingmoveBlack[i][j] == 0)//�ڷ�����ȥ
					{
						t2 = t2 - 1;  //�ڷ���һ��
					}
					if (KingmoveBlack[i][j] != 0)
					{
						t2 = t2 + 1;
					}
				}
			}
		}
	}
}
/////��������C1////////
void c1account()//���ݹ�ʽ���м���
{
	c1 = 0;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (CurPosition[i][j] == EMPTY)
			{
				if (QueenmoveBlack[i][j] != 0 && QueenmoveWhite[i][j] != 0)
				{
					c1 = c1 + pow((double)2, -(QueenmoveBlack[i][j])) - pow((double)2, -(QueenmoveWhite[i][j]));
				}
				if (QueenmoveBlack[i][j] != 0 && QueenmoveWhite[i][j] == 0)
				{
					c1 = c1 + pow((double)2, -(QueenmoveBlack[i][j]));
				}
				if (QueenmoveBlack[i][j] == 0 && QueenmoveWhite[i][j] != 0)
				{
					c1 = c1 - pow((double)2, -(QueenmoveWhite[i][j]));
				}
			}
		}
	}
	c1 = c1 * 2;
}
/////��������C2////////
void c2account()
{
	c2 = 0;
	double a = 0;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (CurPosition[i][j] == EMPTY)
			{
				if (KingmoveBlack[i][j] != 0 && KingmoveWhite[i][j] != 0)
				{
					a = KingmoveWhite[i][j] - KingmoveBlack[i][j];
					c2 = c2 + MIN(1.0, (double)MAX(-1.0, a / 6.0));
				}
				if (KingmoveBlack[i][j] != 0 && KingmoveWhite[i][j] == 0)
				{
					c2 = c2 + 1;
				}
				if (KingmoveBlack[i][j] == 0 && KingmoveWhite[i][j] != 0)
				{
					c2 = c2 - 1;
				}
			}
		}
	}
}
///////����ո������/////
void MobilitySearch()
{
	int i, j;
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			Mobility[i][j] = 0;
		}
	}
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			if (CurPosition[i][j] == EMPTY)
			{
				if (CurPosition[i][j - 1] == EMPTY)
					Mobility[i][j] += 1;
				if (CurPosition[i - 1][j - 1] == EMPTY)
					Mobility[i][j] += 1;
				if (CurPosition[i - 1][j] == EMPTY)
					Mobility[i][j] += 1;
				if (CurPosition[i - 1][j + 1] == EMPTY)
					Mobility[i][j] += 1;
				if (CurPosition[i][j + 1] == EMPTY)
					Mobility[i][j] += 1;
				if (CurPosition[i + 1][j + 1] == EMPTY)
					Mobility[i][j] += 1;
				if (CurPosition[i + 1][j] == EMPTY)
					Mobility[i][j] += 1;
				if (CurPosition[i + 1][j - 1] == EMPTY)
					Mobility[i][j] += 1;
			}
		}
	}
}
//////����ÿ�����ӵ�����//////
void aaccount()
{
	register int k, l, m, i, j;
	register int n = 0;
	register int h = 0;
	aWhite[4] = { 0 };//�洢ÿ������ͨ��queenMove��õ�����
	aBlack[4] = { 0 };
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			if (CurPosition[i][j] == BLACKCHESS)//�ҵ�һ������
			{
				k = i;
				l = j;
				m = 1;
				while (CurPosition[k][l - 1] == EMPTY && QueenmoveBlack[k][l - 1] != 0)
				{
					aBlack[n] = aBlack[n] + Mobility[k][l - 1] / m;
					l--;
					m = m + 1;
				}
				k = i;
				l = j;
				m = 1;
				while (CurPosition[k - 1][l - 1] == EMPTY && QueenmoveBlack[k - 1][l - 1] != 0)
				{
					aBlack[n] = aBlack[n] + Mobility[k - 1][l - 1] / m;
					k--;
					l--;
					m = m + 1;
				}
				k = i;
				l = j;
				m = 1;
				while (CurPosition[k - 1][l] == EMPTY && QueenmoveBlack[k - 1][l] != 0)
				{
					aBlack[n] = aBlack[n] + Mobility[k - 1][l] / m;
					k--;
					m = m + 1;
				}
				k = i;
				l = j;
				m = 1;
				while (CurPosition[k - 1][l + 1] == EMPTY && QueenmoveBlack[k - 1][l + 1] != 0)
				{
					aBlack[n] = aBlack[n] + Mobility[k - 1][l + 1] / m;
					k--;
					l++;
					m = m + 1;
				}
				k = i;
				l = j;
				m = 1;
				while (CurPosition[k][l + 1] == EMPTY && QueenmoveBlack[k][l + 1] != 0)
				{
					aBlack[n] = aBlack[n] + Mobility[k][l + 1] / m;
					l++;
					m = m + 1;
				}
				k = i;
				l = j;
				m = 1;
				while (CurPosition[k + 1][l + 1] == EMPTY && QueenmoveBlack[k + 1][l + 1] != 0)
				{
					aBlack[n] = aBlack[n] + Mobility[k + 1][l + 1] / m;
					k++;
					l++;
					m = m + 1;
				}
				k = i;
				l = j;
				m = 1;
				while (CurPosition[k + 1][l] == EMPTY && QueenmoveBlack[k + 1][l] != 0)
				{
					aBlack[n] = aBlack[n] + Mobility[k + 1][l] / m;
					k++;
					m = m + 1;
				}
				k = i;
				l = j;
				m = 1;
				while (CurPosition[k + 1][l - 1] == EMPTY && QueenmoveBlack[k + 1][l - 1] != 0)
				{
					aBlack[n] = aBlack[n] + Mobility[k + 1][l - 1] / m;
					k++;
					l--;
					m = m + 1;
				}
				n++;
			}
			if (CurPosition[i][j] == WHITECHESS)//�ҵ�����
			{
				k = i;
				l = j;
				m = 1;
				while (CurPosition[k][l - 1] == EMPTY && QueenmoveWhite[k][l - 1] != 0)
				{
					aWhite[h] = aWhite[h] + Mobility[k][l - 1] / m;
					l--;
					m = m + 1;
				}
				k = i;
				l = j;
				m = 1;
				while (CurPosition[k - 1][l - 1] == EMPTY && QueenmoveWhite[k - 1][l - 1] != 0)
				{
					aWhite[h] = aWhite[h] + Mobility[k - 1][l - 1] / m;
					k--;
					l--;
					m = m + 1;
				}
				k = i;
				l = j;
				m = 1;
				while (CurPosition[k - 1][l] == EMPTY && QueenmoveWhite[k - 1][l] != 0)
				{
					aWhite[h] = aWhite[h] + Mobility[k - 1][l] / m;
					k--;
					m = m + 1;
				}
				k = i;
				l = j;
				m = 1;
				while (CurPosition[k - 1][l + 1] == EMPTY && QueenmoveWhite[k - 1][l + 1] != 0)
				{
					aWhite[h] = aWhite[h] + Mobility[k - 1][l + 1] / m;
					k--;
					l++;
					m = m + 1;
				}
				k = i;
				l = j;
				m = 1;
				while (CurPosition[k][l + 1] == EMPTY && QueenmoveWhite[k][l + 1] != 0)
				{
					aWhite[h] = aWhite[h] + Mobility[k][l + 1] / m;
					l++;
					m = m + 1;
				}
				k = i;
				l = j;
				m = 1;
				while (CurPosition[k + 1][l + 1] == EMPTY && QueenmoveWhite[k + 1][l + 1] != 0)
				{
					aWhite[h] = aWhite[h] + Mobility[k + 1][l + 1] / m;
					k++;
					l++;
					m = m + 1;
				}
				k = i;
				l = j;
				m = 1;
				while (CurPosition[k + 1][l] == EMPTY && QueenmoveWhite[k + 1][l] != 0)
				{
					aWhite[h] = aWhite[h] + Mobility[k + 1][l] / m;
					k++;
					m = m + 1;
				}
				k = i;
				l = j;
				m = 1;
				while (CurPosition[k + 1][l - 1] == EMPTY && QueenmoveWhite[k + 1][l - 1] != 0)
				{
					aWhite[h] = aWhite[h] + Mobility[k + 1][l - 1] / m;
					k++;
					l--;
					m = m + 1;
				}
				h++;
			}
		}
	}
}
//////����W����//////
void waccount()/////���㹫ʽ///////
{
	w = 0;
	int i, j;
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			if (CurPosition[i][j] == EMPTY)
			{
				if (QueenmoveBlack[i][j] != 0 && QueenmoveWhite[i][j] != 0)
				{
					w = w + pow(2, -(fabs((double)(QueenmoveBlack[i][j] - QueenmoveWhite[i][j]))));
				}
			}
		}
	}
}
/////����S����///////
void saccount()
{
	s = 0;
	int M1, M2, N1, N2, i, j;
	M1 = M2 = N1 = N2 = 0;
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			if (CurPosition[i][j] == EMPTY)
			{
				if (QueenmoveBlack[i][j] < QueenmoveWhite[i][j])
				{
					if (QueenmoveBlack[i][j] == 0)
					{
						M2++;
						N2 += Mobility[i][j];
					}
					else
					{
						M1++;
						N1 += Mobility[i][j];
					}
				}
				if (QueenmoveBlack[i][j] > QueenmoveWhite[i][j])
				{
					if (QueenmoveWhite[i][j] == 0)
					{
						M1++;
						N1 += Mobility[i][j];
					}
					else
					{
						M2++;
						N2 += Mobility[i][j];
					}
				}
			}
		}
	}
	double s1 = M2 - M1;
	double s2 = N1 - N2;
	s = s1 / 1000 + s2 / 10000;
}
//////�������վ��������/////
double evaluateAll()//�д��Ľ�
{
	double Value;
	//����KingMove��QueenMove����
	SearchKingMove();
	SearchQueenMove();
	MobilitySearch();
	/////�����������ֵ//////
	t1account();
	t2account();
	c1account();
	c2account();
	//saccount();
	//////����Ȩ��////////
	waccount();
	double a = (17 / (w + 17));
	double b = (w / (w + 49.03));
	double c = (1 - (a + b)) / 2;
	Value = a * t1 + b * t2 / 2 + c * ((c1 + c2) / 2);
	return Value;
}