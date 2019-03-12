#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->connt = new DBconnt();
    qDebug() << this->connt->getDBinfo();

    student stu1(1,true,"王五");

    qDebug()<<stu1.getinfo();

    student stu2;
    //stu2 = stu1;
    if(stu2!=stu1)
    {
        qDebug()<<"不相等";
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
