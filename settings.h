#ifndef SETTINGS_H
#define SETTINGS_H

#include <QGroupBox>
#include <QWidget>
#include <QVBoxLayout>
#include <QRadioButton>

class Settings : public QWidget
{
    Q_OBJECT
public:
    explicit Settings(QWidget *parent = nullptr);
    QGroupBox *ChooseChess;
    QRadioButton *RB_black;
    QRadioButton *RB_white;

signals:

};

#endif // SETTINGS_H
