#include"AITool.h"

int getWinside(int Board[10][10], Step Book[92]) { //根据最后的棋盘信息和棋谱信息判断胜利方

	bool allFull = true;
	int whiteflag = 0, blackflag = 0;
	int winSide = 4;
	SPosition whiteChess[4];
	SPosition blackChess[4];

	//1.棋盘全部走满的情况下，后手胜
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (Board[i][j] == EMP) {
				allFull = false;
				goto END;
			}
		}
	}
END:;
	if (allFull) return WHITE;
	else {
		//2.判断胜方
		//存储棋盘信息
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (Board[i][j] == WHITE) {
					whiteChess[whiteflag].x = i; whiteChess[whiteflag].y = j;
					whiteflag++;
				}
				else if (Board[i][j] == BLACK) {
					blackChess[blackflag].x = i; blackChess[blackflag].y = j;
					blackflag++;
				}
			}
		}
		bool canWhiteMove = false, canBlackMove = false;
		for (int i = 0; i < 4; i++) {
			if (Board[whiteChess[i].x][whiteChess[i].y - 1] == EMP && whiteChess[i].y - 1 >= 0) canWhiteMove = true;//上
			else if (Board[whiteChess[i].x - 1][whiteChess[i].y] == EMP && whiteChess[i].x - 1 >= 0) canWhiteMove = true;//左
			else if (Board[whiteChess[i].x][whiteChess[i].y + 1] == EMP && whiteChess[i].y + 1 <= 9)  canWhiteMove = true;//下
			else if (Board[whiteChess[i].x + 1][whiteChess[i].y] == EMP && whiteChess[i].x + 1 <= 9)  canWhiteMove = true;//右
			else if (Board[whiteChess[i].x - 1][whiteChess[i].y - 1] == EMP && whiteChess[i].x - 1 >= 0 && whiteChess[i].y - 1 >= 0)  canWhiteMove = true;//左上
			else if (Board[whiteChess[i].x - 1][whiteChess[i].y + 1] == EMP && whiteChess[i].x - 1 >= 0 && whiteChess[i].y + 1 <= 9)  canWhiteMove = true;//左下
			else if (Board[whiteChess[i].x + 1][whiteChess[i].y - 1] == EMP && whiteChess[i].x + 1 <= 9 && whiteChess[i].y - 1 >= 0)  canWhiteMove = true;//右上
			else if (Board[whiteChess[i].x + 1][whiteChess[i].y + 1] == EMP && whiteChess[i].x + 1 <= 9 && whiteChess[i].y + 1 <= 9)  canWhiteMove = true;//右下
		}
		for (int i = 0; i < 4; i++) {
			if (Board[blackChess[i].x][blackChess[i].y - 1] == EMP && blackChess[i].y - 1 >= 0) canBlackMove = true;//上
			else if (Board[blackChess[i].x - 1][blackChess[i].y] == EMP && blackChess[i].x - 1 >= 0) canBlackMove = true;//左
			else if (Board[blackChess[i].x][blackChess[i].y + 1] == EMP && blackChess[i].y + 1 <= 9)  canBlackMove = true;//下
			else if (Board[blackChess[i].x + 1][blackChess[i].y] == EMP && blackChess[i].x + 1 <= 9)  canBlackMove = true;//右
			else if (Board[blackChess[i].x - 1][blackChess[i].y - 1] == EMP && blackChess[i].x - 1 >= 0 && blackChess[i].y - 1 >= 0)  canBlackMove = true;//左上
			else if (Board[blackChess[i].x - 1][blackChess[i].y + 1] == EMP && blackChess[i].x - 1 >= 0 && blackChess[i].y + 1 <= 9)  canBlackMove = true;//左下
			else if (Board[blackChess[i].x + 1][blackChess[i].y - 1] == EMP && blackChess[i].x + 1 <= 9 && blackChess[i].y - 1 >= 0)  canBlackMove = true;//右上
			else if (Board[blackChess[i].x + 1][blackChess[i].y + 1] == EMP && blackChess[i].x + 1 <= 9 && blackChess[i].y + 1 <= 9)  canBlackMove = true;//右下
		}
		if (canWhiteMove == false) {
			return BLACK;
		}
		if (canBlackMove == false) {
			return WHITE;
		}
		else return BLACK;
	}
}

