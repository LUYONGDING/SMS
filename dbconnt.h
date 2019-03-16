#ifndef DBCONNT_H
#define DBCONNT_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTextCodec>

#include "debugmode.h"

class DBconnt : public QObject  //数据库连接类
{
    Q_OBJECT
public:
    //    explicit DBconnt(QObject *parent = 0);
    DBconnt();
    ~DBconnt();

    QSqlQuery * query;    //数据库操作类

    QString getDBinfo() const;   //获得数据库信息
    void closeDB(); //关闭数据库
    void openDB();
    QSqlDatabase * db;    //数据库类
protected:
private:
    QString HostName;   //数据库地址
    QString UserName;   //用户名
    QString Password;   //密码
    QString DatabaseName;   //数据库名
    int Port;

signals:

public slots:
};

#endif // DBCONNT_H
