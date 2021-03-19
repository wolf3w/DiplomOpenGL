#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include "oglwidget.hpp"

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = nullptr);
    ~OptionsDialog();

private slots:
    void on_checkDT_stateChanged(int arg1);

private:
    Ui::OptionsDialog *ui;
};

#endif // OPTIONSDIALOG_H
