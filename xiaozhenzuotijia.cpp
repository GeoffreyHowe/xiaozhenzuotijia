#include "xiaozhenzuotijia.h"
#include "ui_xiaozhenzuotijia.h"
#include <QFontDatabase>
#include <QtWidgets/QMessageBox>
#include <QDebug>

#include "shudialog.h"
#include "aboutdialog.h"
#include "gameoverdialog.h"
#include "helpdialog.h"
#include "randomeventdialog.h"


XiaoZhenZuotijia::XiaoZhenZuotijia(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::XiaoZhenZuotijia)
{
    ui->setupUi(this);



    zuotijia = new Qzuotijia;   //初始化玩家

    iniFont();                  //初始化字体
    iniData();                  //初始化界面
    iniconnect();               //初始化信号与槽的链接
}

XiaoZhenZuotijia::~XiaoZhenZuotijia()
{
    //删除申请动态内存空间，培养一个码农良好的编程习惯
    delete ui;
    delete zuotijia;
    delete prbDay;
    delete labDay;
}
//下一天按钮点击事件
void XiaoZhenZuotijia::onbtnNextDay_clicked()
{
    zuotijia->changeDay(1);                 //改变做题家记录的自己的天数

    //实时刷新当前天数
    prbDay->setValue(zuotijia->getDay());
    labDay ->setText("第"+QString::number(zuotijia->getDay())+"天");

    //如果做题家前一天没睡好，减点儿身心健康
    if(zuotijia->getTime().toInt()<7)
    {
        zuotijia->changeHealth(-10);
    }

    zuotijia->nextDay();//做题家进入下一天，清点一下自己的清单，把相应事件给经历喽，把自己对应属性加加减减

    //判断当前天数，如果能被4整除，就来一个随机事件，弹出相应窗口
    if(zuotijia->getDay()%4==0)
    {
        RandomEventDialog * rand;
        rand = new RandomEventDialog(zuotijia);
        rand->exec();
    }

    //如果游戏到了第40天，游戏结束，弹出gameover窗口，展示最终得分
    if(zuotijia->getDay()==40)
    {
        GameOverDialog* over;
        over = new GameOverDialog(zuotijia);
        over->exec();
        this->close();
    }
}

//右箭头按钮点击事件
void XiaoZhenZuotijia::onbtnBegin_clicked()
{
    //判断一下做题家保存的待添加事件指针有没有指向正确的位置，
    //如果指向正确的位置，就进入循环，开始添加事件
    if(zuotijia->tmpa!=NULL)
    {
        //试图添加事件，添加事件会返回是否成功添加事件，根据返回值确定是否要进行列表的移动
        //如果想添加的事件占用时间太多，是不能成功添加嗷
        if(zuotijia->add())
        {
            //遍历界面上的可进行事件列表的item，和做题家保存的待添加事件指针指向的item的文本比较，
            //找到需要被移走的事件item的下标
            //主要还是QT的list不支持根据指针（或者item对象）移走列表中的项，所以只能用这种笨方法了
            for(int i=0;i<ui->CandoList->count();i++)
            {
                if(ui->CandoList->item(i)->text()==zuotijia->tmpa->text())
                {
                    ui->CandoList->takeItem(i);             //移去可办列表中的事件item
                    ui->DoingList->addItem(zuotijia->tmpa); //把那个item塞进进行中时间列表
//                    qDebug()<<"转移"<<zuotijia->getTime();
                    //剩余时间少于7h，时间界面刷新颜色，来提示下一天会掉身心健康
                    if(zuotijia->getTime().toInt()<7)
                    {
                        ui->labTime->setStyleSheet("color:red;background-color:orange");
//                        qDebug()<<"颜色";
                    }
                }
            }
        }else
        {
            //剩余时间太少了，弹一个提示框
            QMessageBox::warning(this,"么的时间了","当天剩余时间已经无法进行这一项活动了\n另外，剩余时间过少可能会影响你的身心健康哦！\n爆肝虽然能提升成绩，但也不要过度哦",QMessageBox::Cancel,QMessageBox::NoButton);
        }

    }
    //添加过一个事件就把待添加事件指针置零，防止重复添加
    zuotijia->tmpa=NULL;
}


