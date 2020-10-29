#include "Qzuotijia.h"





Qzuotijia::Qzuotijia()
{
    //初始化初始属性
    Day = 1;
    Time = 16;
    Health = 90;
    Score = 400;
}

Qzuotijia::~Qzuotijia()
{

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
int Qzuotijia:: getDay()
{
    return Day;
}
