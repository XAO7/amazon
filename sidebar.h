#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QStyleOption>
#include <QPainter>

class SideBar: public QWidget
{
    Q_OBJECT
public:
    SideBar(QWidget *parent, QStackedWidget *stacked_widget);
    QPushButton *Button_new;
    QPushButton *Button_regret;
    QPushButton *Button_error;

private:
    QPushButton *Button_home;
    QPushButton *Button_settings;
    QStackedWidget *sw;

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_clicked();
};

#endif // SIDEBAR_H