bool CanMoveOrShoot(int plate[10][10], SPosition posFrom, SPosition posTo)//判断走棋或者防止障碍是否合法
{
	//printf("judge  %c%c %c%c\n", posFrom.x + 'A', posFrom.y + 'A', posTo.x + 'A', posTo.y + 'A');

	int fromX = posFrom.x;
	int fromY = posFrom.y;
	int toX = posTo.x;
	int toY = posTo.y;
	int k;

	if (plate[toX][toY] != EMP) {
		//printf("not empty\n");
		return false;
	}
	else if (fromX == toX && toY == fromY) {
		//printf("no move\n");
		return false;
	}//原地动棋
	else if (fromX == toX) k = 0;//在垂直方向上
	else if (fromY == toY) k = 1;//在水平方向上
	else if (toX - fromX == toY - fromY) k = 2;//在左上右下斜线上
	else if (fromX - toX == toY - fromY) k = 3;//在左下右上斜线上
	else {
		//printf("invaild move\n");
		return false;
	}
	switch (k)
	{
	case 0:///////////////////////////////////////////////////////垂直方向
		if (toY > fromY) {//下
			for (int i = fromY + 1; i < toY; i++) {
				if (plate[fromX][i] != EMP) {
					//printf("down error\n");
					return false;
				}
			}
		}
		else if (toY < fromY) {//上
			for (int i = fromY - 1; i > toY; i--) {
				if (plate[fromX][i] != EMP) {
					//printf("up error\n");
					return false;
				}
			}
		}
		else return true;
	case 1:////////////////////////////////////////////////////水平方向
		if (toX > fromX) {//右
			for (int i = fromX + 1; i < toX; i++) {
				if (plate[i][fromY] != EMP) {
					//printf("right error\n");
					return false;
				}
			}
		}
		else if (toX < fromX) {//左
			for (int i = fromX - 1; i > toX; i--) {
				if (plate[i][fromY] != EMP) {
					//printf("left error\n");
					return false;
				}
			}
		}
		else return true;
	case 2://////////////////////////////////////////////////左上右下斜线
		if (toX < fromX) {//左上
			for (int i = fromX - 1, j = fromY - 1; i > toX && j > toY; i--, j--) {
				if (plate[i][j] != EMP) {
					//printf("left up error\n");
					return false;
				}
			}
		}
		else if (toX > fromX) {//右下
			for (int i = fromX + 1, j = fromY + 1; i < toX && j < toY; i++, j++) {
				if (plate[i][j] != EMP) {
					//printf("right down error\n");
					return false;
				}
			}
		}
		else return true;
	case 3://////////////////////////////////////////////////左下右上斜线
		if (toY > fromY) {//左下
			for (int i = fromX - 1, j = fromY + 1; i > toX && j < toY; i--, j++) {
				if (plate[i][j] != EMP) {
					//printf("left down error\n");
					return false;
				}
			}
		}
		else if (toY < fromY) {//右上
			for (int i = fromX + 1, j = fromY - 1; i < toX && j > toY; i++, j--) {
				if (plate[i][j] != EMP) {
					//printf("right up error\n");
					return false;
				}
			}
		}
		else return true;
	default:
		return true;
	}
}

