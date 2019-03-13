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
//    if(stu2!=stu1)
//    {
//        qDebug()<<"不相等";
//    }

    user u1(1,"user1","123",2);

    teacher t1(1,&u1,"li4",1);

    group g1(&u1,"gp1",&t1,1);

    department d1(1,&g1,"study","haha");
    department d2(1,&g1,"fan","hehe");
//    if(d1 != d2)
//    {
//        qDebug()<<"不相等";
//    }
    qDebug()<<d1.getInfo();
    qDebug()<<d2.getInfo();

    studentDependence * dep1 = new studentDependence(&g1,&d1,"buzhang",1,&stu1);
    qDebug()<<dep1->getInfo();
    delete dep1;
}

MainWindow::~MainWindow()
{
    delete ui;
}
