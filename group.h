#ifndef GROUP_H
#define GROUP_H

#include "user.h"
#include "teacher.h"
#include <QString>
#include <QObject>

class group : public QObject
{
    Q_OBJECT
public:
    //explicit group(QObject *parent = 0);
    group();
    group(user * user, QString groupName, teacher * thr, int groupType);
    ~group();

    //设置和获得成员属性接口
    void setGroupID(user * user);
    void setGroupName(QString groupName);
    void setGroupTeacherID(teacher * thr);
    void setGroupType(int groupType);

    int getGroupID() const;
    QString getGroupName() const;
    int getGroupTeacherID() const;
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
    int groupTeacherID;   //社团指导老师ID,与teacher中的teacherID关联
    int groupType;  //标志是社团还是机构
signals:
};

#endif // GROUP_H
