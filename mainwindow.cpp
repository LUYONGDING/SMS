#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->db = new DBconnt();
//    qDebug() << this->db->getDBinfo();
    this->setMouseTracking(true);

    this->us = new user();

    this->setWindowTitle("学生社团管理系统");   //设置窗口标题
    this->setWindowIcon(QIcon(":/mainWin/Icon/guishen_0131ev05b08mg01.png"));   //设置窗口图标

    connect(ui->pushButton_clear,&QPushButton::clicked,[=](){   //清除按钮：点击后将用户名和密码置空
        ui->lineEdit_passwd->setText("");
        ui->lineEdit_userName->setText("");
    });
    connect(ui->pushButton_login,&QPushButton::clicked,this,&MainWindow::userLogin);    //连接登陆按钮和登陆槽函数

    ui->label_regist->installEventFilter(this); //安装事件过滤器，监听点击事件

//    connect(this->regist,&registForm::destroyed,[=](){
//        this->show();
//    });
    this->timer = new QTimer(this);
}

MainWindow::~MainWindow()
{
    if(NULL == this->db)
    {
        delete db;
        db = NULL;
    }
//    if(NULL == this->regist)
//    {
//        delete regist;
//        regist = NULL;
//    }
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *event) //使用绘图事件设置背景
{
    QPainter painter(this);
    painter.drawPixmap(0,0,520,520,QPixmap(":/mainWin/background/guishen_0039ev05a07.jpg"));
}

void MainWindow::userLogin()    //登陆槽函数
{

    db->openDB();
    bool ret = false;
    ret = db->query->prepare("SELECT * FROM `user` WHERE `user`.user_name = :name AND `user`.user_passwd = :passwd");
    db->query->bindValue(":name",ui->lineEdit_userName->text());
    db->query->bindValue(":passwd",ui->lineEdit_passwd->text());
    ret = db->query->exec();
    if(!ret)
    {
        QMessageBox::critical(this,"错误",QString(db->query->lastError().text()));
        db->closeDB();
        return;
    }
    else if(!(db->query->next()))
    {
        QMessageBox::critical(this,"错误","账号或密码错误");
        db->closeDB();
        return;
    }
    else
    {
        this->us->setUserType(db->query->value("user_type").toInt());
        this->us->setUserID(db->query->value("user_id").toInt());
        this->us->setUserPasswd(db->query->value("user_passwd").toString());
        this->us->setUserName(db->query->value("user_name").toString());
        if(0==us->getUserType())
        {
            QMessageBox::information(this,"login","管理员登录成功");
            //code
        }
        if(1==us->getUserType())
        {
            QMessageBox::information(this,"login","教师登录成功");

            this->tchmain = new TeacherMainWindow();
            connect(tchmain,&TeacherMainWindow::loginOut,this,&MainWindow::show);
            if(!this->tchmain->isWindow())
            {
                delete this->tchmain;
            }
            connect(this,&MainWindow::sendUserInfo,tchmain,&TeacherMainWindow::getUserInfo);
            connect(this->timer,&QTimer::timeout,[=](){
                tchmain->show();
                emit sendUserInfo(this->us);
                this->timer->stop();
            });
            this->timer->start(1000);
            this->hide();
            //code
        }
        if(2==us->getUserType())
        {
            QMessageBox::information(this,"login","社团登录成功");
            this->grpmain = new GroupMainWindow();
            if(!this->grpmain->isWindow())
            {
                delete this->tchmain;
            }
            connect(this,&MainWindow::sendUserInfo,grpmain,&GroupMainWindow::getUserInfo);
            connect(this->timer,&QTimer::timeout,[=](){
                grpmain->show();
                emit sendUserInfo(us);
                this->timer->stop();
            });
            this->timer->start(1000);
            this->hide();
            //code
        }
        db->closeDB();
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->label_regist)
    {
        if(event->type() == QEvent::MouseMove)
        {
            this->setCursor(Qt::PointingHandCursor);
        }
        else
        {
            this->setCursor(Qt::ArrowCursor);
        }
        if(event->type() == QEvent::MouseButtonPress)
        {
            //QMessageBox::information(this,"regist","注册");
            //code
            regist = new registForm(this);
            regist->show();
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return MainWindow::eventFilter(watched,event);
    }
}
