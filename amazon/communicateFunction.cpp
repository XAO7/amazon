#define _CRT_SECURE_NO_WARNINGS 
#include"communicateFunction.h"

//SETTING PROGRAM NAME
string AI_name = "Valkyria";
string CP_name = "####";

void Amazon::go(char *message, char *result)
{
    //分析命令
    if (message[0] == 'm')//行棋
    {
        if (start == 1) {
            //判断已经通过，处理己方上一步行棋
            Board[step.start.x][step.start.y] = EMP;
            Board[step.end.x][step.end.y] = computerSide;
            Board[step.bar.x][step.bar.y] = BAR;

            //保存己方棋谱
//            cout << "save step" << step.start.x << step.start.y << step.end.x << step.end.y << endl;
            Book[count] = step;
            count++;
        }

        //获取对手行棋着法
        step.start.x = message[5] - 'A';
        step.start.y = message[6] - 'A';
        step.end.x = message[7] - 'A';
        step.end.y = message[8] - 'A';
        step.bar.x = message[9] - 'A';
        step.bar.y = message[10] - 'A';

        //处理对手行棋
        Board[step.start.x][step.start.y] = EMP;
        Board[step.end.x][step.end.y] = computerSide ^ 1;
        Board[step.bar.x][step.bar.y] = BAR;

        last_step[0] = step.start.x;
        last_step[1] = step.start.y;
        last_step[2] = step.end.x;
        last_step[3] = step.end.y;
        last_step[4] = step.bar.x;
        last_step[5] = step.bar.y;

        //printBoard(Board);

        //将对手行棋保存到棋谱
        Book[count] = step;
        count++;

        //重置errorTime
        errorTime = 0;

        //生成着法，并保存在step结构中
//        printf("AI 正在处理");
        AICompute(Board, computerSide, step);
//        printf("AI 处理完毕");

        //设置开始标记；
        start = 1;
        //输出着法
        snprintf(result, 16, "move %c%c%c%c%c%c", step.start.x + 'A', step.start.y + 'A', step.end.x + 'A', step.end.y + 'A', step.bar.x + 'A', step.bar.y + 'A');
//        printf("move %c%c%c%c%c%c\n", step.start.x + 'A', step.start.y + 'A', step.end.x + 'A', step.end.y + 'A', step.bar.x + 'A', step.bar.y + 'A');
        fflush(stdout);

    }
    else if (message[0] == 'n')//建立新棋局
    {
        // scanf("%s", message);//获取己方执棋颜色
        // fflush(stdin);

        start = 0; // 避免新的棋局时 上一棋局最后一步被保存

        if (strcmp(message, "new black") == 0)//执黑
            computerSide = BLACK;
        else//执白
            computerSide = WHITE;

        //初始化棋局
        for (int i = 0; i < 10; ++i)
            for (int j = 0; j < 10; ++j)
                Board[i][j] = EMP;
        Board[0][3] = Board[3][0] = Board[6][0] = Board[9][3] = WHITE;
        Board[0][6] = Board[3][9] = Board[6][9] = Board[9][6] = BLACK;

        //printBoard(Board);

        if (computerSide == BLACK)
        {
            //生成第一手着法，并保存在step结构中
            //printf("AI 正在处理");
            AICompute(Board, computerSide, step);
            //printf("AI 处理完毕");

            //将开始对局标记设置为一；
            start = 1;

            //输出着法
            snprintf(result, 16, "move %c%c%c%c%c%c", step.start.x + 'A', step.start.y + 'A', step.end.x + 'A', step.end.y + 'A', step.bar.x + 'A', step.bar.y + 'A');
            fflush(stdout);

            //printBoard(Board);

        }
    }
    else if (message[0] == 'e')//着法错误
    {
        fflush(stdin);

        //防止进入死循环，重算之前检测出错次数
        if (errorTime > ERROR_TIME_MAX) {
            return;
        }

        //收到error消息时，己方上一步走法还未写入棋谱，棋盘也还未更新
        //重新生成走法
        AICompute(Board, computerSide, step);


        //重新输出着法
        snprintf(result, 16, "move %c%c%c%c%c%c", step.start.x + 'A', step.start.y + 'A', step.end.x + 'A', step.end.y + 'A', step.bar.x + 'A', step.bar.y + 'A');
        fflush(stdout);

        //更新出错次数
        errorTime++;

    }
    else if (strcmp(message, "name?") == 0)//询问引擎名
    {
        fflush(stdin);

        fflush(stdout);
        //输出引擎名
        //printf("name αβ剪枝\n");
        //fflush(stdout);
    }
    else if (strcmp(message, "end") == 0)//对局结束
    {
        fflush(stdin);

        //打印第一行比赛信息并判断先手胜还是后手胜
        winSide = getWinside(Board, Book);

        time_t nowtime;
        struct tm* p;;
        time(&nowtime);
        p = localtime(&nowtime);
        string filename = "./比赛棋谱/棋谱" + get_date_time(true, time(NULL)) + ".txt";
        fstream  toBook(filename);//创建一个fstream文件流对象
        toBook.open(filename, ios::out);

        switch (computerSide)
        {
        case BLACK:
            if (winSide == BLACK) {
                toBook << "#[AM][" + AI_name + "][" + CP_name + "][先手胜][" << 1900 + p->tm_year << " / " << 1 + p->tm_mon << " / " << p->tm_mday << " " <<
                    p->tm_hour << ":" << p->tm_min << ":" << p->tm_sec << " 四川][国赛]；" << endl;
            }
            if (winSide == WHITE) {
                toBook << "#[AM][" + AI_name + "][" + CP_name + "][后手胜][" << 1900 + p->tm_year << "/" << 1 + p->tm_mon << "/" << p->tm_mday << " " <<
                    p->tm_hour << ":" << p->tm_min << ":" << p->tm_sec << " 四川][国赛]；" << endl;
            }
            break;
        case WHITE:
            if (winSide == BLACK) {
                toBook << "#[AM][" + CP_name + "][" + AI_name + "][先手胜][" << 1900 + p->tm_year << "/" << 1 + p->tm_mon << "/" << p->tm_mday << " " <<
                    p->tm_hour << ":" << p->tm_min << ":" << p->tm_sec << " 四川][国赛]；" << endl;
            }
            if (winSide == WHITE) {
                toBook << "#[AM][" + CP_name + "][" + AI_name + "][后手胜][" << 1900 + p->tm_year << "/" << 1 + p->tm_mon << "/" << p->tm_mday << " " <<
                    p->tm_hour << ":" << p->tm_min << ":" << p->tm_sec << " 四川][国赛]；" << endl;
            }
            break;
        default:
            break;
        }

        //逐行打印棋谱信息
        for (int i = 0, round = 1; i < count; i++) {
            if (i % 2 == 0) {
                toBook << round << " " << char(Book[i].start.x + 'A') << char(Book[i].start.y + 'A')
                    << char(Book[i].end.x + 'A') << char(Book[i].end.y + 'A')
                    << char(Book[i].bar.x + 'A') << char(Book[i].bar.y + 'A') << " ";
            }
            else {
                toBook << char(Book[i].start.x + 'A') << char(Book[i].start.y + 'A')
                    << char(Book[i].end.x + 'A') << char(Book[i].end.y + 'A')
                    << char(Book[i].bar.x + 'A') << char(Book[i].bar.y + 'A') << endl;
                round++;
            }
        }

        toBook.close();
        start = 0;
        count = 0;
    }
    else if (strcmp(message, "quit") == 0)//退出引擎
    {
        fflush(stdin);
        return;
    }
}

string get_date_time(bool onlynum, time_t timestamp)
{
    char buffer[20] = { 0 };
    struct tm* info = localtime(&timestamp);
    if (onlynum) {
        strftime(buffer, sizeof buffer, "%Y%m%d%H%M%S", info);
    }
    else {
        strftime(buffer, sizeof buffer, "%Y/%m/%d %H:%M:%S", info);
    }
    return string(buffer);
}

