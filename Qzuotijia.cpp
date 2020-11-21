#include "Qzuotijia.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QFile>

Qzuotijia::Qzuotijia()
{
    //初始化初始属性
    Day = 1;        //第一天
    Time = 24;      //一天时间
    Health = 90;    //初始健康值
    Score = 400;    //初始纸面
    ExtraScore = 0; //初始竞赛加分
    tmpa = NULL;    //带加入事件指针
    tmpr = NULL;    //代移除事件指针

    //初始化玩家的事件列表（通过外部的json文件实现事件的更新和属性设置）
    QFile file(":/json/QincidentList.json");
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"Warnning"<<"can't open"<<endl;
        }

        QJsonParseError json_error;
        QJsonDocument parse_doucment = QJsonDocument::fromJson(file.readAll(), &json_error);

        //如果读取时没有出错，就按照设计的json文件结构解析事件列表并完成对做题家事件列表的初始化
        if(json_error.error == QJsonParseError::NoError)
            {
                if(parse_doucment.isArray())
                {
                    QJsonArray array = parse_doucment.array();
                    int size = array.size();
                    for(int i=0; i < size ; i++)
                    {
                        if(array[i].isObject())
                        {
                            QJsonObject ob = array[i].toObject();
                            Qincident* a1 ;
                            QListWidgetItem* Cando;
                            //qDebug()<<ob.value("name").toString()<<endl;
                            a1 = new Qincident(
                                        ob.value("name").toString(),
                                        ob.value("cTime").toInt(),
                                        ob.value("cScore").toInt(),
                                        ob.value("cHealth").toInt(),
                                        ob.value("cExtraScore").toInt(),
                                        ob.value("discription").toString()
                                        );
                            Cando = new QListWidgetItem(ob.value("name").toString());
                            CandoList.append(*a1);                          //添加事件列表
                            CandoItems.append(ob.value("name").toString()); //添加事件item列表

                            //删除申请动态内存空间，培养一个码农良好的编程习惯，
                            //因为在循环内申请，指针指向的之前申请到的动态内存空间就会被后面申请的覆盖
                            delete a1;
                            delete Cando;
                        }
                    }
                }
        }
}

Qzuotijia::~Qzuotijia()
{

}
//改变日期的函数，顺便发射日期改变的信号，通知相应组件刷新
void Qzuotijia::changeDay(int d)
{
    //如果改变后日期大于40，就把改变值修正一下。
    if(Day+d>40)
        d=40-Day;
    if(d!=0&&Day<40)
    {
        Day+=d;
        emit onDaychanged();
    }
}
//改变健康值的函数，顺便发射信号，通知相应组件刷新
void Qzuotijia::changeHealth(int h)
{
    if(h!=0)
    {
        Health+=h;
        emit onHealthchanged();
    }
}
//改变成绩，发射信号
void Qzuotijia::changeScore(int s)
{
    if(s!=0)
    {
        Score+=s;
        emit onScorechanged();
    }
}
//改变今天时间，发射信号
void Qzuotijia::changeTime(int t)
{
    if(t!=0)
    {
        Time-=t;
        emit onTimechanged();
    }
}
//改变竞赛加分，发射信号
void Qzuotijia::changeExtraScore(int e)
{
    if(e!=0&&e!=100)
    {
        ExtraScore+=e;
        emit onExtraScorechanged();
    }else if(e==100){
        ExtraScore *= 2;
        emit onExtraScorechanged();
    }
}


//获取成绩
QString Qzuotijia:: getScore()
{
    return QString::number(Score);
}
//获取时间
QString Qzuotijia:: getTime()
{
    return QString::number(Time);
}
//获取身心健康
QString Qzuotijia:: getHealth()
{
    return QString::number(Health);
}
//获取竞赛加分
QString Qzuotijia::getExtraScore()
{
    return QString::number(ExtraScore);
}
//获取可进行事件列表
QList<QString> Qzuotijia::getCandoItems()
{
    return CandoItems;
}
//获取进行中事件列表
QList<QString> Qzuotijia::getDoingItems()
{
    return  DoingItems;
}
//获取可进行事件item列表，方便初始化
QList<Qincident> Qzuotijia::getCandoList()
{
    return CandoList;
}
//获取日期
int Qzuotijia:: getDay()
{
    return Day;
}

//下一天事件，当下一天按钮点下，触发该事件，做题家进行当天的事件
void Qzuotijia::nextDay()
{
    if(Day<40)
    {
        Qincident Doing;
        //使用foreach遍历进行中事件，并让做题家做一下
        foreach(Doing,DoingList)
        {
            Do(Doing);
        }
    }
}

//存一下刚刚点击的可进行列表中的事件item，方便等会儿添加
void Qzuotijia::settmpItema(QListWidgetItem* tmp)
{
    this->tmpa = tmp;
//    qDebug()<<this->tmpa->text()<<endl;
}

//存一下刚刚点击的进行中列表中的事件item，方便等会儿移除
void Qzuotijia::settmpItemr(QListWidgetItem *tmpr)
{
    this->tmpr = tmpr;
    qDebug()<<this->tmpr->text()<<endl;
}

//给做题家的清单里面添加事件,返回值是剩余时间是否还能往清单内添加事件了
bool Qzuotijia::add()
{
    if(tmpa!=NULL)
    {
        //列表的同步
        DoingItems.append(tmpa->text());
        CandoItems.removeOne(tmpa->text());

        Qincident Doing;

        //使用foreach遍历进行中事件列表
        foreach(Doing,CandoList)
        {
            //判断一下这个事件能不能放进列表（主要还是时间合适不合适）
            if(Doing.name==tmpa->text()&&Time-Doing.cTime>=0)
            {
                DoingList.append(Doing);    //实现添加
                CandoList.removeOne(Doing); //实现移除
                changeTime(Doing.cTime);    //实时改变剩余时间
                return true;
            }
        }
    }
    return false;
}

//给做题家的清单里面移除事件
void Qzuotijia::remove()
{
    //和移入类似，但是因为移入进行了比较完备的判断，所以可以放心移除
    if(tmpr!=NULL)
    {
        //列表的同步
        DoingItems.removeOne(tmpr->text());
        CandoItems.append(tmpr->text());

        Qincident Doing;
        foreach(Doing,DoingList)
        {
            if(Doing.name==tmpr->text())
            {
                CandoList.append(Doing);
                DoingList.removeOne(Doing);
                changeTime(-Doing.cTime);//实时改变时间
            }
        }
    }
}


void Qzuotijia::Do(Qincident Doing)
{
    changeScore(Doing.cScore);              //根据要进行的事件的属性改成绩
    changeHealth(Doing.cHealth);            //根据要进行的事件的属性改身心健康
    changeExtraScore(Doing.cExtraScore);    //根据要进行的事件的属性改竞赛加分
//    qDebug()<<"进行事件："<<Doing.name;
//    qDebug()<<"cTime"<<":"<<Doing.cTime;
//    qDebug()<<"cScore"<<":"<<Doing.cScore;
//    qDebug()<<"cScoreExtraScore"<<":"<<Doing.cExtraScore;
}
