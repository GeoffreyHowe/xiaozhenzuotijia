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
};
#endif // XIAOZHENZUOTIJIA_H
