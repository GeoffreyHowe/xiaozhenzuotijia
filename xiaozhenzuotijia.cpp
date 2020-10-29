#include "xiaozhenzuotijia.h"
#include "ui_xiaozhenzuotijia.h"
#include <QFontDatabase>

XiaoZhenZuotijia::XiaoZhenZuotijia(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::XiaoZhenZuotijia)
{
    ui->setupUi(this);

    //初始化字体
    iniFont();
}

XiaoZhenZuotijia::~XiaoZhenZuotijia()
{
    delete ui;
}

void XiaoZhenZuotijia::iniFont()
{
    // 添加字体文件
    int fontId = QFontDatabase::addApplicationFont(":/fonts/LCD2N___.TTF");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);

    //创建字体
    QFont LED;
    LED.setFamily(fontFamilies.at(0));
}

