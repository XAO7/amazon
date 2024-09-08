#include "settings.h"
#include <iostream>

using namespace std;

Settings::Settings(QWidget *parent) : QWidget(parent)
{
    ChooseChess = new QGroupBox(tr("选择棋子(黑先 白后)"));
    ChooseChess->setParent(this);
    RB_black = new QRadioButton(tr("黑"));
    RB_white = new QRadioButton(tr("白"));

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(RB_black);
    vbox->addWidget(RB_white);

    ChooseChess->setLayout(vbox);
    ChooseChess->setFixedSize(200, 100);
    ChooseChess->setGeometry(100, 50, 200, 50);

    RB_black->setChecked(1);
}
