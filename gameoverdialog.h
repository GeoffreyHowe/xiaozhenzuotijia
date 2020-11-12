#ifndef GAMEOVERDIALOG_H
#define GAMEOVERDIALOG_H

#include <QDialog>
#include "Qzuotijia.h"

namespace Ui {
class GameOverDialog;
}

class GameOverDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameOverDialog(Qzuotijia *zuotijia ,QWidget *parent = nullptr);
    ~GameOverDialog();

    void iniFont();

private:
    Ui::GameOverDialog *ui;

    Qzuotijia * zuotijia;//从主窗口传递来的参数，主要是为了获取做题家的分数
};

#endif // GAMEOVERDIALOG_H
