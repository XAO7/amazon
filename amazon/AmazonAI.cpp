#include"AmazonAI.h"

void AICompute(int Board_10[10][10], int computerSide, Step& step) {

	int Board_12[12][12] = { 0 };
	InitBoard(Board_12);

	//TRANSFORM_10_TO_12
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (Board_10[i][j] == BLACK) {
				Board_12[i + 1][j + 1] = BLACKCHESS;
			}
			else if (Board_10[i][j] == WHITE) {
				Board_12[i + 1][j + 1] = WHITECHESS;
			}
			else if (Board_10[i][j] == BAR) {
				Board_12[i + 1][j + 1] = BARRIER;
			}
			else if (Board_10[i][j] == EMP) {
				Board_12[i + 1][j + 1] = EMPTY;
			}
		}
	}

	//µ÷ÓÃ¦Á¦Â¼ôÖ¦Ëã·¨
	SearchAGoodMove(Board_12, computerSide);

	//TRANSFORM_CHESSMOVE_TO_STEP
	step.start.x = BestMove.From.x-1;
	step.start.y = BestMove.From.y-1;
	step.end.x = BestMove.To.x-1;
	step.end.y = BestMove.To.y-1;
	step.bar.x = BestMove.Bar.x-1;
	step.bar.y = BestMove.Bar.y-1;

	//TRAMSFORM_12_TO_10
//	for (int i = 1; i < 11; i++) {
//		for (int j = 1; j < 11; j++)
//		{
//			if (Board_12[i][j] == BLACKCHESS) {
//				Board_10[i-1][j-1] = BLACK;
//			}
//			else if (Board_12[i][j] == WHITECHESS) {
//				Board_10[i - 1][j - 1] = WHITE;
//			}
//			else if (Board_12[i][j] == BARRIER) {
//				Board_10[i - 1][j - 1] = BAR;
//			}
//			else if (Board_12[i][j] == EMPTY) {
//				Board_10[i - 1][j - 1] = EMP;
//			}
//		}
//	}
}

void InitBoard(int Board[12][12])
{
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (i == 0 || j == 0 || i == 11 || j == 11)
				Board[i][j] = BARRIER;
			else
				Board[i][j] = EMPTY;
		}
	}
}
