 #ifndef RANDOMEVENTDIALOG_H
#define RANDOMEVENTDIALOG_H

#include <QDialog>
#include <QList>

#include "Qevent.h"

namespace Ui {
class RandomEventDialog;
}

class RandomEventDialog : public QDialog
{
    Q_OBJECT

public:
    QList<Qevent> QRandomEventList;
    void occur();

    explicit RandomEventDialog(Qzuotijia* zuotijia,QWidget *parent = nullptr);
    ~RandomEventDialog();

private:
    Ui::RandomEventDialog *ui;

    Qzuotijia * zuotijia;
    void iniQRandomEventList();

};

#endif // RANDOMEVENTDIALOG_H
