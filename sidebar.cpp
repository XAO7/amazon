#include "sidebar.h"

SideBar::SideBar(QWidget *parent, QStackedWidget *stacked_widget): QWidget(parent)
{
    Button_home = new QPushButton(this);
    Button_home->setFixedSize(100, 70);
    Button_home->setObjectName("Button_home");
    Button_home->setGeometry(0, 70, 100, 70);
    Button_home->setStyleSheet(R"(
                QPushButton
                {
                    border-image:url(":/images/cb_1.png");
                    border:none;
                }
                )");

    Button_settings = new QPushButton(this);
    Button_settings->setFixedSize(100, 70);
    Button_settings->setObjectName("Button_settings");
    Button_settings->setGeometry(0, 140, 100, 70);
    Button_settings->setStyleSheet(R"(
                QPushButton
                {
                    border-image:url(":/images/st_0.png");
                    border:none;
                }
                )");

    Button_new = new QPushButton(this);
    Button_new->setFixedSize(100, 50);
    Button_new->setObjectName("Button_new");
    Button_new->setGeometry(0, 300, 100, 50);
    Button_new->setText("新的一局");

    Button_regret = new QPushButton(this);
    Button_regret->setFixedSize(100, 50);
    Button_regret->setObjectName("Button_regret");
    Button_regret->setGeometry(0, 375, 100, 50);
    Button_regret->setText("悔棋");

    Button_error = new QPushButton(this);
    Button_error->setFixedSize(100, 50);
    Button_error->setObjectName("Button_error");
    Button_error->setGeometry(0, 450, 100, 50);
    Button_error->setText("AI改错");

    QFont font;
    font.setPointSize(16);
    font.setBold(1);
    Button_new->setFont(font);
    Button_regret->setFont(font);
    Button_error->setFont(font);

    sw = stacked_widget;


    connect(Button_home, SIGNAL(clicked()), this, SLOT(on_clicked()));
    connect(Button_settings, SIGNAL(clicked()), this, SLOT(on_clicked()));
    connect(Button_new, SIGNAL(clicked()), sw->widget(0), SLOT(newCB()));
    connect(Button_regret, SIGNAL(clicked()), sw->widget(0), SLOT(regret()));
    connect(Button_error, SIGNAL(clicked()), sw->widget(0), SLOT(error()));
}

void SideBar::on_clicked()
{
    if (sender() == Button_home)
    {
        Button_home->setStyleSheet(R"(
                    QPushButton
                    {
                        border-image:url(":/images/cb_1.png");
                        border:none;
                    }
                    )");
        Button_settings->setStyleSheet(R"(
                    QPushButton
                    {
                        border-image:url(":/images/st_0.png");
                        border:none;
                    }
                    )");
        sw->setCurrentIndex(0);
    }
    else
    {
        Button_home->setStyleSheet(R"(
                    QPushButton
                    {
                        border-image:url(":/images/cb_0.png");
                        border:none;
                    }
                    )");
        Button_settings->setStyleSheet(R"(
                    QPushButton
                    {
                        border-image:url(":/images/st_1.png");
                        border:none;
                    }
                    )");
        sw->setCurrentIndex(1);
    }
}

void SideBar::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
