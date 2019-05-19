#ifndef GROUPMAINWINDOW_H
#define GROUPMAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QLayout>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QSqlQueryModel>
#include <QAction>
#include <QSqlRelationalTableModel>
#include <QLabel>
#include <QDateTime>
#include <QTimer>


#include "group.h"
#include "department.h"
#include "user.h"
#include "student.h"
#include "studentdependence.h"
#include "dbconnt.h"

namespace Ui {
class GroupMainWindow;
}

class GroupMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GroupMainWindow(QWidget *parent = 0);
    ~GroupMainWindow();
protected:
    void paintEvent(QPaintEvent *event);    //绘图事件
private:
    Ui::GroupMainWindow *ui;
    DBconnt * db;   //数据库操作成员
    user * us;  //用户类成员
    group * grp;    //机构/社团类成员
    department * dpment;    //部门类成员
    student * stu;  //学生类成员
    studentDependence * studpence;  //学生从属类成员
    QStandardItemModel * model; //标准Model
    QSqlQueryModel * mainTableView; //数据库查询Model成员
    QSqlRelationalTableModel * RMainTableView;  //关系数据库查询Model成员
    QPainter * painter; //绘图成员
    QTimer * timer; //定时器成员
    QLabel * currentTimeLabel;  //显示时间QLabel成员
    void setMarginSpacing();    //设置各控件Margin与Spacing函数
    void setGroupModel();   //设置树视图函数
signals:
    void sendOpenInfo(QStringList list);    //打开表信息的信号
    void loginOut();    //登出信号
public slots:
    void getUserInfo(user & us);    //获得用户信息的槽函数
    void CustomContextMenu(const QPoint &); //树视图右键菜单槽函数
    void opendpmentTableView(QStringList list); //打开部门表的槽函数
    void openTableViewByDC(const QModelIndex & index);  //双击打开部门表的槽函数
};

#endif // GROUPMAINWINDOW_H
