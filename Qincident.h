#pragma once

#include <QString>


class Qincident
{
public:
    QString name;   //事件名字
    int cHealth;    //会改变的身心健康值
    int cScore;     //会改变的纸面成绩值
    int cTime;      //会改变的当天时间值
    int cExtraScore;//会改变的竞赛加分值
    QString description;//事件描述，将会在事件item上作为tooltip展示


    bool operator==(const Qincident);//重载==运算符，使用容器和foreach时必须提供，不然会报错（惨痛教训

    Qincident(QString name,int cTime,int cScore,int cHealth,int cExtraScore,QString des);
    Qincident();
    ~Qincident();
};
