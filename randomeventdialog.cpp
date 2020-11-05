#include "ui_randomeventdialog.h"
#include "randomeventdialog.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QTime>

void RandomEventDialog::occur()
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    int i = qrand()%QRandomEventList.count();
    QRandomEventList.value(i).influence(*zuotijia);
    this->setWindowTitle("【突发事件！！！】————"+QRandomEventList.value(i).name);

    ui->textBrowser->setText(QRandomEventList.value(i).description);
}

RandomEventDialog::RandomEventDialog(Qzuotijia* zuotijia,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RandomEventDialog),
    zuotijia(zuotijia)
{
    ui->setupUi(this);
    iniQRandomEventList();
    occur();
}

RandomEventDialog::~RandomEventDialog()
{
    delete ui;
}
//初始化随机事件列表
void RandomEventDialog::iniQRandomEventList()
{
    QFile file(":/json/QrandomEventList.json");
            if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                qDebug()<<"Warnning"<<"can't open"<<endl;
            }

            QJsonParseError json_error;
            QJsonDocument parse_doucment = QJsonDocument::fromJson(file.readAll(), &json_error);

            if(json_error.error == QJsonParseError::NoError)
                {
                    if(parse_doucment.isArray())
                    {
                        QJsonArray array = parse_doucment.array();
                        int size = array.size();
                        for(int i=0; i < size ; i++)
                        {
                            if(array[i].isObject())
                            {
                                QJsonObject ob = array[i].toObject();
                                Qevent* a1 ;
                                //qDebug()<<ob.value("name").toString()<<endl;
                                a1 = new Qevent(
                                            ob.value("name").toString(),
                                            ob.value("cTime").toInt(),
                                            ob.value("cScore").toInt(),
                                            ob.value("cHealth").toInt(),
                                            ob.value("cExtraScore").toInt(),
                                            ob.value("discription").toString(),
                                            ob.value("cDay").toInt()
                                            );
                                QRandomEventList.append(*a1);
                                delete a1;
                            }
                        }
                    }
            }
}
