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
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlRecord>
#include <QTimer>
#include <QDateTime>
#include <QLabel>
#include <QBitmap>

#include "dbconnt.h"
#include "teacher.h"
#include "group.h"
#include "user.h"
#include "department.h"
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
    DBconnt * db;   //数据库类
    teacher * tch;  //教师类
    group * grp;    //社团类
    user * us;  //用户类
    department * dpment;    //部门类
    studentDependence * studpdence; //从属类
    student * stu;  //学生类
    QStandardItemModel * model; //树视图Model
    QSqlQueryModel * mainTableView; //SqlQueryModel
    QSqlTableModel * MainTableView; //数据库Model
    QSqlRelationalTableModel * RMainTableView;  //关系数据库Model
    void setMarginSpacing();    //设置各个控件的Margin与Spacing
    void setSearchWidget(); //设置查找部件内容
    QString controlInfo;    //控制信息
    QLabel * currentTimeLabel;  //显示时间QLabel
    QTimer * timer; //计时器类
signals:
    //发送信息信号
    void sendOpenInfo(QStringList list);
    void sendOpenInfo2(QStringList list);
    void sendOpenInfo3(QStringList list);
    void loginOut();    //登出信号
public slots:
    void getUserInfo(user & us);    //获取用户信息槽函数
    void CustomContextMenu(const QPoint &); //树视图右键菜单
    void setGroupModel();   //设置主框体
    void openGrpTableView(QStringList list);    //打开社团
    void opendpmentTableView(QStringList list); //打开部门
    void openTableViewByDC(const QModelIndex &);    //双击打开社团
    void opendpmentTableViewByGrp(QStringList list);    //双击打开部门
private slots:
    void on_pushButton_add_clicked();   //增加按钮槽函数
    void on_pushButton_change_clicked();    //改变按钮槽函数
    void on_pushButton_delete_clicked();    //删除按钮槽函数
    void on_pushButton_search_clicked();    //查询按钮槽函数
    void on_pushButton_reset_clicked(); //清空按钮槽函数
};

#endif // TEACHERMAINWINDOW_H
