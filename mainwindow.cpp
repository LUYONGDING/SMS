#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->db = new DBconnt();
    qDebug() << this->db->getDBinfo();

    this->setWindowTitle("学生社团管理系统");   //设置窗口标题
    this->setWindowIcon(QIcon(":/mainWin/Icon/guishen_0131ev05b08mg01.png"));   //设置窗口图标
    ui->comboBox_userType->addItem("教师");
    ui->comboBox_userType->addItem("社团或机构");
    ui->comboBox_userType->addItem("管理员");

    connect(ui->pushButton_clear,&QPushButton::clicked,[=](){   //清除按钮：点击后将用户名和密码置空
        ui->lineEdit_passwd->setText("");
        ui->lineEdit_userName->setText("");
    });
    connect(ui->pushButton_login,&QPushButton::clicked,this,&MainWindow::userLogin);
}

MainWindow::~MainWindow()
{
    if(NULL == db)
    {
        delete db;
    }

    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *event) //使用绘图事件设置背景
{
    QPainter painter(this);
    painter.drawPixmap(0,0,520,520,QPixmap(":/mainWin/background/guishen_0039ev05a07.jpg"));
}
void MainWindow::userLogin()
{
    if(ui->comboBox_userType->currentText() == QString("教师"))
    {
        //QMessageBox::information(NULL,"login","登录：教师");
        bool ret = false;

//        QString sql = QString("SELECT * FROM `user` WHERE `user`.user_name = '%1' AND `user`.user_passwd = '%2'")
//         .arg(ui->lineEdit_userName->text())
//         .arg(ui->lineEdit_passwd->text());
//        db->query->exec(sql);
       ret = db->query->prepare("SELECT * FROM `user` WHERE `user`.user_name = :name AND `user`.user_passwd = :passwd AND `user`.user_type = :type");
        db->query->bindValue(":name",ui->lineEdit_userName->text());
        db->query->bindValue(":passwd",ui->lineEdit_passwd->text());
        db->query->bindValue(":type",1);
        db->query->exec();
        if(!(db->query->next()))
        {
            //QString error = QString(db->query->lastError().text());
            QMessageBox::critical(this,"错误",db->query->lastQuery());
        }else
        {
            QMessageBox::information(this,"login","成功");
        }
    }
}
