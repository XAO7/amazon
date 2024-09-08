#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(1000, 800);
    setWindowFlags(Qt::FramelessWindowHint);

    titlebar = new TitleBar(this);
    titlebar->setFixedSize(900, 50);
    titlebar->setGeometry(100, 0, 900, 50);

    st = new Settings(this);
    st->setFixedSize(900, 750);
    st->setGeometry(100, 50, 900, 750);

    cb = new ChessBoard(this);
    cb->setFixedSize(900, 750);
    cb->setGeometry(100, 50, 900, 750);

    stacked_widget = new QStackedWidget(this);
    stacked_widget->insertWidget(0, cb);
    stacked_widget->insertWidget(1, st);
    stacked_widget->setGeometry(100, 50, 900, 750);

//    cout << cb->parent() << stacked_widget << endl;
//cb parent由Widget变为StackedWidget

    sidebar = new SideBar(this, stacked_widget);
    sidebar->setFixedSize(100, 800);
    sidebar->setGeometry(0, 0, 100, 800);

    cb->PB_new = sidebar->Button_new;
    cb->PB_regret = sidebar->Button_regret;
    cb->PB_error = sidebar->Button_error;

    stacked_widget->setCurrentIndex(0);

    setStyleSheet("TitleBar{background-color:DarkSlateBlue;} SideBar{background-color:Grey;}");

}

Widget::~Widget()
{
}
