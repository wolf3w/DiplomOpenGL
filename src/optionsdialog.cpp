#include "headers/optionsdialog.h"
#include "ui_optionsdialog.h"

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
}

OptionsDialog::~OptionsDialog()
{
    ds = nullptr;
    delete ui;
}

void OptionsDialog::setDataStorage (DataStorage *dspointer)
{
    ds = dspointer;
}

void OptionsDialog::on_checkDT_stateChanged(int arg1)
{
}

void OptionsDialog::on_surfRedSpin_valueChanged(double arg1)
{
    float val = static_cast<float>(arg1);
    ds->setSurfaceRed(val);
}

void OptionsDialog::on_surfBlueSpin_valueChanged(double arg1)
{
    float val = static_cast<float>(arg1);
    ds->setSurfaceBlue(val);
}

void OptionsDialog::on_surfGreenSpin_valueChanged(double arg1)
{
    float val = static_cast<float>(arg1);
    ds->setSurfaceGreen(val);
}

void OptionsDialog::on_gridRedSpin_valueChanged(double arg1)
{
    float val = static_cast<float>(arg1);
    ds->setGridRed(val);
}

void OptionsDialog::on_gridBlueSpin_valueChanged(double arg1)
{
    float val = static_cast<float>(arg1);
    ds->setGridBlue(val);
}

void OptionsDialog::on_gridGreenSpin_valueChanged(double arg1)
{
    float val = static_cast<float>(arg1);
    ds->setGridGreen(val);
}
