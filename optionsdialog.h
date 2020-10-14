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
    explicit OptionsDialog(OGLWidget *oglwArg, QWidget *parent = nullptr);
    ~OptionsDialog();

private:
    Ui::OptionsDialog *ui;
    OGLWidget *oglw;
    QOpenGLFunctions_4_3_Core *ogl;
};

#endif // OPTIONSDIALOG_H
