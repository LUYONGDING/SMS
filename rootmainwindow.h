#ifndef ROOTMAINWINDOW_H
#define ROOTMAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlRecord>
#include <QModelIndex>

#include "dbconnt.h"
#include "teacher.h"
#include "group.h"
#include "user.h"
#include "department.h"
#include "studentdependence.h"
#include "student.h"

namespace Ui {
class RootMainWindow;
}

class RootMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RootMainWindow(QWidget *parent = 0);
    ~RootMainWindow();

private:
    Ui::RootMainWindow *ui;
    void setMarginSpacing();
    DBconnt * db;
    teacher * tch;
    group * grp;
    user * us;
    department * dpment;
    studentDependence * studpdence;
    student * stu;
    QStandardItemModel * userModel;
    QStandardItemModel * groupModel;
    QStandardItemModel * stuModel;
    QStandardItemModel * tchModel;
    QSqlTableModel * MainTableView;
    QSqlRelationalTableModel * RMainTableView;
    QString controlInfo;
    bool isRoot = false;
    void paintEvent(QPaintEvent *event);
    void setUserModel();
    void setGroupModel();
    void setStuModel();
    void setTchModel();
    void setSearchWidget();
signals:
    void sendOpenInfo(QString info);
    void sendOpenInfoList_Grp(QStringList list);
    void sendOpenInfoList_Dpment(QStringList list);
public slots:
   void getUserInfo(user * us);
   void CustomContextMenu_User(const QPoint &pos);
   void CustomContextMenu_Grp(const QPoint &pos);
   void CustomContextMenu_Stu(const QPoint &pos);
   void CustomContextMenu_Tch(const QPoint &pos);
   void openGrpTableViewInUser();
   void openTchTableViewInUser();
   void openRtTableViewInUser();
   void openGrpTableViewInGrp(QStringList list);
   void openDpmentTableViewInGrp(QStringList list);
   void openGrp_0TableViewInGrp();
   void openGrp_1TableViewInGrp();
   void openStuTableViewInStu();
   void openTchTableViewInTch();
   void openTableViewInUserByDC(const QModelIndex & index);
   void openTableViewInGrpByDC(const QModelIndex & index);
   void openTableViewInStuByDC(const QModelIndex & index);
   void openTableViewInTchByDC(const QModelIndex & index);
private slots:
   void on_pushButton_add_clicked();
   void on_pushButton_change_clicked();
   void on_pushButton_delete_clicked();
   void on_pushButton_search_clicked();
   void on_pushButton_reset_clicked();
};

#endif // ROOTMAINWINDOW_H
