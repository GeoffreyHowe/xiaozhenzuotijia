#include "Qevent.h"

void Qevent::influence(Qzuotijia &zuotijia)
{
    zuotijia.changeDay(this->cDay);
    zuotijia.changeTime(this->cTime);
    zuotijia.changeScore(this->cScore);
    zuotijia.changeHealth(this->cHealth);
}

Qevent::Qevent()
{

}

Qevent::Qevent(QString name,int cTime,int cScore,int cHealth,int cExtraScore,QString des,int cDay):
    Qincident(name,cTime,cScore,cHealth,cExtraScore,des),cDay(cDay)
{

}

Qevent::~Qevent()
{

}