void AICompute_TEST(   //测试AI
	int Board[10][10],			//棋盘数据
	int computerSide,       //是否是作为玩家1进行计算，否则作为玩家2进行计算
	Step& final_step)
{

	SPosition  outPosSelected;	//选择输出着子
	SPosition  outPosMoveTo;//选择走子位置
	SPosition  outPosShootAt;	//选择放置障碍位置

	//遍历计算每个棋子的所有走法的总权值

	//解析棋盘
	//存放己方执棋信息
	SPosition chess[4];
	int count = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
		{
			if (Board[i][j] == computerSide) {
				chess[count].x = i; chess[count].y = j; count++;
			}
		}
	}
	Step temp_steps[4];
	//分别计算出四个棋子的最佳走法，存入相应序号的位置
	for (int i = 0; i < 4; i++) {
		outPosSelected = chess[i];
		int moveStep = 1;
		/////////////////////////////////////探测向上方向//////////////////////////////////
		outPosMoveTo.x = outPosSelected.x;
		while (true) {
			if (outPosSelected.y - moveStep < 0) {
				moveStep = 1;
				break;
			}
			else
			{
				outPosMoveTo.y = outPosSelected.y - moveStep;
				if (CanMoveOrShoot(Board, outPosSelected, outPosMoveTo)) {
					double tempValue = ValueOfStep(Board, computerSide, outPosSelected, outPosMoveTo, outPosShootAt);//获取该步骤的权值
					if (tempValue >= temp_steps[i].value) {
						temp_steps[i].value = tempValue; //更新最终权值
						temp_steps[i].start = outPosSelected; temp_steps[i].end = outPosMoveTo; temp_steps[i].bar = outPosShootAt;
					}
					moveStep++;//更新步长
				}
				else {
					moveStep = 1;
					break;
				}
			}
		}
		/////////////////////////////////////探测向下方向//////////////////////////////////
		outPosMoveTo.x = outPosSelected.x;
		while (true) {
			if (outPosSelected.y + moveStep > 9) {
				moveStep = 1;
				break;
			}
			else
			{
				outPosMoveTo.y = outPosSelected.y + moveStep;
				if (CanMoveOrShoot(Board, outPosSelected, outPosMoveTo)) {
					double tempValue = ValueOfStep(Board, computerSide, outPosSelected, outPosMoveTo, outPosShootAt);//获取该步骤的权值
					if (tempValue >= temp_steps[i].value) {
						temp_steps[i].value = tempValue; //更新最终权值
						temp_steps[i].start = outPosSelected; temp_steps[i].end = outPosMoveTo; temp_steps[i].bar = outPosShootAt;
					}
					moveStep++;
				}
				else {
					moveStep = 1;
					break;
				}
			}
		}
		/////////////////////////////////////探测向左方向//////////////////////////////////
		outPosMoveTo.y = outPosSelected.y;
		while (true) {
			if (outPosSelected.x - moveStep < 0) {
				moveStep = 1;
				break;
			}
			else
			{
				outPosMoveTo.x = outPosSelected.x - moveStep;
				if (CanMoveOrShoot(Board, outPosSelected, outPosMoveTo)) {
					double tempValue = ValueOfStep(Board, computerSide, outPosSelected, outPosMoveTo, outPosShootAt);//获取该步骤的权值
					if (tempValue >= temp_steps[i].value) {
						temp_steps[i].value = tempValue; //更新最终权值
						temp_steps[i].start = outPosSelected; temp_steps[i].end = outPosMoveTo; temp_steps[i].bar = outPosShootAt;
					}
					moveStep++;
				}
				else {
					moveStep = 1;
					break;
				}
			}
		}
		/////////////////////////////////////探测向右方向//////////////////////////////////
		outPosMoveTo.y = outPosSelected.y;
		while (true) {
			if (outPosSelected.x + moveStep > 9) {
				moveStep = 1;
				break;
			}
			else
			{
				outPosMoveTo.x = outPosSelected.x + moveStep;
				if (CanMoveOrShoot(Board, outPosSelected, outPosMoveTo)) {
					double tempValue = ValueOfStep(Board, computerSide, outPosSelected, outPosMoveTo, outPosShootAt);//获取该步骤的权值
					if (tempValue >= temp_steps[i].value) {
						temp_steps[i].value = tempValue; //更新最终权值
						temp_steps[i].start = outPosSelected; temp_steps[i].end = outPosMoveTo; temp_steps[i].bar = outPosShootAt;
					}
					moveStep++;
				}
				else {
					moveStep = 1;
					break;
				}
			}
		}
		/////////////////////////////////////探测向左上方向//////////////////////////////////
		while (true) {
			if (outPosSelected.x - moveStep < 0 || outPosSelected.y - moveStep < 0) {
				moveStep = 1;
				break;
			}
			else
			{
				outPosMoveTo.x = outPosSelected.x - moveStep;
				outPosMoveTo.y = outPosSelected.y - moveStep;
				if (CanMoveOrShoot(Board, outPosSelected, outPosMoveTo)) {
					double tempValue = ValueOfStep(Board, computerSide, outPosSelected, outPosMoveTo, outPosShootAt);//获取该步骤的权值
					if (tempValue >= temp_steps[i].value) {
						temp_steps[i].value = tempValue; //更新最终权值
						temp_steps[i].start = outPosSelected; temp_steps[i].end = outPosMoveTo; temp_steps[i].bar = outPosShootAt;
					}
					moveStep++;
				}
				else {
					moveStep = 1;
					break;
				}
			}
		}
		/////////////////////////////////////探测向左下方向//////////////////////////////////
		while (true) {
			if (outPosSelected.x - moveStep < 0 || outPosSelected.y + moveStep > 9) {
				moveStep = 1;
				break;
			}
			else
			{
				outPosMoveTo.x = outPosSelected.x - moveStep;
				outPosMoveTo.y = outPosSelected.y + moveStep;
				if (CanMoveOrShoot(Board, outPosSelected, outPosMoveTo)) {
					double tempValue = ValueOfStep(Board, computerSide, outPosSelected, outPosMoveTo, outPosShootAt);//获取该步骤的权值
					if (tempValue >= temp_steps[i].value) {
						temp_steps[i].value = tempValue; //更新最终权值
						temp_steps[i].start = outPosSelected; temp_steps[i].end = outPosMoveTo; temp_steps[i].bar = outPosShootAt;
					}
					moveStep++;
				}
				else {
					moveStep = 1;
					break;
				}
			}
		}
		/////////////////////////////////////探测向右上方向//////////////////////////////////
		while (true) {
			if (outPosSelected.x + moveStep > 9 || outPosSelected.y - moveStep < 0) {
				moveStep = 1;
				break;
			}
			else
			{
				outPosMoveTo.x = outPosSelected.x + moveStep;
				outPosMoveTo.y = outPosSelected.y - moveStep;
				if (CanMoveOrShoot(Board, outPosSelected, outPosMoveTo)) {
					double tempValue = ValueOfStep(Board, computerSide, outPosSelected, outPosMoveTo, outPosShootAt);//获取该步骤的权值
					if (tempValue >= temp_steps[i].value) {
						temp_steps[i].value = tempValue; //更新最终权值
						temp_steps[i].start = outPosSelected; temp_steps[i].end = outPosMoveTo; temp_steps[i].bar = outPosShootAt;
					}
					moveStep++;
				}
				else {
					moveStep = 1;
					break;
				}
			}
		}
		/////////////////////////////////////探测向右下方向//////////////////////////////////
		while (true) {
			if (outPosSelected.x + moveStep > 9 || outPosSelected.y + moveStep > 9) {
				moveStep = 1;
				break;
			}
			else
			{
				outPosMoveTo.x = outPosSelected.x + moveStep;
				outPosMoveTo.y = outPosSelected.y + moveStep;
				if (CanMoveOrShoot(Board, outPosSelected, outPosMoveTo)) {
					double tempValue = ValueOfStep(Board, computerSide, outPosSelected, outPosMoveTo, outPosShootAt);//获取该步骤的权值
					if (tempValue >= temp_steps[i].value) {
						temp_steps[i].value = tempValue; //更新最终权值
						temp_steps[i].start = outPosSelected; temp_steps[i].end = outPosMoveTo; temp_steps[i].bar = outPosShootAt;
					}
					moveStep++;
				}
				else {
					moveStep = 1;
					break;
				}
			}
		}
		//如果八个方向都不能走，将value值置为一个负的随机数
		if (temp_steps[i].start.x == 4 && temp_steps[i].start.y == 4 && temp_steps[i].end.x == 4 && temp_steps[i].end.y == 4 && temp_steps[i].bar.x == 4 && temp_steps[i].bar.y == 4) {
			temp_steps[i].value = -1 * rand();
		}
	}

	//printf("%f/%f/%f/%f\n", temp_steps[0].value, temp_steps[1].value, temp_steps[2].value, temp_steps[3].value);

	/////////////////////比较出最好的走法///////////////////////
	int flag = 0;
	double max = 0;
	for (int i = 0; i < 4; i++) {
		if (temp_steps[i].value >= max) {
			max = temp_steps[i].value;
			flag = i;
		}
	}

	//printf("%f %d\n", max, flag);

	final_step.start.x = temp_steps[flag].start.x; final_step.start.y = temp_steps[flag].start.y;
	final_step.end.x = temp_steps[flag].end.x; final_step.end.y = temp_steps[flag].end.y;
	final_step.bar.x = temp_steps[flag].bar.x; final_step.bar.y = temp_steps[flag].bar.y;
	//printf("move %c%c%c%c%c%c\n", temp_step.start.x + 'A', temp_step.start.y + 'A', temp_step.end.x + 'A', temp_step.end.y + 'A', temp_step.bar.x + 'A', temp_step.bar.y + 'A');

	return;
}

