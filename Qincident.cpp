#include "Qincident.h"


//重载==运算符，因为要用一个改类的QList容器，且要用foreach遍历它，必定要提供一个==运算符的重载
bool Qincident::operator==(const Qincident Q)
{
    if((name==Q.name)&&(cHealth==Q.cHealth)&&(cScore==Q.cScore)&&(cTime==Q.cTime)&&(description==Q.description)&&(cExtraScore==Q.cExtraScore))
        return true;
    else
        return false;

}

//构造函数，初始化数据
Qincident::Qincident(QString name,int cTime,int cScore,int cHealth,int cExtraScore,QString des):
    name(name),cHealth(cHealth),cScore(cScore),cTime(cTime),cExtraScore(cExtraScore),description(des)
{

}

Qincident::Qincident()
{

}

Qincident::~Qincident()
{

}
