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

#include "dbconnt.h"
#include "teacher.h"
#include "group.h"
#include "user.h"
#include "department.h"
#include "mainwindow.h"

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
    void setMarginSpacing();
public slots:
    void getUserInfo(user * us);
    void CustomContextMenu(const QPoint &);
    void setGroupModel();
};

#endif // TEACHERMAINWINDOW_H