void printBoard(int Board[10][10]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
			cout << Board[j][i];
		cout << '\n';
	}
}

double ValueOfStep(int Board[10][10], int computerSide, SPosition outPosSelected, SPosition outPosMoveTo, SPosition& outPosShootAt) {

	//将棋盘信息拷贝一次
	int Board_copy[10][10];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
		{
			Board_copy[i][j] = Board[i][j];
		}
	}
	//修改棋盘信息
	Board_copy[outPosSelected.x][outPosSelected.y] = EMP;
	Board_copy[outPosMoveTo.x][outPosMoveTo.y] = computerSide;

	//存放临时最终步数
	Step temp_final_step;
	temp_final_step.start.x = outPosSelected.x; temp_final_step.start.y = outPosSelected.y; temp_final_step.end.x = outPosMoveTo.x; temp_final_step.end.y = outPosMoveTo.y;
	temp_final_step.value = 0;

	//探测八个方向上可以放障碍的位置
	int move_step = 1;
	SPosition new_bar;

	//////////////////////////////////向上/////////////////////////////////
	while (true) {
		if (outPosMoveTo.y - move_step < 0) {
			move_step = 1;
			break;
		}
		else {
			//生成障碍位置
			new_bar.y = outPosMoveTo.y - move_step;
			new_bar.x = outPosMoveTo.x;
			if (CanMoveOrShoot(Board_copy, outPosMoveTo, new_bar)) {
				//修改临时棋盘信息
				Board_copy[new_bar.x][new_bar.y] = BAR;
				//获取该情况走法的权值
				double value = ValueOfShoot(Board_copy, temp_final_step.end, new_bar);
				if (value >= temp_final_step.value) {
					temp_final_step.value = value; //更新最终权值
					temp_final_step.bar.x = new_bar.x; temp_final_step.bar.y = new_bar.y;
				}
				move_step++;
				//还原临时棋盘信息
				Board_copy[new_bar.x][new_bar.y] = EMP;
			}
			else {
				move_step = 1;
				break;
			}
		}
	}
	//////////////////////////////////向下/////////////////////////////////

	while (true) {
		if (outPosMoveTo.y + move_step > 9) {
			move_step = 1;
			break;
		}
		else {
			//生成障碍位置
			new_bar.y = outPosMoveTo.y + move_step;
			new_bar.x = outPosMoveTo.x;
			if (CanMoveOrShoot(Board_copy, outPosMoveTo, new_bar)) {
				//修改临时棋盘信息
				Board_copy[new_bar.x][new_bar.y] = BAR;
				//获取该情况走法的权值
				double value = ValueOfShoot(Board_copy, temp_final_step.end, new_bar);
				if (value >= temp_final_step.value) {
					temp_final_step.value = value; //更新最终权值
					temp_final_step.bar.x = new_bar.x; temp_final_step.bar.y = new_bar.y;
				}
				move_step++;
				//还原临时棋盘信息
				Board_copy[new_bar.x][new_bar.y] = EMP;
			}
			else {
				move_step = 1;
				break;
			}
		}
	}
	//////////////////////////////////向左/////////////////////////////////

	while (true) {
		if (outPosMoveTo.x - move_step < 0) {
			move_step = 1;
			break;
		}
		else {
			//生成障碍位置
			new_bar.x = outPosMoveTo.x - move_step;
			new_bar.y = outPosMoveTo.y;

			if (CanMoveOrShoot(Board_copy, outPosMoveTo, new_bar)) {
				//修改临时棋盘信息
				Board_copy[new_bar.x][new_bar.y] = BAR;
				//获取该情况走法的权值
				double value = ValueOfShoot(Board_copy, temp_final_step.end, new_bar);
				if (value >= temp_final_step.value) {
					temp_final_step.value = value; //更新最终权值
					temp_final_step.bar.x = new_bar.x; temp_final_step.bar.y = new_bar.y;
				}
				move_step++;
				//还原临时棋盘信息
				Board_copy[new_bar.x][new_bar.y] = EMP;
			}
			else {
				move_step = 1;
				break;
			}
		}
	}
	//////////////////////////////////向右/////////////////////////////////

	while (true) {
		if (outPosMoveTo.x + move_step > 9) {
			move_step = 1;
			break;
		}
		else {
			//生成障碍位置
			new_bar.x = outPosMoveTo.x + move_step;
			new_bar.y = outPosMoveTo.y;

			if (CanMoveOrShoot(Board_copy, outPosMoveTo, new_bar)) {
				//修改临时棋盘信息
				Board_copy[new_bar.x][new_bar.y] = BAR;
				//获取该情况走法的权值
				double value = ValueOfShoot(Board_copy, temp_final_step.end, new_bar);
				if (value >= temp_final_step.value) {
					temp_final_step.value = value; //更新最终权值
					temp_final_step.bar.x = new_bar.x; temp_final_step.bar.y = new_bar.y;
				}
				move_step++;
				//还原临时棋盘信息
				Board_copy[new_bar.x][new_bar.y] = EMP;
			}
			else {
				move_step = 1;
				break;
			}
		}
	}
	//////////////////////////////////向左上/////////////////////////////////
	while (true) {
		if (outPosMoveTo.x - move_step < 0 || outPosMoveTo.y - move_step < 0) {
			move_step = 1;
			break;
		}
		else {
			//生成障碍位置

			new_bar.x = outPosMoveTo.x - move_step;
			new_bar.y = outPosMoveTo.y - move_step;

			if (CanMoveOrShoot(Board_copy, outPosMoveTo, new_bar)) {
				//修改临时棋盘信息
				Board_copy[new_bar.x][new_bar.y] = BAR;
				//获取该情况走法的权值
				double value = ValueOfShoot(Board_copy, temp_final_step.end, new_bar);
				if (value >= temp_final_step.value) {
					temp_final_step.value = value; //更新最终权值
					temp_final_step.bar.x = new_bar.x; temp_final_step.bar.y = new_bar.y;
				}
				move_step++;
				//还原临时棋盘信息
				Board_copy[new_bar.x][new_bar.y] = EMP;
				new_bar.x = 0; new_bar.y = 0;
			}
			else {
				move_step = 1;
				break;
			}
		}
	}
	//////////////////////////////////向左下/////////////////////////////////
	while (true) {
		if (outPosMoveTo.x - move_step < 0 || outPosMoveTo.y + move_step > 9) {
			move_step = 1;
			break;
		}
		else {
			//生成障碍位置

			new_bar.x = outPosMoveTo.x - move_step;
			new_bar.y = outPosMoveTo.y + move_step;

			if (CanMoveOrShoot(Board_copy, outPosMoveTo, new_bar)) {
				//修改临时棋盘信息
				Board_copy[new_bar.x][new_bar.y] = BAR;
				//获取该情况走法的权值
				double value = ValueOfShoot(Board_copy, temp_final_step.end, new_bar);
				if (value >= temp_final_step.value) {
					temp_final_step.value = value; //更新最终权值
					temp_final_step.bar.x = new_bar.x; temp_final_step.bar.y = new_bar.y;
				}
				move_step++;
				//还原临时棋盘信息
				Board_copy[new_bar.x][new_bar.y] = EMP;
			}
			else {
				move_step = 1;
				break;
			}
		}
	}
	//////////////////////////////////向右上/////////////////////////////////
	while (true) {
		if (outPosMoveTo.x + move_step > 9 || outPosMoveTo.y - move_step < 0) {
			move_step = 1;
			break;
		}
		else {
			//生成障碍位置

			new_bar.x = outPosMoveTo.x + move_step;
			new_bar.y = outPosMoveTo.y - move_step;

			if (CanMoveOrShoot(Board_copy, outPosMoveTo, new_bar)) {
				//修改临时棋盘信息
				Board_copy[new_bar.x][new_bar.y] = BAR;
				//获取该情况走法的权值
				double value = ValueOfShoot(Board_copy, temp_final_step.end, new_bar);
				if (value >= temp_final_step.value) {
					temp_final_step.value = value; //更新最终权值
					temp_final_step.bar.x = new_bar.x; temp_final_step.bar.y = new_bar.y;
				}
				move_step++;
				//还原临时棋盘信息
				Board_copy[new_bar.x][new_bar.y] = EMP;
			}
			else {
				move_step = 1;
				break;
			}
		}
	}
	//////////////////////////////////向右下/////////////////////////////////
	while (true) {
		if (outPosMoveTo.x + move_step > 9 || outPosMoveTo.y + move_step > 9) {
			move_step = 1;
			break;
		}
		else {
			//生成障碍位置

			new_bar.x = outPosMoveTo.x + move_step;
			new_bar.y = outPosMoveTo.y + move_step;

			if (CanMoveOrShoot(Board_copy, outPosMoveTo, new_bar)) {
				//修改临时棋盘信息
				Board_copy[new_bar.x][new_bar.y] = BAR;
				//获取该情况走法的权值
				double value = ValueOfShoot(Board_copy, temp_final_step.end, new_bar);
				if (value >= temp_final_step.value) {
					temp_final_step.value = value; //更新最终权值
					temp_final_step.bar.x = new_bar.x; temp_final_step.bar.y = new_bar.y;
				}
				move_step++;
				//还原临时棋盘信息
				Board_copy[new_bar.x][new_bar.y] = EMP;
			}
			else {
				move_step = 1;
				break;
			}
		}
	}

	if (temp_final_step.bar.x == 4 && temp_final_step.bar.y == 4) {
		temp_final_step.bar = outPosSelected;
	}
	//探查完八个方向以后
	outPosShootAt.x = temp_final_step.bar.x;
	outPosShootAt.y = temp_final_step.bar.y;
	return temp_final_step.value;
}

