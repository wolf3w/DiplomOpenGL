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
