#include "titlebar.h"

TitleBar::TitleBar(QWidget *parent): QWidget(parent)
{
    Button_min = new QPushButton(this);
    Button_min->setFixedSize(40, 40);
    Button_min->setObjectName("Button_min");
    Button_min->setGeometry(780, 5, 40, 40);
    Button_min->setStyleSheet(R"(
                QPushButton
                {
                    border-image:url(":/images/min_0.png");
                    border:none;
                }

                QPushButton:hover
                {
                    border-image:url(":/images/min_1.png");
                    border:none;
                }
                )");

    Button_close = new QPushButton(this);
    Button_close->setFixedSize(40, 40);
    Button_close->setObjectName("Button_close");
    Button_close->setGeometry(850, 5, 40, 40);
    Button_close->setStyleSheet(R"(
                QPushButton
                {
                    border-image:url(":/images/close_0.png");
                    border:none;
                }

                QPushButton:hover
                {
                    border-image:url(":/images/close_1.png");
                    border:none;
                }
                )");

    Label_title = new QLabel(this);
    Label_title->setText("Amazon Chess");
    Label_title->setGeometry(285, 0, 350, 50);
    QFont font;
    font.setBold(1);
    font.setLetterSpacing(QFont::PercentageSpacing, 125);
    font.setPointSize(30);
    font.setFamily(tr("Consolas"));
    QPalette p;
    p.setColor(QPalette::WindowText, Qt::white);
    Label_title->setFont(font);
    Label_title->setPalette(p);

    connect(Button_min, SIGNAL(clicked()), parent, SLOT(showMinimized()));
    connect(Button_close, SIGNAL(clicked()), parent, SLOT(close()));
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{

    // 鼠标左键按下事件
    if (event->button() == Qt::LeftButton)
    {
        // 记录鼠标左键状态
        m_leftButtonPressed = true;
        //记录鼠标在屏幕中的位置
        m_start = event->globalPos();
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{

    // 持续按住才做对应事件
    if(m_leftButtonPressed)
    {
        //将父窗体移动到父窗体原来的位置加上鼠标移动的位置：event->globalPos()-m_start
        parentWidget()->move(parentWidget()->geometry().topLeft() +
                             event->globalPos() - m_start);
        //将鼠标在屏幕中的位置替换为新的位置
        m_start = event->globalPos();
    }
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{

    // 鼠标左键释放
    if (event->button() == Qt::LeftButton)
    {
        // 记录鼠标状态
        m_leftButtonPressed = false;
    }
}

void TitleBar::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}



