#ifndef TEACHER_H
#define TEACHER_H

#include <QObject>
#include <QString>
#include <QDebug>
#include "user.h"

class teacher : public QObject
{
    Q_OBJECT
public:
    //explicit teacher(QObject *parent = 0);
    teacher();  //无参构造
    teacher(int teacherID,
    user * us,
    QString teacherName,
    bool teacherSex);   //有参构造
    ~teacher();

    //设置和获得成员属性的接口
    void setTeacherID(int teacherID);
    void setTeahcerUserID(user * us);
    void setTeacherName(QString teacherName);
    void setTeacherSex(bool teacherSex);

    int getTeacherID() const;
    int getTeacherUserID() const;
    QString getTeacherName() const;
    bool getTeacherSex() const;

    QString getInfo() const;    //获得信息

    teacher & operator =(teacher & another);    //重载=操作符
    bool operator ==(teacher & another) const;    //重载==操作符
    bool operator !=(teacher & another) const;    //重载!=操作符

protected:
private:
    int teacherID;  //老师职工ID
    int teacherUserID;  //老师用户ID，与user中的userID关联
    QString teacherName;    //教师姓名
    bool teacherSex;    //教师性别
signals:

public slots:
};

#endif // TEACHER_H
