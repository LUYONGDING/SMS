#ifndef REGISTFORM_H
#define REGISTFORM_H

#include <QWidget>
#include <QComboBox>
#include <QDebug>
#include <QPushButton>
#include <QMessageBox>
#include <QGroupBox>

#include "dbconnt.h"
#include "user.h"
#include "group.h"
#include "teacher.h"

namespace Ui {
class registForm;
}

class registForm : public QWidget
{
    Q_OBJECT

public:
    explicit registForm(QWidget *parent = 0);
    ~registForm();
    void userRegist();  //用户登录槽函数
    void SetNULLTeacherEdit();  //置空教师注册控件
    void SetNULLGroupEdit();    //置空社团注册控件
signals:
private:
    Ui::registForm *ui;
    DBconnt * db;   //数据库类
    user * us;  //用户类
    teacher * tch;  //教师类
};

#endif // REGISTFORM_H
