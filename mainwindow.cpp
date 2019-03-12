#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->connt = new DBconnt();
    qDebug() << this->connt->getDBinfo();
}

MainWindow::~MainWindow()
{
    delete ui;
}
