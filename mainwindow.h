﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>

#include "dbconnt.h"
#include "user.h"
#include "group.h"
#include "student.h"
#include "department.h"
#include "studentdependence.h"
#include "teacher.h"
#include "root.h"

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

private:
    Ui::MainWindow *ui;

    DBconnt * connt;

};

#endif // MAINWINDOW_H
