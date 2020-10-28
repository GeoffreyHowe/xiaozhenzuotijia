#include "xiaozhenzuotijia.h"
#include "ui_xiaozhenzuotijia.h"

XiaoZhenZuotijia::XiaoZhenZuotijia(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::XiaoZhenZuotijia)
{
    ui->setupUi(this);
}

XiaoZhenZuotijia::~XiaoZhenZuotijia()
{
    delete ui;
}

