#include "Qzuotijia.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QFile>

Qzuotijia::Qzuotijia()
{
    //初始化初始属性
    Day = 1;
    Time = 24;
    Health = 90;
    Score = 400;
    ExtraScore = 0;
    tmpa = NULL;
    tmpr = NULL;

    //初始化玩家的事件列表（通过外部的json文件实现事件的更新和属性设置）
    QFile file(":/json/QincidentList.json");
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"Warnning"<<"can't open"<<endl;
        }

        QJsonParseError json_error;
        QJsonDocument parse_doucment = QJsonDocument::fromJson(file.readAll(), &json_error);

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
                            CandoList.append(*a1);
                            CandoItems.append(ob.value("name").toString());
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

void Qzuotijia::changeExtraScore(int e)
{
    if(e!=0)
    {
        ExtraScore+=e;
        emit onExtraScorechanged();
    }
}



QString Qzuotijia:: getScore()
{
    return QString::number(Score);
}
QString Qzuotijia:: getTime()
{
    return QString::number(Time);
}
QString Qzuotijia:: getHealth()
{
    return QString::number(Health);
}

QString Qzuotijia::getExtraScore()
{
    return QString::number(ExtraScore);
}

QList<QString> Qzuotijia::getCandoItems()
{
    return CandoItems;
}

QList<QString> Qzuotijia::getDoingItems()
{
    return  DoingItems;
}

QList<Qincident> Qzuotijia::getCandoList()
{
    return CandoList;
}

int Qzuotijia:: getDay()
{
    return Day;
}
//下一天事件，当下一天按钮点下，触发该事件
void Qzuotijia::nextDay()
{
    if(Day<40)
    {
        Qincident Doing;
        foreach(Doing,DoingList)
        {
            Do(Doing);
        }
    }
}

void Qzuotijia::settmpItema(QListWidgetItem* tmp)
{
    this->tmpa = tmp;
//    qDebug()<<this->tmpa->text()<<endl;
}

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
        DoingItems.append(tmpa->text());
        CandoItems.removeOne(tmpa->text());

        Qincident Doing;
        foreach(Doing,CandoList)
        {
            if(Doing.name==tmpa->text()&&Time-Doing.cTime>=0)
            {
                DoingList.append(Doing);
                CandoList.removeOne(Doing);
                changeTime(Doing.cTime);
                return true;
            }
        }
    }
    return false;
}
//给做题家的清单里面移除事件
void Qzuotijia::remove()
{
    if(tmpr!=NULL)
    {
        DoingItems.removeOne(tmpr->text());
        CandoItems.append(tmpr->text());

        Qincident Doing;
        foreach(Doing,DoingList)
        {
            if(Doing.name==tmpr->text())
            {
                CandoList.append(Doing);
                DoingList.removeOne(Doing);
                changeTime(-Doing.cTime);
            }
        }
    }
}


void Qzuotijia::Do(Qincident Doing)
{
    changeScore(Doing.cScore);
    changeHealth(Doing.cHealth);
    changeExtraScore(Doing.cExtraScore);
//    qDebug()<<"进行事件："<<Doing.name;
//    qDebug()<<"cTime"<<":"<<Doing.cTime;
//    qDebug()<<"cScore"<<":"<<Doing.cScore;
//    qDebug()<<"cScoreExtraScore"<<":"<<Doing.cExtraScore;
}
