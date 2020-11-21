#ifndef SHUDIALOG_H
#define SHUDIALOG_H

#include <QDialog>
//老师来了弹出该对话框，显示上海大学简介
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
