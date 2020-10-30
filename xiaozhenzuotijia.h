#ifndef XIAOZHENZUOTIJIA_H
#define XIAOZHENZUOTIJIA_H

#include <QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QLabel>

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

private slots:
    void onbtnNextDay_clicked();//下一天
    void onbtnBegin_clicked();//两个列表间项目的移动
    void onbtnStop_clicked();//两个列表间项目的移动
    void refreshTime();//刷新时间
    void refreshScore();//刷新成绩
    void refreshHealth();//刷新身心健康

private:
    Ui::XiaoZhenZuotijia *ui;
    Qzuotijia *zuotijia;//玩家对象指针，在构造函数内new出来
    QProgressBar *prbDay;//状态栏进度条，显示第几天
    QLabel *labDay;//状态栏标签，显示第几天


    void iniFont();//    初始化字体
    void iniconnect();//    初始化关联信号与槽
    void iniData(); //初始化界面
};
#endif // XIAOZHENZUOTIJIA_H