long ValueOfStep_TEST(int Board[10][10], int computerSide, SPosition outPosSelected, SPosition outPosMoveTo, SPosition& outPosShootAt) {
	while (true)
	{
		//j将棋盘信息拷贝一次
		int Board_copy[10][10];
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++)
			{
				Board_copy[i][j] = Board[i][j];
			}
		}
		//修改棋盘信息
		Board_copy[outPosSelected.x][outPosSelected.y] = EMP;
		Board_copy[outPosMoveTo.x][outPosMoveTo.y] = computerSide;


		outPosShootAt.x = rand() % 10;
		outPosShootAt.y = rand() % 10;
		if (CanMoveOrShoot(Board_copy, outPosMoveTo, outPosShootAt) && (outPosMoveTo.x != outPosShootAt.x || outPosMoveTo.y != outPosShootAt.y)) {
			return rand();
		}
	}
}

double ValueOfShoot(int Board[10][10], SPosition outPosMoveTo, SPosition outPosShootAt) {
	//ONLY FOR TEST!!!
	//return rand();

	//AI判断信息
	int judge_side = BLACK;
	double free_stand_of_selected = 0;
	double free_stand_of_all_black = 0;
	double free_stand_of_all_white = 0;

	//解析棋盘信息
	judge_side = Board[outPosMoveTo.x][outPosMoveTo.y];
	SPosition W_chess[4];
	SPosition B_chess[4];
	int wflag = 0, bflag = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (Board[i][j] == BLACK) {
				B_chess[bflag].x = i; B_chess[bflag].y = j;
				bflag++;
			}
			else if (Board[i][j] == WHITE) {
				W_chess[wflag].x = i; W_chess[wflag].y = j;
				wflag++;
			}
		}
	}

	//计算判断信息
	free_stand_of_selected = getFreeStand(Board, outPosMoveTo);

	for (int i = 0; i < 4; i++) {
		free_stand_of_all_black += getFreeStand(Board, B_chess[i]);
	}
	for (int i = 0; i < 4; i++) {
		free_stand_of_all_white += getFreeStand(Board, W_chess[i]);
	}

	//printf("freestandofselected:%f\n", free_stand_of_selected);
	//printf("freestandofw:%f\n", free_stand_of_all_white);
	//printf("freestandofb:%f\n", free_stand_of_all_black);
	switch (judge_side)
	{
	case(BLACK):
		if (free_stand_of_all_black > free_stand_of_all_white)
			return (free_stand_of_selected * free_stand_of_all_black * (free_stand_of_all_black - free_stand_of_all_white)) / free_stand_of_all_white;
		else if (free_stand_of_all_black < free_stand_of_all_white)
			return (free_stand_of_selected * free_stand_of_all_black) / free_stand_of_all_white * (free_stand_of_all_white - free_stand_of_all_black);
		else
			return (free_stand_of_selected * free_stand_of_all_black) / free_stand_of_all_white;
		break;
	case(WHITE):
		if (free_stand_of_all_white > free_stand_of_all_black)
			return (free_stand_of_selected * free_stand_of_all_white * (free_stand_of_all_white - free_stand_of_all_black)) / free_stand_of_all_black;
		else if (free_stand_of_all_white < free_stand_of_all_black)
			return(free_stand_of_selected * free_stand_of_all_white) / free_stand_of_all_black * (free_stand_of_all_black - free_stand_of_all_white);
		else return (free_stand_of_selected * free_stand_of_all_white) / free_stand_of_all_black;
		break;
	default:
		return 0;
		break;
	}
}

