#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QPalette>
#include <QPixmap>
#include <QBrush>
#include <titlebar.h>
#include <sidebar.h>
#include <chessboard.h>
#include <settings.h>


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public:
    TitleBar *titlebar;
    SideBar *sidebar;
    QStackedWidget *stacked_widget;
    ChessBoard *cb;
    Settings *st;

protected:
};
#endif // WIDGET_H
