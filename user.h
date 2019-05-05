#ifndef USER_H
#define USER_H

#include <QObject>
#include <QDebug>
#include <QString>
#include "debugmode.h"

class user : public QObject
{
    Q_OBJECT
public:
    explicit user(QObject *parent = 0);
    user();
    user(int userID, QString userName, QString userPasswd,int userType); //构造函数
    ~user();    //析构函数

    //设置和获得成员接口
    void setUserID(int userID);
    void setUserName(QString userName);
    void setUserPasswd(QString userPasswd);
    void setUserType(int userType);
    int getUserID() const;
    QString getUserName() const;
    QString getUserPasswd() const;
    int getUserType() const;

    //获得信息
    QString getinfo() const;

    user & operator= (const user & another); //重写=操作符
    bool operator ==(user & another) const;  //重写==操作符
    bool operator !=(user & another) const;  //重写!=操作符

protected:
private:
    int userID; //用户ID
    QString userName;   //用户名
    QString userPasswd; //用户密码
    int userType;

signals:

public slots:
};

#endif // USER_H
