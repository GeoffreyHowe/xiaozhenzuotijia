#include <QString>


class Qincident
{
public:
    QString name;
    int cHealth;
    int cScore;
    int cTime;
    QString description;

    void setDescripition(QString);

    bool operator==(const Qincident);

    Qincident(QString name,int cTime,int cScore,int cHealth,QString des);
    Qincident();
    ~Qincident();
};
