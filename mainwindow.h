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
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
signals:
    void sendUserInfo0(user & us);
    void sendUserInfo1(user & us);
    void sendUserInfo2(user & us);
private slots:
    void userLogin();   //登录槽函数
    void timeUpdate();
private:
    Ui::MainWindow *ui;

    DBconnt * db;

    registForm * regist;

    user * us;

    QTimer * timer;

    TeacherMainWindow * tchmain;

    RootMainWindow * rtmain;

    GroupMainWindow * grpmain;

    QLabel * currentTimeLabel;
};

#endif // MAINWINDOW_H
