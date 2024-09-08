#include "chessboard.h"
#include <iostream>
#include <widget.h>
#include <settings.h>

using namespace std;

ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    QPalette p = palette();
    QPixmap pix(":/images/bg.png");
    pix = pix.scaled(900, 750);
    p.setBrush(QPalette::Window, QBrush(pix));
    setPalette(p);

    img_black.load(":/images/black.png");
    img_white.load(":/images/white.png");
    img_cb.load(":/images/cb.png");

    CB.chesses[0] = {QPoint(1, 7), 1};
    CB.chesses[1] = {QPoint(10, 7), 1};
    CB.chesses[2] = {QPoint(4, 10), 1};
    CB.chesses[3] = {QPoint(7, 10), 1};
    CB.chesses[4] = {QPoint(4, 1), 2};
    CB.chesses[5] = {QPoint(7, 1), 2};
    CB.chesses[6] = {QPoint(1, 4), 2};
    CB.chesses[7] = {QPoint(10, 4), 2};
    CB.count = 8;

    state = 0;

    worker = new Worker();
    workerThread = new QThread();
    worker->moveToThread(workerThread);


    connect(this, SIGNAL(operate(Amazon *, char *)), worker, SLOT(doWork(Amazon *, char *)));
    connect(worker, SIGNAL(resultReady(char *)), this, SLOT(parseResult(char *)));
    connect(workerThread, &QThread::finished, worker, &Worker::deleteLater);

    RB_black = ((Widget *)parent)->st->RB_black;
    RB_white = ((Widget *)parent)->st->RB_white;

    connect(RB_black, SIGNAL(clicked()), this, SLOT(on_ChooseChess()));
    //st初始化应在cb前 否则RB_black指针未分配空间
    connect(RB_white, SIGNAL(clicked()), this, SLOT(on_ChooseChess()));

    workerThread->start();

    if (humanSide == 1)
    {
        opponent.go((char *)"new white", result);
    }
    else
    {
        emit operate(&opponent, (char *)"new black");
        PB_new->setEnabled(0);
        PB_regret->setEnabled(0);
        PB_error->setEnabled(0);
    }
}

void ChessBoard::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        pos = event->pos();
        CBEvent(getCBPos(pos));
    }
}

QPoint ChessBoard::getCBPos(QPoint pos)
{
    int x, y;
    if (pos.x() < 100 || pos.x() > 800 || pos.y() < 25 || pos.y() > 725)
        return QPoint(0, 0);

    x = 1 + (pos.x() - 100) / 70;
    y = 1 + (pos.y() - 25) / 70;
    return QPoint(x, y);
}

void ChessBoard::CBEvent(QPoint CBPos)
{
    Chess *tmp;

    if (state == 0 && (c = getChess(CBPos)) && c->type == humanSide)
    {
        state = 1;
        getMove(move, 0, CBPos);
    }
    else if (state == 1)
    {
        if ((tmp = getChess(CBPos)) && tmp->type == humanSide)
        {
            c = tmp;
            getMove(move, 0, CBPos);
            return;
        }
        else if (tmp)
        {
            return;
        }

        state = 2;

        CB.last_human = c->CBPos;
        c->CBPos = CBPos;
        CB.current_human = CBPos;
        getMove(move, 2, CBPos);
    }
    else if (state == 2)
    {
        if (!getChess(CBPos))
        {
            CB.chesses[CB.count] = {CBPos, 3};
            CB.count ++;

            getMove(move, 4, CBPos);

            char message[] = "move ";
            strcat(message, move);

            cout << "[Human] " << message << endl;
            emit operate(&opponent, message);
            state = 0;

            PB_new->setEnabled(0);
            PB_regret->setEnabled(0);
            PB_error->setEnabled(0);
        }
    }

    update();
}

Chess *ChessBoard::getChess(QPoint CBPos)
{
    for (int i = 0; i < CB.count; i++)
    {
        if (CB.chesses[i].CBPos == CBPos)
        {
            return &CB.chesses[i];
        }
    }

    return NULL;
}

void ChessBoard::getMove(char *move, int n, QPoint CBPos)
{
    move[n] = 'A' + CBPos.x() - 1;
    move[n + 1] = 'A' + CBPos.y() - 1;
}

