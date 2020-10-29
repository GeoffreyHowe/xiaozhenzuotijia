# include <QObject>

class Qzuotijia :public QObject
{
    Q_OBJECT;

private:
    int Day;   //属性，游戏进行天数
    int Health;//健康值，影响最终游戏分数
    int Score;//成绩，基本决定最终游戏分值
    int Time;//当天剩余的时间


public:
    Qzuotijia();
    ~Qzuotijia();

    void changeDay(int);
    void changeHealth(int);
    void changeScore(int);
    void changeTime(int);

    QString getScore();
    QString getTime();
    QString getHealth();
    int getDay();


private slots:




signals:
    void onDaychanged(int);
    void onHealthchanged(int);
    void onScorechanged(int);
    void onTimechanged(int);


};
