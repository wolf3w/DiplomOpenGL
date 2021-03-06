#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QOpenGLFunctions>
#include <QMessageBox>

#include "datastorage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DataStorage *dsMain;

    /* Вывод о приложении */
    void printAbout ();
    /* Открыть окно настроек */
    void optionsWindow ();
};

#endif // MAINWINDOW_H
