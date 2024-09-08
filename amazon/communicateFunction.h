#include"AmazonGame.h"
#include"AITool.h"
#include"AmazonAI.h"
#include<fstream>
#include <windows.h>

string get_date_time(bool onlynum = true, time_t timestamp = time(NULL));

class Amazon
{

private:

    Step step;//临时步结构
    int count = 0;//计算步数；
    int winSide = 4;//胜利方
    int errorTime = 0;
    Step Book[92];//保存棋谱；

public:
    int computerSide = 0;//己方执棋颜色
    int start = 0;//对局开始标记
    int last_step[6];//记录人类方上一步棋 用于悔棋;
    int Board[10][10];//棋盘结构
    void go(char *message, char *result);
};
