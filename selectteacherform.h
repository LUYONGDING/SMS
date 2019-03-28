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
    void paintEvent(QPaintEvent * event);
signals:
    void selectedID(QString & ID);
public slots:
    void slotRowDoubleClicked(const QModelIndex &);
private slots:
    void searchTeacher();
    void returnTeacherID();
private:
    Ui::selectTeacherForm *ui;
    DBconnt * db;   //数据库类
    teacher * tch;  //教师类
//    QSqlTableModel * teacherModel;  //教师数据库表模型类
    QSqlQueryModel * teacherModel;
    void resetTable();  //重置数据表
};

#endif // SELECTTEACHERFORM_H
