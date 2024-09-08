#include"AlphaBeta.h"

int mode = 0;
int a_step = 0;
int SearchDepth = 2 ;   //搜索两层
int CurPosition[12][12] = { 0 };   //将实际操作的棋盘复制到这里，在这个棋盘上进行模拟行棋和评估
CHESSMOVE BestMove = { 0 };

//对CurPosition进行操作
void MakeMove(CHESSMOVE* move)//模拟行棋
{
	CurPosition[move->From.x][move->From.y] = EMPTY;
	CurPosition[move->To.x][move->To.y] = move->ChessID;
	CurPosition[move->Bar.x][move->Bar.y] = BARRIER;
}

void UndoMakeMove(CHESSMOVE* move)//撤销模拟行棋
{
	CurPosition[move->Bar.x][move->Bar.y] = EMPTY;
	CurPosition[move->To.x][move->To.y] = EMPTY;
	CurPosition[move->From.x][move->From.y] = move->ChessID;
}

//搜索最佳步数
void SearchAGoodMove(int Board[12][12], int computerSide)   //传入一个12*12的二维数组
{
	if (computerSide == BLACK) 
		mode = 1;
	else 
		mode = 0;
	memcpy(CurPosition, Board, 144 * sizeof(int));   //复制传入的Board棋盘到CurPosition
	AlphaBetaSearch(SearchDepth);    //第一次搜索传入设置的搜索深度
	MakeMove(&BestMove);
	memcpy(Board, CurPosition, 144 * sizeof(int));
	a_step = 0;
}

//αβ剪枝算法搜索步数
double AlphaBetaSearch(int depth, double alpha, double beta)
{
	double score = 0;   //定义评估分数
	int type = 0;
	//evaluationfunction ev;
	if (JudgeWin(CurPosition) != 0){//分出胜负
		//return ev.evaluation(CurPosition);//返回评估值
		return evaluateAll();
	}
	if (depth == 0)//到达叶子节点
	{
		if ((SearchDepth - depth) % 2 == 0){//极大值结点
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
	a_step = a_step + 1;  //每搜索一层就是棋局进行了一步
	switch (mode)
	{
	case 1:
		if (a_step % 2 == 1)//奇数层
		{
			type = mode + 1;
		}
		else if (a_step % 2 == 0)
		{
			type = mode;
		}
		break;
	case 0:
		if (a_step % 2 == 1)  //奇数层
		{
			type = mode + 1;
		}
		else if (a_step % 2 == 0)  //偶数层
		{
			type = mode + 2;
		}
		break;
	default:
		break;
	}
	int count = getPossibleMove(CurPosition, depth, type);  //记录步法总数，生成所有符合规则的步法
	for (int i = 0; i < count; i++)
	{
		MakeMove(&MoveList[depth][i]);            //模拟行棋，在CurPosition上模拟
		score = -AlphaBetaSearch(depth - 1, -beta, -alpha);   //递归向下搜索
		UndoMakeMove(&MoveList[depth][i]);              //撤销模拟行棋
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


