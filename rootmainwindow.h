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
#include <QLabel>
#include <QTimer>
#include <QDateTime>

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
protected:
     void paintEvent(QPaintEvent *event);
private:
    Ui::RootMainWindow *ui;

    DBconnt * db;   //数据库操作类
    teacher * tch;  //教师类
    group * grp;    //机构/社团类
    user * us;  //用户类
    user * infoUs;  //用户类，用于保存登录用户信息
    department * dpment;    //部门类
    studentDependence * studpdence; //学生从属类
    student * stu;  //学生类
    QStandardItemModel * userModel; //用户树视图
    QStandardItemModel * groupModel;    //社团树视图
    QStandardItemModel * stuModel;  //学生表树视图
    QStandardItemModel * tchModel;  //教师表树视图
    QSqlTableModel * MainTableView; //主框体数据库Model
    QSqlRelationalTableModel * RMainTableView;  //主框体关系数据库Model
    QString controlInfo;    //控制信息
    QTimer * timer; //计时器类
    QLabel * currentTimeLabel;  //显示计时器QLabel
    bool isRoot = false;    //是否Root用户标志位

    void setMarginSpacing();    //设置各控件的Margin与Spacing
    void setUserModel();    //设置用户树视图
    void setGroupModel();   //设置机构/社团树视图
    void setStuModel(); //设置学生树视图
    void setTchModel(); //设置教师树视图
    void setSearchWidget(); //设置查询部件信息
signals:
    void sendOpenInfo(QString info);    //打开信息槽信号
    void sendOpenInfoList_Grp(QStringList list);    //打开机构/社团信息信号
    void sendOpenInfoList_Dpment(QStringList list); //打开部门信息信号
    void loginOut();    //登出信息
public slots:
   void getUserInfo(user & us); //获得用户信息槽函数
   void CustomContextMenu_User(const QPoint &pos);  //用户树视图右键菜单
   void CustomContextMenu_Grp(const QPoint &pos);   //机构/社团树视图右键菜单
   void CustomContextMenu_Stu(const QPoint &pos);   //学生表树视图右键菜单
   void CustomContextMenu_Tch(const QPoint &pos);   //教师表树视图右键菜单
   void openGrpTableViewInUser();   //用户树视图打开机构/社团用户
   void openTchTableViewInUser();   //用户树视图打开教师用户
   void openRtTableViewInUser();    //用户树视图打开管理员用户
   void openGrpTableViewInGrp(QStringList list);    //机构/社团树视图打开机构/社团
   void openDpmentTableViewInGrp(QStringList list); //机构/社团树视图打开部门
   void openGrp_0TableViewInGrp();  //打开机构
   void openGrp_1TableViewInGrp();  //打开社团
   void openStuTableViewInStu();    //学生表树视图打开学生表
   void openTchTableViewInTch();    //教师表树视图打开教师表
   void openTableViewInUserByDC(const QModelIndex & index); //用户树视图双击打开
   void openTableViewInGrpByDC(const QModelIndex & index);  //机构/社团树视图双击打开
   void openTableViewInStuByDC(const QModelIndex & index);  //学生表树视图双击打开
   void openTableViewInTchByDC(const QModelIndex & index);  //教师表树视图双击打开
private slots:
   void on_pushButton_add_clicked();    //增加按钮槽函数
   void on_pushButton_change_clicked(); //更改按钮槽函数
   void on_pushButton_delete_clicked(); //删除按钮槽函数
   void on_pushButton_search_clicked(); //查询按钮槽函数
   void on_pushButton_reset_clicked();  //清空按钮槽函数
};

#endif // ROOTMAINWINDOW_H
