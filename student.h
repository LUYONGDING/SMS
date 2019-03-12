#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>
#include <QString>
#include <QDebug>

class student : public QObject
{
    Q_OBJECT
public:
    //explicit student(QObject *parent = 0);
    student();
    student(int studentID, bool studentSex, QString studentName);   //带参构造函数
    ~student();

    //设置和获得成员属性的接口
    void setStudentID(int studentID);
    void setStudentSex(bool studentSex);
    void setStudentName(QString studentName);

    int getStudentID() const;
    bool getStudentSex() const;
    QString getStudentName() const;

    //获得信息
    QString getinfo() const;

    student & operator =(student & another);   //重载=操作符
    bool operator ==(student & another);    //重载==操作符
    bool operator !=(student & another);    //重载!=操作符



protected:
private:
    int studentID;  //学生学号
    bool studentSex;    //学生性别
    QString studentName;    //学生姓名
signals:

public slots:
};

#endif // STUDENT_H
