#ifndef ROOT_H
#define ROOT_H

#include <QObject>
#include <QDebug>
#include <QString>
#include "user.h"

class root : public QObject
{
    Q_OBJECT
public:
    explicit root(QObject *parent = 0);
    root(); //无参构造函数
    root(int rootID,
    user * us,
    QString rootName,
    bool rootSex); //有参构造函数
    ~root();

    //设置和获得成员属性的接口
    void setRootID(int rootID);
    void setUserID(user * us);
    void setUserID(int ID);
    void setRootName(QString rootName);
    void setRootSex(bool rootSex);

    int getRootID() const;
    int getRootUserID() const;
    QString getRootName() const;
    bool getRootSex() const;

    QString getInfo() const;    //获得信息

    root & operator =(root & another);  //重载=操作符
    bool operator ==(root & another) const; //重载==操作符
    bool operator !=(root & another) const; //重载!=操作符

protected:
private:
    int rootID;
    int rootUserID;
    QString rootName;
    bool rootSex;

signals:

public slots:
};

#endif // ROOT_H
