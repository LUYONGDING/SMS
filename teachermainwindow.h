#ifndef TEACHERMAINWINDOW_H
#define TEACHERMAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QSqlQueryModel>

#include "dbconnt.h"
#include "teacher.h"
#include "group.h"
#include "user.h"
#include "department.h"
#include "mainwindow.h"
#include "studentdependence.h"
#include "student.h"

namespace Ui {
class TeacherMainWindow;
}

class TeacherMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TeacherMainWindow(QWidget *parent = 0);
    ~TeacherMainWindow();
    void paintEvent(QPaintEvent *event);

private:
    Ui::TeacherMainWindow *ui;
    DBconnt * db;
    teacher * tch;
    group * grp;
    user * us;
    department * dpment;
    studentDependence * studpdence;
    student * stu;
    QStandardItemModel * model;
    QSqlQueryModel * mainTableView;
    void setMarginSpacing();
signals:
    void sendOpenInfo(QStringList list);
    void sendOpenInfo2(QStringList list);
public slots:
    void getUserInfo(user * us);
    void CustomContextMenu(const QPoint &);
    void setGroupModel();
    void openGrpTableView(QStringList list);
    void opendpmentTableView(QStringList list);
};

#endif // TEACHERMAINWINDOW_H
