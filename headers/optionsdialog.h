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
    void setDataStorage (DataStorage *dspointer);

private slots:
    void on_checkDT_stateChanged(int arg1);

    void on_surfRedSpin_valueChanged(double arg1);

    void on_surfBlueSpin_valueChanged(double arg1);

    void on_surfGreenSpin_valueChanged(double arg1);

    void on_gridRedSpin_valueChanged(double arg1);

    void on_gridBlueSpin_valueChanged(double arg1);

    void on_gridGreenSpin_valueChanged(double arg1);

private:
    Ui::OptionsDialog *ui;
    DataStorage *ds;
};

#endif // OPTIONSDIALOG_H
