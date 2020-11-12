#include "gameoverdialog.h"
#include "ui_gameoverdialog.h"

#include <QFontDatabase>



GameOverDialog::GameOverDialog(Qzuotijia *zuotijia,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOverDialog),
    zuotijia(zuotijia)
{
    ui->setupUi(this);
    iniFont();
}

GameOverDialog::~GameOverDialog()
{
    delete ui;
}
void GameOverDialog::iniFont()
{
    int fontId = QFontDatabase::addApplicationFont(":/fonts/LCD2N___.TTF");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);

    //创建字体
    QFont LED;
    LED.setFamily(fontFamilies.at(0));
    LED.setPointSize(18);

    ui->labScore->setText(
                QString::number(
                    zuotijia->getScore().toInt()*zuotijia->getHealth().toInt()/100+zuotijia->getExtraScore().toInt())
                );


}
