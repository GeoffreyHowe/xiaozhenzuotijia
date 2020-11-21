#include "Qincident.h"
#include "Qzuotijia.h"


//为了练习继承的应用而特意写的类，继承自Qincident
class Qevent :public Qincident
{
public:
    int cDay;
    void influence(Qzuotijia& zuotijia);    //和incident不同，event应当影响做题家，而不是做题家去进行事件

    Qevent();
    Qevent(QString name,int cTime,int cScore,int cHealth,int cExtraScore,QString des,int cDay);
    ~Qevent();
};
