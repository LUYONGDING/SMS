#ifndef SELECTTEACHERFORM_H
#define SELECTTEACHERFORM_H

#include <QWidget>
#include <QPushButton>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QTableView>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include <QMessageBox>
#include <QSqlRecord>


#include "dbconnt.h"
#include "teacher.h"

namespace Ui {
class selectTeacherForm;
}

class selectTeacherForm : public QWidget
{
    Q_OBJECT

public:
    explicit selectTeacherForm(QWidget *parent = 0);
    ~selectTeacherForm();
protected:
    void paintEvent(QPaintEvent * event);   //绘图事件
signals:
    void selectedID(QString & ID);  //选择ID信号
public slots:
    void slotRowDoubleClicked(const QModelIndex & index);   //双击槽函数
private slots:
    void searchTeacher();   //查询教师ID槽函数
    void returnTeacherID(); //返回教师ID槽函数
private:
    Ui::selectTeacherForm *ui;
    DBconnt * db;   //数据库类
    teacher * tch;  //教师类
//    QSqlTableModel * teacherModel;  //教师数据库表模型类
    QSqlQueryModel * teacherModel;
    void resetTable();  //重置数据表
};

#endif // SELECTTEACHERFORM_H
