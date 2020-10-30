#include "xiaozhenzuotijia.h"
#include "ui_xiaozhenzuotijia.h"
#include <QFontDatabase>
#include <QDebug>
XiaoZhenZuotijia::XiaoZhenZuotijia(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::XiaoZhenZuotijia)
{
    ui->setupUi(this);



    zuotijia = new Qzuotijia;//初始化玩家

    iniFont();//初始化字体
    iniData();//初始化界面
    iniconnect();//初始化信号与槽的链接
}

XiaoZhenZuotijia::~XiaoZhenZuotijia()
{
    delete ui;
    delete zuotijia;
    delete prbDay;
    delete labDay;
}
//下一天按钮点击事件
void XiaoZhenZuotijia::onbtnNextDay_clicked()
{
    zuotijia->changeDay(1);
    prbDay->setValue(zuotijia->getDay());
    labDay ->setText("第"+QString::number(zuotijia->getDay())+"天");

    zuotijia->nextDay();
}
//右箭头按钮点击事件
void XiaoZhenZuotijia::onbtnBegin_clicked()
{
    if(zuotijia->tmpa!=NULL)
    {
        for(int i=0;i<ui->CandoList->count();i++)
        {
            if(ui->CandoList->item(i)->text()==zuotijia->tmpa->text())
            {
                ui->CandoList->takeItem(i);
                ui->DoingList->addItem(zuotijia->tmpa->text());
            }
        }
    }
    zuotijia->tmpa=NULL;
}
//左箭头按钮点击事件
void XiaoZhenZuotijia::onbtnStop_clicked()
{
    if(zuotijia->tmpr!=NULL)
    {
        for(int i=0;i<ui->DoingList->count();i++)
        {
            if(ui->DoingList->item(i)->text()==zuotijia->tmpr->text())
            {
                ui->DoingList->takeItem(i);
                ui->CandoList->addItem(zuotijia->tmpr->text());
            }
        }
    }
    zuotijia->tmpr=NULL;
}
//刷新今天时间Label
void XiaoZhenZuotijia::refreshTime()
{
    ui->labTime->setText(zuotijia->getTime());
}
//刷新纸面成绩Label
void XiaoZhenZuotijia::refreshScore()
{
    ui->labScore->setText(zuotijia->getScore());
}
//刷新身心健康Label
void XiaoZhenZuotijia::refreshHealth()
{
    ui->labHealth->setText(zuotijia->getHealth());
}
//初始化Label的字体
void XiaoZhenZuotijia::iniFont()
{
    // 添加字体文件
    int fontId = QFontDatabase::addApplicationFont(":/fonts/LCD2N___.TTF");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);

    //创建字体
    QFont LED;
    LED.setFamily(fontFamilies.at(0));
    LED.setPointSize(18);

    ui->labScore->setFont(LED);
    ui->labHealth->setFont(LED);
    ui->labTime->setFont(LED);
}
//初始化信号与槽
void XiaoZhenZuotijia::iniconnect()
{
    connect(ui->btnNextDay,SIGNAL(clicked()),this,SLOT(onbtnNextDay_clicked()));//点击下一天时间+1
        //选中CandoList里的Item后通知做题家哪一个Item被选中了，方便等下做题家把这一项目放入自己的DoingList
    connect(ui->CandoList,SIGNAL(itemClicked ( QListWidgetItem * )),zuotijia,SLOT(settmpItema(QListWidgetItem* )));
    connect(ui->btnBegin,SIGNAL(clicked()),zuotijia,SLOT(add()));//通知做题家整理自己的list
    connect(ui->btnBegin,SIGNAL(clicked()),this,SLOT(onbtnBegin_clicked()));//根据做题家整理好的list刷新界面

        //选中DoingList里的Item后通知做题家哪一个Item被选中了，方便等下做题家把这一项目放入自己的TodoList
    connect(ui->DoingList,SIGNAL(itemClicked ( QListWidgetItem * )),zuotijia,SLOT(settmpItemr(QListWidgetItem* )));
    connect(ui->btnStop,SIGNAL(clicked()),zuotijia,SLOT(remove()));//通知做题家整理自己的list
    connect(ui->btnStop,SIGNAL(clicked()),this,SLOT(onbtnStop_clicked()));//根据做题家整理好的list刷新界面

    connect(zuotijia,SIGNAL(onTimechanged()),this,SLOT(refreshTime()));
    connect(zuotijia,SIGNAL(onScorechanged()),this,SLOT(refreshScore()));
    connect(zuotijia,SIGNAL(onHealthchanged()),this,SLOT(refreshHealth()));
}

void XiaoZhenZuotijia::iniData()
{
    ui->labScore->setText(zuotijia->getScore());
    ui->labTime->setText(zuotijia->getTime());
    ui->labHealth->setText(zuotijia->getHealth());

    labDay = new QLabel;//状态栏的时间标签
    labDay ->setText("第"+QString::number(zuotijia->getDay())+"天");
    labDay->setAlignment(Qt::AlignCenter);
    labDay->setMinimumWidth(200);
    ui ->statusbar->addWidget(labDay);

    prbDay = new QProgressBar; //状态栏的进度条
    prbDay -> setMaximumWidth(500);
    prbDay -> setMinimum(0);
    prbDay -> setMaximum(40);
    prbDay -> setValue(zuotijia->getDay());
    ui->statusbar->addWidget(prbDay);

    ui->CandoList->addItems(zuotijia->getCandoItems());//初始化CandoList

}

