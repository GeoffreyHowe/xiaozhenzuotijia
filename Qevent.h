#include "Qincident.h"
#include "Qzuotijia.h"

class Qevent :public Qincident
{
public:
    int cDay;
    void influence(Qzuotijia& zuotijia);

    Qevent();
    Qevent(QString name,int cTime,int cScore,int cHealth,int cExtraScore,QString des,int cDay);
    ~Qevent();
};