void ChessBoard::parseResult(char *r)
{
    cout << "[AI] " << r << endl;

    QPoint p((int)r[5] - 64, (int)r[6] - 64);
    for (int i = 0; i < CB.count; i++)
    {
        if (CB.chesses[i].CBPos == p)
        {
            CB.last_point = p;
            CB.last_index = i;
            CB.chesses[i].CBPos.setX((int)r[7] - 64);
            CB.chesses[i].CBPos.setY((int)r[8] - 64);
        }
    }
    CB.chesses[CB.count] = {QPoint((int)r[9] - 64, (int)r[10] - 64), 3};
    CB.count ++;

    PB_new->setEnabled(1);
    PB_regret->setEnabled(1);
    PB_error->setEnabled(1);

    update();
}

void ChessBoard::newCB()
{
    cout << "new" << endl;
    state = 0;

    CB.chesses[0] = {QPoint(1, 7), 1};
    CB.chesses[1] = {QPoint(10, 7), 1};
    CB.chesses[2] = {QPoint(4, 10), 1};
    CB.chesses[3] = {QPoint(7, 10), 1};
    CB.chesses[4] = {QPoint(4, 1), 2};
    CB.chesses[5] = {QPoint(7, 1), 2};
    CB.chesses[6] = {QPoint(1, 4), 2};
    CB.chesses[7] = {QPoint(10, 4), 2};
    CB.count = 8;

    if (_humanSide == 1)
    {
        humanSide = 1;
        opponent.go((char *)"new white", result);
    }
    else
    {
        humanSide = 2;
        emit operate(&opponent, (char *)"new black");
        PB_new->setEnabled(0);
        PB_regret->setEnabled(0);
        PB_error->setEnabled(0);
    }

    update();
}

void ChessBoard::regret()
{
    cout << "regret" << endl;
    opponent.Board[opponent.last_step[0]][opponent.last_step[1]] = opponent.computerSide ^ 1;
    opponent.Board[opponent.last_step[2]][opponent.last_step[3]] = 2;
    opponent.Board[opponent.last_step[4]][opponent.last_step[5]] = 2;
    opponent.start = 0;

    CB.chesses[CB.last_index].CBPos = CB.last_point;
    getChess(CB.current_human)->CBPos = CB.last_human;
    CB.count -= 2;

    update();
}

void ChessBoard::error()
{
    cout << "error" << endl;
    CB.chesses[CB.last_index].CBPos = CB.last_point;
    CB.count --;

    update();

    char message[] = "error";
    emit operate(&opponent, message);
    PB_new->setEnabled(0);
    PB_regret->setEnabled(0);
    PB_error->setEnabled(0);
}

void ChessBoard::on_ChooseChess()
{
    if (sender() == RB_black)
    {
        _humanSide = 1;
    }
    else
    {
        _humanSide = 2;
    }
}

void ChessBoard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap img_cb_ = img_cb;
    int x, y;

    QPixmap tmpPix(img_cb_.size());
    tmpPix.fill(Qt::transparent);
    QPainter p1(&tmpPix);
    p1.setCompositionMode(QPainter::CompositionMode_Source);
    p1.drawPixmap(0, 0, img_cb_);
    p1.setCompositionMode(QPainter::CompositionMode_DestinationIn);

    for (int i = 0; i < CB.count; i++)
    {
        x = (CB.chesses[i].CBPos.x() - 1) * 70;
        y = (CB.chesses[i].CBPos.y() - 1) * 70;

        if (CB.chesses[i].type == 3)
        {
            p1.fillRect(x, y, 70, 70, QColor(0, 0, 0, 0));
        }
    }

    p1.end();
    img_cb_ = tmpPix;
    painter.drawPixmap(100, 25, 700, 700, img_cb_);

    for (int i = 0; i < CB.count; i++)
    {
        x = (CB.chesses[i].CBPos.x() - 1) * 70 + 100;
        y = (CB.chesses[i].CBPos.y() - 1) * 70 + 25;

        if (CB.chesses[i].type == 1)
        {
            painter.drawPixmap(x, y, 70, 70, img_black);
        }
        else if (CB.chesses[i].type == 2)
        {
            painter.drawPixmap(x, y, 70, 70, img_white);
        }
    }
}

ChessBoard::~ChessBoard()
{
    workerThread->quit();
    workerThread->wait();
}
