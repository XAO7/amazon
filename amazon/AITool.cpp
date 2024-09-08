#include"AITool.h"

int getWinside(int Board[10][10], Step Book[92]) { //��������������Ϣ��������Ϣ�ж�ʤ����

	bool allFull = true;
	int whiteflag = 0, blackflag = 0;
	int winSide = 4;
	SPosition whiteChess[4];
	SPosition blackChess[4];

	//1.����ȫ������������£�����ʤ
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
		//2.�ж�ʤ��
		//�洢������Ϣ
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
			if (Board[whiteChess[i].x][whiteChess[i].y - 1] == EMP && whiteChess[i].y - 1 >= 0) canWhiteMove = true;//��
			else if (Board[whiteChess[i].x - 1][whiteChess[i].y] == EMP && whiteChess[i].x - 1 >= 0) canWhiteMove = true;//��
			else if (Board[whiteChess[i].x][whiteChess[i].y + 1] == EMP && whiteChess[i].y + 1 <= 9)  canWhiteMove = true;//��
			else if (Board[whiteChess[i].x + 1][whiteChess[i].y] == EMP && whiteChess[i].x + 1 <= 9)  canWhiteMove = true;//��
			else if (Board[whiteChess[i].x - 1][whiteChess[i].y - 1] == EMP && whiteChess[i].x - 1 >= 0 && whiteChess[i].y - 1 >= 0)  canWhiteMove = true;//����
			else if (Board[whiteChess[i].x - 1][whiteChess[i].y + 1] == EMP && whiteChess[i].x - 1 >= 0 && whiteChess[i].y + 1 <= 9)  canWhiteMove = true;//����
			else if (Board[whiteChess[i].x + 1][whiteChess[i].y - 1] == EMP && whiteChess[i].x + 1 <= 9 && whiteChess[i].y - 1 >= 0)  canWhiteMove = true;//����
			else if (Board[whiteChess[i].x + 1][whiteChess[i].y + 1] == EMP && whiteChess[i].x + 1 <= 9 && whiteChess[i].y + 1 <= 9)  canWhiteMove = true;//����
		}
		for (int i = 0; i < 4; i++) {
			if (Board[blackChess[i].x][blackChess[i].y - 1] == EMP && blackChess[i].y - 1 >= 0) canBlackMove = true;//��
			else if (Board[blackChess[i].x - 1][blackChess[i].y] == EMP && blackChess[i].x - 1 >= 0) canBlackMove = true;//��
			else if (Board[blackChess[i].x][blackChess[i].y + 1] == EMP && blackChess[i].y + 1 <= 9)  canBlackMove = true;//��
			else if (Board[blackChess[i].x + 1][blackChess[i].y] == EMP && blackChess[i].x + 1 <= 9)  canBlackMove = true;//��
			else if (Board[blackChess[i].x - 1][blackChess[i].y - 1] == EMP && blackChess[i].x - 1 >= 0 && blackChess[i].y - 1 >= 0)  canBlackMove = true;//����
			else if (Board[blackChess[i].x - 1][blackChess[i].y + 1] == EMP && blackChess[i].x - 1 >= 0 && blackChess[i].y + 1 <= 9)  canBlackMove = true;//����
			else if (Board[blackChess[i].x + 1][blackChess[i].y - 1] == EMP && blackChess[i].x + 1 <= 9 && blackChess[i].y - 1 >= 0)  canBlackMove = true;//����
			else if (Board[blackChess[i].x + 1][blackChess[i].y + 1] == EMP && blackChess[i].x + 1 <= 9 && blackChess[i].y + 1 <= 9)  canBlackMove = true;//����
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

bool CanMoveOrShoot(int plate[10][10], SPosition posFrom, SPosition posTo)//�ж�������߷�ֹ�ϰ��Ƿ�Ϸ�
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
	}//ԭ�ض���
	else if (fromX == toX) k = 0;//�ڴ�ֱ������
	else if (fromY == toY) k = 1;//��ˮƽ������
	else if (toX - fromX == toY - fromY) k = 2;//����������б����
	else if (fromX - toX == toY - fromY) k = 3;//����������б����
	else {
		//printf("invaild move\n");
		return false;
	}
	switch (k)
	{
	case 0:///////////////////////////////////////////////////////��ֱ����
		if (toY > fromY) {//��
			for (int i = fromY + 1; i < toY; i++) {
				if (plate[fromX][i] != EMP) {
					//printf("down error\n");
					return false;
				}
			}
		}
		else if (toY < fromY) {//��
			for (int i = fromY - 1; i > toY; i--) {
				if (plate[fromX][i] != EMP) {
					//printf("up error\n");
					return false;
				}
			}
		}
		else return true;
	case 1:////////////////////////////////////////////////////ˮƽ����
		if (toX > fromX) {//��
			for (int i = fromX + 1; i < toX; i++) {
				if (plate[i][fromY] != EMP) {
					//printf("right error\n");
					return false;
				}
			}
		}
		else if (toX < fromX) {//��
			for (int i = fromX - 1; i > toX; i--) {
				if (plate[i][fromY] != EMP) {
					//printf("left error\n");
					return false;
				}
			}
		}
		else return true;
	case 2://////////////////////////////////////////////////��������б��
		if (toX < fromX) {//����
			for (int i = fromX - 1, j = fromY - 1; i > toX && j > toY; i--, j--) {
				if (plate[i][j] != EMP) {
					//printf("left up error\n");
					return false;
				}
			}
		}
		else if (toX > fromX) {//����
			for (int i = fromX + 1, j = fromY + 1; i < toX && j < toY; i++, j++) {
				if (plate[i][j] != EMP) {
					//printf("right down error\n");
					return false;
				}
			}
		}
		else return true;
	case 3://////////////////////////////////////////////////��������б��
		if (toY > fromY) {//����
			for (int i = fromX - 1, j = fromY + 1; i > toX && j < toY; i--, j++) {
				if (plate[i][j] != EMP) {
					//printf("left down error\n");
					return false;
				}
			}
		}
		else if (toY < fromY) {//����
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

void AICompute_TEST(   //����AI
	int Board[10][10],			//��������
	int computerSide,       //�Ƿ�����Ϊ���1���м��㣬������Ϊ���2���м���
	Step& final_step)
{

	SPosition  outPosSelected;	//ѡ���������
	SPosition  outPosMoveTo;//ѡ������λ��
	SPosition  outPosShootAt;	//ѡ������ϰ�λ��

	//��������ÿ�����ӵ������߷�����Ȩֵ

	//��������
	//��ż���ִ����Ϣ
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
	//�ֱ������ĸ����ӵ�����߷���������Ӧ��ŵ�λ��
	for (int i = 0; i < 4; i++) {
		outPosSelected = chess[i];
		int moveStep = 1;
		/////////////////////////////////////̽�����Ϸ���//////////////////////////////////
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
					double tempValue = ValueOfStep(Board, computerSide, outPosSelected, outPosMoveTo, outPosShootAt);//��ȡ�ò����Ȩֵ
					if (tempValue >= temp_steps[i].value) {
						temp_steps[i].value = tempValue; //��������Ȩֵ
						temp_steps[i].start = outPosSelected; temp_steps[i].end = outPosMoveTo; temp_steps[i].bar = outPosShootAt;
					}
					moveStep++;//���²���
				}
				else {
					moveStep = 1;
					break;
				}
			}
		}
		/////////////////////////////////////̽�����·���//////////////////////////////////
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
					double tempValue = ValueOfStep(Board, computerSide, outPosSelected, outPosMoveTo, outPosShootAt);//��ȡ�ò����Ȩֵ
					if (tempValue >= temp_steps[i].value) {
						temp_steps[i].value = tempValue; //��������Ȩֵ
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
		/////////////////////////////////////̽��������//////////////////////////////////
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
					double tempValue = ValueOfStep(Board, computerSide, outPosSelected, outPosMoveTo, outPosShootAt);//��ȡ�ò����Ȩֵ
					if (tempValue >= temp_steps[i].value) {
						temp_steps[i].value = tempValue; //��������Ȩֵ
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
		/////////////////////////////////////̽�����ҷ���//////////////////////////////////
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
					double tempValue = ValueOfStep(Board, computerSide, outPosSelected, outPosMoveTo, outPosShootAt);//��ȡ�ò����Ȩֵ
					if (tempValue >= temp_steps[i].value) {
						temp_steps[i].value = tempValue; //��������Ȩֵ
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
		/////////////////////////////////////̽�������Ϸ���//////////////////////////////////
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
					double tempValue = ValueOfStep(Board, computerSide, outPosSelected, outPosMoveTo, outPosShootAt);//��ȡ�ò����Ȩֵ
					if (tempValue >= temp_steps[i].value) {
						temp_steps[i].value = tempValue; //��������Ȩֵ
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
		/////////////////////////////////////̽�������·���//////////////////////////////////
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
					double tempValue = ValueOfStep(Board, computerSide, outPosSelected, outPosMoveTo, outPosShootAt);//��ȡ�ò����Ȩֵ
					if (tempValue >= temp_steps[i].value) {
						temp_steps[i].value = tempValue; //��������Ȩֵ
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
		/////////////////////////////////////̽�������Ϸ���//////////////////////////////////
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
					double tempValue = ValueOfStep(Board, computerSide, outPosSelected, outPosMoveTo, outPosShootAt);//��ȡ�ò����Ȩֵ
					if (tempValue >= temp_steps[i].value) {
						temp_steps[i].value = tempValue; //��������Ȩֵ
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
		/////////////////////////////////////̽�������·���//////////////////////////////////
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
					double tempValue = ValueOfStep(Board, computerSide, outPosSelected, outPosMoveTo, outPosShootAt);//��ȡ�ò����Ȩֵ
					if (tempValue >= temp_steps[i].value) {
						temp_steps[i].value = tempValue; //��������Ȩֵ
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
		//����˸����򶼲����ߣ���valueֵ��Ϊһ�����������
		if (temp_steps[i].start.x == 4 && temp_steps[i].start.y == 4 && temp_steps[i].end.x == 4 && temp_steps[i].end.y == 4 && temp_steps[i].bar.x == 4 && temp_steps[i].bar.y == 4) {
			temp_steps[i].value = -1 * rand();
		}
	}

	//printf("%f/%f/%f/%f\n", temp_steps[0].value, temp_steps[1].value, temp_steps[2].value, temp_steps[3].value);

	/////////////////////�Ƚϳ���õ��߷�///////////////////////
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

	//��������Ϣ����һ��
	int Board_copy[10][10];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
		{
			Board_copy[i][j] = Board[i][j];
		}
	}
	//�޸�������Ϣ
	Board_copy[outPosSelected.x][outPosSelected.y] = EMP;
	Board_copy[outPosMoveTo.x][outPosMoveTo.y] = computerSide;

	//�����ʱ���ղ���
	Step temp_final_step;
	temp_final_step.start.x = outPosSelected.x; temp_final_step.start.y = outPosSelected.y; temp_final_step.end.x = outPosMoveTo.x; temp_final_step.end.y = outPosMoveTo.y;
	temp_final_step.value = 0;

	//̽��˸������Ͽ��Է��ϰ���λ��
	int move_step = 1;
	SPosition new_bar;

	//////////////////////////////////����/////////////////////////////////
	while (true) {
		if (outPosMoveTo.y - move_step < 0) {
			move_step = 1;
			break;
		}
		else {
			//�����ϰ�λ��
			new_bar.y = outPosMoveTo.y - move_step;
			new_bar.x = outPosMoveTo.x;
			if (CanMoveOrShoot(Board_copy, outPosMoveTo, new_bar)) {
				//�޸���ʱ������Ϣ
				Board_copy[new_bar.x][new_bar.y] = BAR;
				//��ȡ������߷���Ȩֵ
				double value = ValueOfShoot(Board_copy, temp_final_step.end, new_bar);
				if (value >= temp_final_step.value) {
					temp_final_step.value = value; //��������Ȩֵ
					temp_final_step.bar.x = new_bar.x; temp_final_step.bar.y = new_bar.y;
				}
				move_step++;
				//��ԭ��ʱ������Ϣ
				Board_copy[new_bar.x][new_bar.y] = EMP;
			}
			else {
				move_step = 1;
				break;
			}
		}
	}
	//////////////////////////////////����/////////////////////////////////

	while (true) {
		if (outPosMoveTo.y + move_step > 9) {
			move_step = 1;
			break;
		}
		else {
			//�����ϰ�λ��
			new_bar.y = outPosMoveTo.y + move_step;
			new_bar.x = outPosMoveTo.x;
			if (CanMoveOrShoot(Board_copy, outPosMoveTo, new_bar)) {
				//�޸���ʱ������Ϣ
				Board_copy[new_bar.x][new_bar.y] = BAR;
				//��ȡ������߷���Ȩֵ
				double value = ValueOfShoot(Board_copy, temp_final_step.end, new_bar);
				if (value >= temp_final_step.value) {
					temp_final_step.value = value; //��������Ȩֵ
					temp_final_step.bar.x = new_bar.x; temp_final_step.bar.y = new_bar.y;
				}
				move_step++;
				//��ԭ��ʱ������Ϣ
				Board_copy[new_bar.x][new_bar.y] = EMP;
			}
			else {
				move_step = 1;
				break;
			}
		}
	}
	//////////////////////////////////����/////////////////////////////////

	while (true) {
		if (outPosMoveTo.x - move_step < 0) {
			move_step = 1;
			break;
		}
		else {
			//�����ϰ�λ��
			new_bar.x = outPosMoveTo.x - move_step;
			new_bar.y = outPosMoveTo.y;

			if (CanMoveOrShoot(Board_copy, outPosMoveTo, new_bar)) {
				//�޸���ʱ������Ϣ
				Board_copy[new_bar.x][new_bar.y] = BAR;
				//��ȡ������߷���Ȩֵ
				double value = ValueOfShoot(Board_copy, temp_final_step.end, new_bar);
				if (value >= temp_final_step.value) {
					temp_final_step.value = value; //��������Ȩֵ
					temp_final_step.bar.x = new_bar.x; temp_final_step.bar.y = new_bar.y;
				}
				move_step++;
				//��ԭ��ʱ������Ϣ
				Board_copy[new_bar.x][new_bar.y] = EMP;
			}
			else {
				move_step = 1;
				break;
			}
		}
	}
	//////////////////////////////////����/////////////////////////////////

	while (true) {
		if (outPosMoveTo.x + move_step > 9) {
			move_step = 1;
			break;
		}
		else {
			//�����ϰ�λ��
			new_bar.x = outPosMoveTo.x + move_step;
			new_bar.y = outPosMoveTo.y;

			if (CanMoveOrShoot(Board_copy, outPosMoveTo, new_bar)) {
				//�޸���ʱ������Ϣ
				Board_copy[new_bar.x][new_bar.y] = BAR;
				//��ȡ������߷���Ȩֵ
				double value = ValueOfShoot(Board_copy, temp_final_step.end, new_bar);
				if (value >= temp_final_step.value) {
					temp_final_step.value = value; //��������Ȩֵ
					temp_final_step.bar.x = new_bar.x; temp_final_step.bar.y = new_bar.y;
				}
				move_step++;
				//��ԭ��ʱ������Ϣ
				Board_copy[new_bar.x][new_bar.y] = EMP;
			}
			else {
				move_step = 1;
				break;
			}
		}
	}
	//////////////////////////////////������/////////////////////////////////
	while (true) {
		if (outPosMoveTo.x - move_step < 0 || outPosMoveTo.y - move_step < 0) {
			move_step = 1;
			break;
		}
		else {
			//�����ϰ�λ��

			new_bar.x = outPosMoveTo.x - move_step;
			new_bar.y = outPosMoveTo.y - move_step;

			if (CanMoveOrShoot(Board_copy, outPosMoveTo, new_bar)) {
				//�޸���ʱ������Ϣ
				Board_copy[new_bar.x][new_bar.y] = BAR;
				//��ȡ������߷���Ȩֵ
				double value = ValueOfShoot(Board_copy, temp_final_step.end, new_bar);
				if (value >= temp_final_step.value) {
					temp_final_step.value = value; //��������Ȩֵ
					temp_final_step.bar.x = new_bar.x; temp_final_step.bar.y = new_bar.y;
				}
				move_step++;
				//��ԭ��ʱ������Ϣ
				Board_copy[new_bar.x][new_bar.y] = EMP;
				new_bar.x = 0; new_bar.y = 0;
			}
			else {
				move_step = 1;
				break;
			}
		}
	}
	//////////////////////////////////������/////////////////////////////////
	while (true) {
		if (outPosMoveTo.x - move_step < 0 || outPosMoveTo.y + move_step > 9) {
			move_step = 1;
			break;
		}
		else {
			//�����ϰ�λ��

			new_bar.x = outPosMoveTo.x - move_step;
			new_bar.y = outPosMoveTo.y + move_step;

			if (CanMoveOrShoot(Board_copy, outPosMoveTo, new_bar)) {
				//�޸���ʱ������Ϣ
				Board_copy[new_bar.x][new_bar.y] = BAR;
				//��ȡ������߷���Ȩֵ
				double value = ValueOfShoot(Board_copy, temp_final_step.end, new_bar);
				if (value >= temp_final_step.value) {
					temp_final_step.value = value; //��������Ȩֵ
					temp_final_step.bar.x = new_bar.x; temp_final_step.bar.y = new_bar.y;
				}
				move_step++;
				//��ԭ��ʱ������Ϣ
				Board_copy[new_bar.x][new_bar.y] = EMP;
			}
			else {
				move_step = 1;
				break;
			}
		}
	}
	//////////////////////////////////������/////////////////////////////////
	while (true) {
		if (outPosMoveTo.x + move_step > 9 || outPosMoveTo.y - move_step < 0) {
			move_step = 1;
			break;
		}
		else {
			//�����ϰ�λ��

			new_bar.x = outPosMoveTo.x + move_step;
			new_bar.y = outPosMoveTo.y - move_step;

			if (CanMoveOrShoot(Board_copy, outPosMoveTo, new_bar)) {
				//�޸���ʱ������Ϣ
				Board_copy[new_bar.x][new_bar.y] = BAR;
				//��ȡ������߷���Ȩֵ
				double value = ValueOfShoot(Board_copy, temp_final_step.end, new_bar);
				if (value >= temp_final_step.value) {
					temp_final_step.value = value; //��������Ȩֵ
					temp_final_step.bar.x = new_bar.x; temp_final_step.bar.y = new_bar.y;
				}
				move_step++;
				//��ԭ��ʱ������Ϣ
				Board_copy[new_bar.x][new_bar.y] = EMP;
			}
			else {
				move_step = 1;
				break;
			}
		}
	}
	//////////////////////////////////������/////////////////////////////////
	while (true) {
		if (outPosMoveTo.x + move_step > 9 || outPosMoveTo.y + move_step > 9) {
			move_step = 1;
			break;
		}
		else {
			//�����ϰ�λ��

			new_bar.x = outPosMoveTo.x + move_step;
			new_bar.y = outPosMoveTo.y + move_step;

			if (CanMoveOrShoot(Board_copy, outPosMoveTo, new_bar)) {
				//�޸���ʱ������Ϣ
				Board_copy[new_bar.x][new_bar.y] = BAR;
				//��ȡ������߷���Ȩֵ
				double value = ValueOfShoot(Board_copy, temp_final_step.end, new_bar);
				if (value >= temp_final_step.value) {
					temp_final_step.value = value; //��������Ȩֵ
					temp_final_step.bar.x = new_bar.x; temp_final_step.bar.y = new_bar.y;
				}
				move_step++;
				//��ԭ��ʱ������Ϣ
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
	//̽����˸������Ժ�
	outPosShootAt.x = temp_final_step.bar.x;
	outPosShootAt.y = temp_final_step.bar.y;
	return temp_final_step.value;
}

long ValueOfStep_TEST(int Board[10][10], int computerSide, SPosition outPosSelected, SPosition outPosMoveTo, SPosition& outPosShootAt) {
	while (true)
	{
		//j��������Ϣ����һ��
		int Board_copy[10][10];
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++)
			{
				Board_copy[i][j] = Board[i][j];
			}
		}
		//�޸�������Ϣ
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

	//AI�ж���Ϣ
	int judge_side = BLACK;
	double free_stand_of_selected = 0;
	double free_stand_of_all_black = 0;
	double free_stand_of_all_white = 0;

	//����������Ϣ
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

	//�����ж���Ϣ
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
	//̽�����������
	////////////////////////////////���ϲ���//////////////////////////////
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
	////////////////////////////////���²���//////////////////////////////
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
	////////////////////////////////������//////////////////////////////
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
	////////////////////////////////���Ҳ���//////////////////////////////
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
	////////////////////////////////�����ϲ���//////////////////////////////
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
	////////////////////////////////�����²���//////////////////////////////
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
	////////////////////////////////�����ϲ���//////////////////////////////
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
	////////////////////////////////�����²���//////////////////////////////
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