#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPoint>
#include <QStyleOption>
#include <QPainter>

class TitleBar: public QWidget
{
    Q_OBJECT
public:
    TitleBar(QWidget *parent);

private:
    QPushButton *Button_min;
    QPushButton *Button_close;
    QHBoxLayout *HLayout_1;
    QLabel *Label_title;

    QPoint m_start;
    QPoint m_end;
    bool m_leftButtonPressed;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // TITLEBAR_H