//左箭头按钮点击事件
void XiaoZhenZuotijia::onbtnStop_clicked()
{
    //做题家把自己进行中列表中的事件移去，
    //因为移入进行中列表时，就已经经过了相对严格的逻辑判断，所以这里可以放心移除
    zuotijia->remove();

    //判断一下待移除事件列表指针是否指向有效值
    if(zuotijia->tmpr!=NULL)
    {
        //遍历事件列表，找到要操作的item，类似上面移入
        for(int i=0;i<ui->DoingList->count();i++)
        {
            if(ui->DoingList->item(i)->text()==zuotijia->tmpr->text())
            {
                ui->DoingList->takeItem(i);
                ui->CandoList->addItem(zuotijia->tmpr);

                //如果移除后，剩余时间能好好睡觉，就把颜色改回来
                if(zuotijia->getTime().toInt()>=7)
                {
                    ui->labTime->setStyleSheet("background:rgb(127, 127, 127);color:rgb(0, 255, 29)");
//                        qDebug()<<"颜色";
                }
            }
        }
    }
    //移除过一个事件就把待添加事件指针置零，防止重复移除
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

void XiaoZhenZuotijia::refreshExtraScore()
{
    ui->labExtraScore->setText(zuotijia->getExtraScore());
}


//初始化Label的字体
void XiaoZhenZuotijia::iniFont()
{
    // 添加字体文件（用了file
    int fontId = QFontDatabase::addApplicationFont(":/fonts/LCD2N___.TTF");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);

    //创建字体
    QFont LED;
    LED.setFamily(fontFamilies.at(0));
    LED.setPointSize(18);

    ui->labScore->setFont(LED);
    ui->labHealth->setFont(LED);
    ui->labTime->setFont(LED);
    ui->labExtraScore->setFont(LED);
}


//初始化信号与槽
void XiaoZhenZuotijia::iniconnect()
{
    connect(ui->btnNextDay,SIGNAL(clicked()),this,SLOT(onbtnNextDay_clicked()));//点击下一天时间+1

        //选中CandoList里的Item后通知做题家哪一个Item被选中了，方便等下做题家把这一项目放入自己的DoingList
    connect(ui->CandoList,SIGNAL(itemClicked ( QListWidgetItem * )),zuotijia,SLOT(settmpItema(QListWidgetItem* )));
    connect(ui->btnBegin,SIGNAL(clicked()),this,SLOT(onbtnBegin_clicked()));//根据做题家整理好的list刷新界面

        //选中DoingList里的Item后通知做题家哪一个Item被选中了，方便等下做题家把这一项目放入自己的TodoList
    connect(ui->DoingList,SIGNAL(itemClicked ( QListWidgetItem * )),zuotijia,SLOT(settmpItemr(QListWidgetItem* )));
    connect(ui->btnStop,SIGNAL(clicked()),this,SLOT(onbtnStop_clicked()));//根据做题家整理好的list刷新界面

    //一旦做题家剩余时间改变了，就通知组件完成属性的刷新，，其余也类似。
    connect(zuotijia,SIGNAL(onTimechanged()),this,SLOT(refreshTime()));
    connect(zuotijia,SIGNAL(onScorechanged()),this,SLOT(refreshScore()));
    connect(zuotijia,SIGNAL(onHealthchanged()),this,SLOT(refreshHealth()));
    connect(zuotijia,SIGNAL(onExtraScorechanged()),this,SLOT(refreshExtraScore()));
}


// 初始化界面数据
void XiaoZhenZuotijia::iniData()
{
    ui->labScore->setText(zuotijia->getScore());//让界面上的label获取到做题家当前成绩，完成初始化
    ui->labTime->setText(zuotijia->getTime());//让界面上的label获取到做题家剩余时间，完成初始化
    ui->labHealth->setText(zuotijia->getHealth());//让界面上的label获取到做题家当前身心健康，完成初始化
    ui->labExtraScore->setText(zuotijia->getExtraScore());//让界面上的label获取到做题家竞赛加分，完成初始化

    labDay = new QLabel;//状态栏的时间标签
    labDay ->setText("第"+QString::number(zuotijia->getDay())+"天");
    labDay->setAlignment(Qt::AlignCenter);
    labDay->setMinimumWidth(200);
    ui ->statusbar->addWidget(labDay);

    prbDay = new QProgressBar; //状态栏的进度条
    prbDay -> setMaximumWidth(500);
    prbDay -> setMinimum(0);
    prbDay -> setMaximum(40);
    prbDay -> setValue(zuotijia->getDay());//获取当前天数
    ui->statusbar->addWidget(prbDay);//把这个widget塞进状态栏（这个组件不支持可视化的在状态栏中布局）

    ui->CandoList->addItems(zuotijia->getCandoItems());//根据做题家保存的列表初始化CandoList

    //根据做题家保存的可进行事件列表，初始化界面中的列表的tooltip
    for(int i = 0;i < ui->CandoList->count();i++)
    {
        ui->CandoList->item(i)->setToolTip(zuotijia->getCandoList().at(i).description);
//        ui->CandoList->item(i)->setSizeHint();
    }

}

//老师来了按钮，点击展示一个文本编辑框，展示上海大学简介（从百度上拉的
void XiaoZhenZuotijia::on_pushButton_clicked()
{
    SHUDialog *shu = new SHUDialog;
    shu->exec();
    delete shu;
}

//关于，点击展示“关于”窗口，主要是本项目的一些背景
void XiaoZhenZuotijia::on_actionAbout_triggered()
{
    AboutDialog *about = new AboutDialog;
    about->exec();
    delete about;
}

//帮助，点击展示“帮助”窗口，主要展示游戏大概玩法
void XiaoZhenZuotijia::on_actionHelp_triggered()
{
    HelpDialog *help = new HelpDialog;
    help->exec();
    delete help;
}
