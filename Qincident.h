#pragma once

#include <QString>


class Qincident
{
public:
    QString name;
    int cHealth;
    int cScore;
    int cTime;
    int cExtraScore;
    QString description;

    void setDescripition(QString);

    bool operator==(const Qincident);

    Qincident(QString name,int cTime,int cScore,int cHealth,int cExtraScore,QString des);
    Qincident();
    ~Qincident();
};
