#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->db = new DBconnt(this);
//    qDebug() << this->db->getDBinfo();
    this->setMouseTracking(true);

    this->us = new user(this);

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
    this->currentTimeLabel = new QLabel(this);
    connect(this->timer,&QTimer::timeout,this,&MainWindow::timeUpdate);
    ui->statusBar->addWidget(this->currentTimeLabel);
    this->timer->start(1000);
    QPushButton *bt =new QPushButton(this);
    this->ui->statusBar->addWidget(bt);
    bt->setFlat(true);
    connect(bt,&QPushButton::clicked,this,[=](){
       QMessageBox::information(NULL,NULL,"Hear me! King of Infinite Space! Planetmover! The Foundation of Fastness! Ruler of Earthquakes! The Vanquisher of Terror! The Creator of Panic! Destroyer! The Shining Victor! Son of Chaos and the Void! The Guardian of the Abyss! God of the Outermost Darkness! Lord of Dimensions! Riddle-knower! Guardian of The Secrets! Lord of the Labyrinth! Master of the Angles! God of the Whiporwills! Omegapoint! Lord of the Gate! Opener of the Way! The Oldest! All-in-One! The One by Life Prolonged! Umr At-Tawil! Iak-Sathath! Yog Sothoth NAFL'FTHAGN!!! Your servant call upon you!");
//        this->play = new QMediaPlayer(this);
//        play->setMedia(QMediaContent(QUrl::fromLocalFile(":/mainWin/Music/RyanAmon-LullabyforMergo.wav")));
//        play->setVolume(30);
//        play->play();
        QSound * star = new QSound(":/mainWin/Music/RyanAmon-LullabyforMergo.wav",this);
        star->play();
    });
}

MainWindow::~MainWindow()
{
//    if(NULL == this->db)
//    {
//        delete db;
//        db = NULL;
//    }
//    if(NULL == this->regist)
//    {
//        delete regist;
//        regist = NULL;
//    }
//    delete this->us;
//    if(this->tchmain!=NULL)
//    {
//        delete this->tchmain;
//    }
//    if(this->rtmain!=NULL)
//    {
//        delete this->rtmain;
//    }
//    if(this->grpmain!=NULL)
//    {
//        delete this->grpmain;
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
            this->rtmain = new RootMainWindow();
            connect(this,&MainWindow::sendUserInfo0,rtmain,&RootMainWindow::getUserInfo);
//            connect(this->timer,&QTimer::timeout,this,[=](){
//                rtmain->show();
//                emit sendUserInfo0(this->us);
//                this->timer->stop();
//            },Qt::UniqueConnection);
            connect(rtmain,&RootMainWindow::loginOut,this,[=](){
                this->ui->lineEdit_userName->clear();
                this->ui->lineEdit_passwd->clear();
                this->show();
            });
            emit sendUserInfo0(*(this->us));
            this->rtmain->show();
            this->timer->start(1000);
            this->hide();
            return;
            //code
        }
        if(1==us->getUserType())
        {
            QMessageBox::information(this,"login","教师登录成功");

            this->tchmain = new TeacherMainWindow();
            connect(tchmain,&TeacherMainWindow::loginOut,this,[=](){
                this->ui->lineEdit_userName->clear();
                this->ui->lineEdit_passwd->clear();
                this->show();
            });
            connect(this,&MainWindow::sendUserInfo1,tchmain,&TeacherMainWindow::getUserInfo);
//            connect(this->timer,&QTimer::timeout,this,[=](){
//                tchmain->show();
//                emit sendUserInfo1(this->us);
//                this->timer->stop();
//            },Qt::UniqueConnection);
//            this->timer->start(1000);
            emit sendUserInfo1(*(this->us));
            tchmain->show();
            this->hide();
            return;
            //code
        }
        if(2==us->getUserType())
        {
            QMessageBox::information(this,"login","社团登录成功");
            this->grpmain = new GroupMainWindow();
            connect(this->grpmain,&GroupMainWindow::loginOut,[=](){
                this->ui->lineEdit_userName->clear();
                this->ui->lineEdit_passwd->clear();
//                delete this->grpmain;
                this->show();
            });
            connect(this,&MainWindow::sendUserInfo2,grpmain,&GroupMainWindow::getUserInfo);
//            connect(this->timer,&QTimer::timeout,this,[=](){
//                grpmain->show();
//                emit sendUserInfo2(us);
//                this->timer->stop();
//            },Qt::UniqueConnection);
//            this->timer->start(1000);
            emit sendUserInfo2(*(this->us));
            this->grpmain->show();
            this->hide();
            return;
            //code
        }
//        db->closeDB();
    }
}

void MainWindow::timeUpdate()
{
    //获取时间
    QDateTime current_time = QDateTime::currentDateTime();
    QString timestr = current_time.toString("yyyy年MM月dd日 hh:mm:ss");
    currentTimeLabel->setText(timestr);
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
