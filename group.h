#ifndef GROUP_H
#define GROUP_H

#include "user.h"
#include <QString>
#include <QObject>

class group : public QObject
{
    Q_OBJECT
public:
    //explicit group(QObject *parent = 0);
    group();
    group(user * user, QString groupName, QString groupTeacher, int groupType);
    ~group();

    //设置和获得成员属性接口
    void setGroupID(user * user);
    void setGroupName(QString groupName);
    void setGroupTeacher(QString groupTeacher);
    void setGroupType(int groupType);

    int getGroupID() const;
    QString getGroupName() const;
    QString getGroupTeacher() const;
    int getGroupType() const ;

    //获得信息
    QString getinfo() const;

    group & operator= (const group & another); //重写=操作符
    bool operator ==(group & another) const;  //重写==操作符
    bool operator !=(group & another) const;  //重写!=操作符

protected:

private:
    int groupID;    //社团ID，与user中的ID关联
    QString groupName;  //社团名字
    QString groupTeacher;   //社团指导老师
    int groupType;  //标志是社团还是机构
signals:
};

#endif // GROUP_H
