#include "headers/mainwindow.h"
#include "headers/optionsdialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Создадим действия для панели */
    QAction *pressOption = new QAction(tr("Настройки"), this);
    QAction *pressAbout  = new QAction(tr("О приложении"), this);

    connect(pressAbout, &QAction::triggered, this, &MainWindow::printAbout);
    connect(pressOption, &QAction::triggered, this, &MainWindow::optionsWindow);

    ui->menuBar->addAction(pressOption);
    ui->menuBar->addAction(pressAbout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printAbout ()
{
    QString textAbout("ВКР. Специальность 09.03.03"
                      "\'Прикладная информатика\'\n"
                      "Выполнил: Чумаков А. А.\n"
                      "Тема: \'Численное решение задач нелинейных "
                      "уравнений Клейна-Гордона и "
                      "их визуализация методами OpenGL\'\n"
                      "Управление:\n"
                      "W,A,S,D - перемещение камеры\n"
                      "R - вернуть камеру в исходное положение\n"
                      "N - следующие 10 итераций\n"
                      "Мышь - изменение направления камеры");
    QMessageBox::information(this, "О приложении", textAbout);
}

void MainWindow::optionsWindow ()
{
    OptionsDialog optionsdialog(this);
    optionsdialog.setModal(true);
    optionsdialog.exec();
}
