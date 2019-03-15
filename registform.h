#ifndef REGISTFORM_H
#define REGISTFORM_H

#include <QWidget>
#include <QComboBox>
#include <QDebug>
#include <QPushButton>
#include <QMessageBox>
#include <QGroupBox>
#include <QButtonGroup>
#include <QRegExp>

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
    bool teacherRegistCheck(); //注册前检查
private:
signals:
private:
    Ui::registForm *ui;
    DBconnt * db;   //数据库类
    user * us;  //用户类
    teacher * tch;  //教师类
    QButtonGroup btnGroup;  //用于教师注册的radio按钮组
    QButtonGroup btnGroup2; //用于社团与机构的radio按钮组
    QRegExp rx; //用于检测密码是否符合规则
};

#endif // REGISTFORM_H
