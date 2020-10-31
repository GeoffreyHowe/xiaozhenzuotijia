# include <QObject>
# include "Qincident.h"
#include <QtWidgets/QListWidgetItem>

class Qzuotijia :public QObject
{
    Q_OBJECT;

private:
    int Day;   //属性，游戏进行天数
    int Health;//健康值，影响最终游戏分数
    int Score;//成绩，基本决定最终游戏分值
    int Time;//当天剩余的时间
    QList<Qincident> CandoList;
    QList<Qincident> DoingList;
    QList<QString> CandoItems;
    QList<QString> DoingItems;


    void addCando(Qincident a);
    void Do(Qincident Doing);//进行Doing清单上的事情


public:
    QListWidgetItem* tmpa;
    QListWidgetItem* tmpr;


    Qzuotijia();
    ~Qzuotijia();

    void changeDay(int);
    void changeHealth(int);
    void changeScore(int);
    void changeTime(int);

    QString getScore();
    QString getTime();
    QString getHealth();
    QList<QString> getCandoItems();
    QList<QString> getDoingItems();
    QList<Qincident> getCandoList();
    int getDay();

    void nextDay();



private slots:
    void settmpItema(QListWidgetItem* tmpa);//获取当前选中的CandoList列表内当前选中的item
    void settmpItemr(QListWidgetItem* tmpr);//获取当前选中的DoingList列表内当前选中的item
    void add();
    void remove();


signals:
    void onDaychanged();//当日期改变，发射的信号，
    void onHealthchanged();//当身心健康改变，发射的信号，
    void onScorechanged();//当成绩改变，发射的信号，
    void onTimechanged();//当今天剩余时间改变，发射的信号，


};
