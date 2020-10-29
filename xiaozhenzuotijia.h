#ifndef XIAOZHENZUOTIJIA_H
#define XIAOZHENZUOTIJIA_H

#include <QMainWindow>

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
    //    初始化字体
    void iniFont();

//    初始化关联信号与槽
    void iniconnect();
};
#endif // XIAOZHENZUOTIJIA_H
