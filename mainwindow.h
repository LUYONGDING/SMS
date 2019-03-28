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


#include "dbconnt.h"
#include "user.h"
#include "group.h"
#include "student.h"
#include "department.h"
#include "studentdependence.h"
#include "teacher.h"
#include "root.h"
#include "registform.h"

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
private slots:
    void userLogin();   //登录槽函数
private:
    Ui::MainWindow *ui;

    DBconnt * db;

    registForm * regist;

};

#endif // MAINWINDOW_H
