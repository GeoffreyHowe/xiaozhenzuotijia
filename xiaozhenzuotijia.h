#ifndef XIAOZHENZUOTIJIA_H
#define XIAOZHENZUOTIJIA_H

#include <QMainWindow>
#include <QtWidgets/QProgressBar>

#include "Qzuotijia.h"

QT_BEGIN_NAMESPACE
namespace Ui { class XiaoZhenZuotijia; }
QT_END_NAMESPACE

class XiaoZhenZuotijia : public QMainWindow
{
    Q_OBJECT

public:
    XiaoZhenZuotijia(QWidget *parent = nullptr);
    ~XiaoZhenZuotijia();

private:
    Ui::XiaoZhenZuotijia *ui;

    Qzuotijia *zuotijia;//玩家对象指针，在构造函数内new出来

    QProgressBar *prbDay;


    void iniFont();//    初始化字体

    void iniconnect();//    初始化关联信号与槽

    void iniData(); //初始化界面
};
#endif // XIAOZHENZUOTIJIA_H
