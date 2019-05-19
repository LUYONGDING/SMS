#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QDebug>
#include <QPixmap>
#include <QPainter>
#include <QPushButton>
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>
#include <QMediaPlayer>
#include <QMediaContent>
#include <QSound>


#include "dbconnt.h"
#include "user.h"
#include "group.h"
#include "student.h"
#include "department.h"
#include "studentdependence.h"
#include "teacher.h"
#include "root.h"
#include "registform.h"
#include "teachermainwindow.h"
#include "groupmainwindow.h"
#include "rootmainwindow.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
private:
    Ui::MainWindow *ui;

    DBconnt * db;   //数据库类成员

    registForm * regist;    //注册窗口成员

    user * us;  //用户类成员

    QTimer * timer; //计时器成员

    TeacherMainWindow * tchmain;    //教师主界面成员

    RootMainWindow * rtmain;    //管理员主界面成员

    GroupMainWindow * grpmain;  //社团主界面成员

    QLabel * currentTimeLabel;  //显示时间QLabel

    QLabel * lab;

    QMediaPlayer * play;
signals:
    //登录用户信息的信号
    void sendUserInfo0(user & us);
    void sendUserInfo1(user & us);
    void sendUserInfo2(user & us);
private slots:
    void userLogin();   //登录槽函数
    void timeUpdate();  //更新时间槽函数
};

#endif // MAINWINDOW_H
