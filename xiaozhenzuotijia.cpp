#include "xiaozhenzuotijia.h"
#include "ui_xiaozhenzuotijia.h"
#include <QFontDatabase>

XiaoZhenZuotijia::XiaoZhenZuotijia(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::XiaoZhenZuotijia)
{
    ui->setupUi(this);

    zuotijia = new Qzuotijia;




    iniFont();//初始化字体

    iniData();//初始化界面
}

XiaoZhenZuotijia::~XiaoZhenZuotijia()
{
    delete ui;
    delete zuotijia;
    delete prbDay;
}

void XiaoZhenZuotijia::iniFont()
{
    // 添加字体文件
    int fontId = QFontDatabase::addApplicationFont(":/fonts/LCD2N___.TTF");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);

    //创建字体
    QFont LED;
    LED.setFamily(fontFamilies.at(0));
    LED.setPointSize(12);

    ui->labScore->setFont(LED);
    ui->labHealth->setFont(LED);
    ui->labTime->setFont(LED);
}

void XiaoZhenZuotijia::iniData()
{
    ui->labScore->setText(zuotijia->getScore());
    ui->labTime->setText(zuotijia->getTime());
    ui->labHealth->setText(zuotijia->getHealth());

    prbDay = new QProgressBar; //状态栏的进度条
    prbDay -> setMaximumWidth(500);
    prbDay -> setMinimum(0);
    prbDay -> setMaximum(40);
    prbDay -> setValue(zuotijia->getDay());
    ui->statusbar->addWidget(prbDay);


}

