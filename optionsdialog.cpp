#include "optionsdialog.h"
#include "ui_optionsdialog.h"

OptionsDialog::OptionsDialog(OGLWidget *oglwArg, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    oglw = oglwArg;
    ogl = oglw->getOGL();

    //ogl->glEnable(GL_DEPTH_TEST);
    ui->checkDT->setChecked(ogl->glIsEnabled(GL_DEPTH_TEST));
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
    oglw = nullptr;
    ogl  = nullptr;
}

void OptionsDialog::on_checkDT_stateChanged(int arg1)
{
    if (ui->checkDT->isChecked())
    {
        ogl->glEnable(GL_DEPTH_TEST);
    }
    else
    {
        ogl->glDisable(GL_DEPTH_TEST);
    }
}