double getFreeStand(int Board[10][10], SPosition position) {
	//ONLY FOR TEST
	//return rand();


	double free_stand = 0;
	int moveStep = 1;
	//探测各个方向步数
	////////////////////////////////向上步数//////////////////////////////
	while (true) {
		if (position.y - moveStep < 0) {
			moveStep = 1;
			break;
		}
		else if (Board[position.x][position.y - moveStep] == EMP) {
			free_stand++;
			moveStep++;
		}
		else {
			moveStep = 1;
			break;
		}
	}
	////////////////////////////////向下步数//////////////////////////////
	while (true) {
		if (position.y + moveStep > 9) {
			moveStep = 1;
			break;
		}
		else if (Board[position.x][position.y + moveStep] == EMP) {
			free_stand++;
			moveStep++;
		}
		else {
			moveStep = 1;
			break;
		}
	}
	////////////////////////////////向左步数//////////////////////////////
	while (true) {
		if (position.x - moveStep < 0) {
			moveStep = 1;
			break;
		}
		else if (Board[position.x - moveStep][position.y] == EMP) {
			free_stand++;
			moveStep++;
		}
		else {
			moveStep = 1;
			break;
		}
	}
	////////////////////////////////向右步数//////////////////////////////
	while (true) {
		if (position.x + moveStep > 9) {
			moveStep = 1;
			break;
		}
		else if (Board[position.x + moveStep][position.y] == EMP) {
			free_stand++;
			moveStep++;
		}
		else {
			moveStep = 1;
			break;
		}
	}
	////////////////////////////////向左上步数//////////////////////////////
	while (true) {
		if (position.y - moveStep < 0 || position.x - moveStep < 0) {
			moveStep = 1;
			break;
		}
		else if (Board[position.x - moveStep][position.y - moveStep] == EMP) {
			free_stand++;
			moveStep++;
		}
		else {
			moveStep = 1;
			break;
		}
	}
	////////////////////////////////向左下步数//////////////////////////////
	while (true) {
		if (position.y + moveStep > 9 || position.x - moveStep < 0) {
			moveStep = 1;
			break;
		}
		else if (Board[position.x - moveStep][position.y + moveStep] == EMP) {
			free_stand++;
			moveStep++;
		}
		else {
			moveStep = 1;
			break;
		}
	}
	////////////////////////////////向右上步数//////////////////////////////
	while (true) {
		if (position.y - moveStep < 0 || position.x + moveStep > 9) {
			moveStep = 1;
			break;
		}
		else if (Board[position.x + moveStep][position.y - moveStep] == EMP) {
			free_stand++;
			moveStep++;
		}
		else {
			moveStep = 1;
			break;
		}
	}
	////////////////////////////////向右下步数//////////////////////////////
	while (true) {
		if (position.y + moveStep > 9 || position.x + moveStep > 9) {
			moveStep = 1;
			break;
		}
		else if (Board[position.x + moveStep][position.y + moveStep] == EMP) {
			free_stand++;
			moveStep++;
		}
		else {
			moveStep = 1;
			break;
		}
	}
	return free_stand;
}