#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QPainter>
#include <QPixmap>
#include <QThread>
#include <QRadioButton>
#include <QPushButton>
#include <amazon/communicateFunction.h>

typedef struct {
    QPoint CBPos;
    int type; //1 black 2 white 3 barrier
}Chess;

typedef struct {
    Chess chesses[100];
    int count;
    QPoint last_point;
    int last_index;
    QPoint last_human;
    QPoint current_human;

}ChessB;

class Worker: public QObject
{
    Q_OBJECT

public:
    char result[16];

public slots:
    void doWork(Amazon *opponent, char *message)
    {
        opponent->go(message, result);
        emit resultReady(result);
    }
signals:
    void resultReady(char *result);
};

class ChessBoard : public QWidget
{
    Q_OBJECT
public:
    explicit ChessBoard(QWidget *parent = nullptr);
    ~ChessBoard();

    int humanSide = 1;
    int _humanSide = 1;
    QPushButton *PB_new;
    QPushButton *PB_regret;
    QPushButton *PB_error;

protected:
    void mousePressEvent(QMouseEvent *event);
    QPoint getCBPos(QPoint pos);
    void CBEvent(QPoint CBPos);
    bool canMove(QPoint CBPos);
    Chess *getChess(QPoint CBPos);
    void getMove(char *move, int n, QPoint CBPos);

    void paintEvent(QPaintEvent *event);

private:
    QPoint pos;
    ChessB CB;

    QPixmap img_black;
    QPixmap img_white;
    QPixmap img_cb;

    int state;
    Chess *c;
    char move[7]; //定义数组时会默认在字符串后加一个\0，它占内存，但如果已经定义了数组长度，且数组长度没有\0的位置，
                    //则会发生越界、输出乱码，同时这种情况下strlen也不会停止，直到遇到第一个\0为止。
    char result[16];
    Amazon opponent;

    QThread *workerThread;
    Worker *worker;

    QRadioButton *RB_black;
    QRadioButton *RB_white;

public slots:
    void parseResult(char *r);
    void newCB();
    void regret();
    void error();

    void on_ChooseChess();
signals:
    void operate(Amazon *, char *);

};

#endif // CHESSBOARD_H
