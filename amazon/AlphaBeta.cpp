#include"AlphaBeta.h"

int mode = 0;
int a_step = 0;
int SearchDepth = 2 ;   //��������
int CurPosition[12][12] = { 0 };   //��ʵ�ʲ��������̸��Ƶ��������������Ͻ���ģ�����������
CHESSMOVE BestMove = { 0 };

//��CurPosition���в���
void MakeMove(CHESSMOVE* move)//ģ������
{
	CurPosition[move->From.x][move->From.y] = EMPTY;
	CurPosition[move->To.x][move->To.y] = move->ChessID;
	CurPosition[move->Bar.x][move->Bar.y] = BARRIER;
}

void UndoMakeMove(CHESSMOVE* move)//����ģ������
{
	CurPosition[move->Bar.x][move->Bar.y] = EMPTY;
	CurPosition[move->To.x][move->To.y] = EMPTY;
	CurPosition[move->From.x][move->From.y] = move->ChessID;
}

//������Ѳ���
void SearchAGoodMove(int Board[12][12], int computerSide)   //����һ��12*12�Ķ�ά����
{
	if (computerSide == BLACK) 
		mode = 1;
	else 
		mode = 0;
	memcpy(CurPosition, Board, 144 * sizeof(int));   //���ƴ����Board���̵�CurPosition
	AlphaBetaSearch(SearchDepth);    //��һ�������������õ��������
	MakeMove(&BestMove);
	memcpy(Board, CurPosition, 144 * sizeof(int));
	a_step = 0;
}

//���¼�֦�㷨��������
double AlphaBetaSearch(int depth, double alpha, double beta)
{
	double score = 0;   //������������
	int type = 0;
	//evaluationfunction ev;
	if (JudgeWin(CurPosition) != 0){//�ֳ�ʤ��
		//return ev.evaluation(CurPosition);//��������ֵ
		return evaluateAll();
	}
	if (depth == 0)//����Ҷ�ӽڵ�
	{
		if ((SearchDepth - depth) % 2 == 0){//����ֵ���
			if (mode == 1)
				//return ev.evaluation(CurPosition);
				return evaluateAll();
			if (mode == 0)
				//return -ev.evaluation(CurPosition);
				return -evaluateAll();
		}
		else{
			if (mode == 1){
				//return -ev.evaluation(CurPosition);
				return -evaluateAll();
			}
			if (mode == 0){
				//return ev.evaluation(CurPosition);
				return evaluateAll();
			}
		}
	}
	a_step = a_step + 1;  //ÿ����һ�������ֽ�����һ��
	switch (mode)
	{
	case 1:
		if (a_step % 2 == 1)//������
		{
			type = mode + 1;
		}
		else if (a_step % 2 == 0)
		{
			type = mode;
		}
		break;
	case 0:
		if (a_step % 2 == 1)  //������
		{
			type = mode + 1;
		}
		else if (a_step % 2 == 0)  //ż����
		{
			type = mode + 2;
		}
		break;
	default:
		break;
	}
	int count = getPossibleMove(CurPosition, depth, type);  //��¼�����������������з��Ϲ���Ĳ���
	for (int i = 0; i < count; i++)
	{
		MakeMove(&MoveList[depth][i]);            //ģ�����壬��CurPosition��ģ��
		score = -AlphaBetaSearch(depth - 1, -beta, -alpha);   //�ݹ���������
		UndoMakeMove(&MoveList[depth][i]);              //����ģ������
		if (score > alpha)
		{
			alpha = score;
			if (depth == SearchDepth) BestMove = MoveList[depth][i];
		}
		if (alpha >= beta) break;
	}
	return alpha;
}

int JudgeWin(int Board[12][12])
{
	int C_Black = 0, C_White = 0;
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 10; j++)
		{
			if (Board[i][j] == BLACKCHESS && Board[i - 1][j - 1] != EMPTY && Board[i - 1][j] != EMPTY && Board[i - 1][j + 1] != EMPTY && Board[i][j + 1] != EMPTY && Board[i + 1][j + 1] != EMPTY && Board[i + 1][j] != EMPTY && Board[i + 1][j - 1] != EMPTY && Board[i][j - 1] != EMPTY)
				C_Black++;
			else if (Board[i][j] == WHITECHESS && Board[i - 1][j - 1] != EMPTY && Board[i - 1][j] != EMPTY && Board[i - 1][j + 1] != EMPTY && Board[i][j + 1] != EMPTY && Board[i + 1][j + 1] != EMPTY && Board[i + 1][j] != EMPTY && Board[i + 1][j - 1] != EMPTY && Board[i][j - 1] != EMPTY)
				C_White++;
		}
	}
	if (C_Black == 4)
		return BLACKCHESS;
	else if (C_White == 4)
		return WHITECHESS;
	else
		return 0;
}


