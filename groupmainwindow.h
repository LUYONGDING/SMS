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
    void paintEvent(QPaintEvent *event);
private:
    Ui::GroupMainWindow *ui;
    DBconnt * db;
    user * us;
    group * grp;
    department * dpment;
    student * stu;
    studentDependence * studpence;
    QStandardItemModel * model;
    QSqlQueryModel * mainTableView;
    QSqlRelationalTableModel * RMainTableView;
    QPainter * painter;
    void setMarginSpacing();
    void setGroupModel();
signals:
    void sendOpenInfo(QStringList list);
public slots:
    void getUserInfo(user * us);
    void CustomContextMenu(const QPoint &);
    void opendpmentTableView(QStringList list);
    void openTableViewByDC(const QModelIndex & index);
};

#endif // GROUPMAINWINDOW_H
