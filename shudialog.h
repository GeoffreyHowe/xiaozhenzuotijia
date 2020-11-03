#ifndef SHUDIALOG_H
#define SHUDIALOG_H

#include <QDialog>

namespace Ui {
class SHUDialog;
}

class SHUDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SHUDialog(QWidget *parent = nullptr);
    ~SHUDialog();

private:
    Ui::SHUDialog *ui;
};

#endif // SHUDIALOG_H
