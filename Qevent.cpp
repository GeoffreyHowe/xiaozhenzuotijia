#include "Qevent.h"

void Qevent::influence(Qzuotijia &zuotijia)
{
    //根据事件相应属性去影响做题家
    zuotijia.changeDay(this->cDay);
    zuotijia.changeTime(this->cTime);
    zuotijia.changeScore(this->cScore);
    zuotijia.changeHealth(this->cHealth);
    zuotijia.changeExtraScore(this->cExtraScore);
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
