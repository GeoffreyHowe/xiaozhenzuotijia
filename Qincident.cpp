#include "Qincident.h"

void Qincident::setDescripition(QString des)
{
    description = des;
}

bool Qincident::operator==(const Qincident Q)
{
    if((name==Q.name)&&(cHealth==Q.cHealth)&&(cScore==Q.cScore)&&(cTime==Q.cTime)&&(description==Q.description)&&(cExtraScore==Q.cExtraScore))
        return true;
}

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
