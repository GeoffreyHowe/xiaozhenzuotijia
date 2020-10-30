#include "Qincident.h"

void Qincident::setDescripition(QString des)
{
    description = des;
}

bool Qincident::operator==(const Qincident Q)
{
    if((name==Q.name)&&(cHealth==Q.cHealth)&&(cScore==Q.cScore)&&(cTime==Q.cTime)&&(description==Q.description))
        return true;
}

Qincident::Qincident(QString name,int cTime,int cScore,int cHealth,QString des):
    name(name),cHealth(cHealth),cScore(cScore),cTime(cTime),description(des)
{

}

Qincident::Qincident()
{

}

Qincident::~Qincident()
{

}
