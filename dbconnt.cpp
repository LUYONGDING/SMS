#include "dbconnt.h"

DBconnt::DBconnt(QObject *parent) : QObject(parent)
{
#if debug_mode
    qDebug()<<"DBconnt::DBconnt()";  //输出：构造函数名
#endif

    QTextCodec * codec = QTextCodec::codecForName("UTF-8");  //设置字符集
    QTextCodec::setCodecForLocale(codec);

    //!设置数据库参数
//    this->HostName = "127.0.0.1";
//    this->UserName = "root";
//    this->Password = "root";
//    this->DatabaseName = "group_manager_system";
//    this->Port = 3306;
    readConfig();


#if debug_mode
    qDebug() << QSqlDatabase::drivers();    //输出：可以使用哪种数据库
#endif

    this->db = new QSqlDatabase();
    *(this->db) = QSqlDatabase::addDatabase("QMYSQL"); //载入MySQL数据库驱动

    //this->db = QSqlDatabase::addDatabase("QMYSQL");

    this->db->setHostName(this->HostName);    //设置数据库地址
    this->db->setUserName(this->UserName); //数据库用户名
    this->db->setPassword(this->Password); //数据库密码
    this->db->setDatabaseName(this->DatabaseName);   //数据库名字
    this->db->setPort(this->Port);

//    if(!this->db->open())
//    {
//        qDebug() << this->db->lastError().text();
//        return;
//    }
//#if debug_mode
//    qDebug()<<"数据库打开成功";    //输出：打开数据库成功提示
//#endif
}

DBconnt::DBconnt()  //构造函数
{

#if debug_mode
    qDebug()<<"DBconnt::DBconnt()";  //输出：构造函数名
#endif

    QTextCodec * codec = QTextCodec::codecForName("UTF-8");  //设置字符集
    QTextCodec::setCodecForLocale(codec);

    //!设置数据库参数
//    this->HostName = "127.0.0.1";
//    this->UserName = "root";
//    this->Password = "root";
//    this->DatabaseName = "group_manager_system";
//    this->Port = 3306;
    readConfig();


#if debug_mode
    qDebug() << QSqlDatabase::drivers();    //输出：可以使用哪种数据库
#endif

    this->db = new QSqlDatabase();
    *(this->db) = QSqlDatabase::addDatabase("QMYSQL"); //载入MySQL数据库驱动

    //this->db = QSqlDatabase::addDatabase("QMYSQL");

    this->db->setHostName(this->HostName);    //设置数据库地址
    this->db->setUserName(this->UserName); //数据库用户名
    this->db->setPassword(this->Password); //数据库密码
    this->db->setDatabaseName(this->DatabaseName);   //数据库名字
    this->db->setPort(this->Port);

//    if(!this->db->open())
//    {
//        qDebug() << this->db->lastError().text();
//        return;
//    }
//#if debug_mode
//    qDebug()<<"数据库打开成功";    //输出：打开数据库成功提示
//#endif
}

DBconnt::~DBconnt()
{

#if debug_mode
    qDebug() << "DBconnt::~DBconnt()";  //输出：析构函数名
#endif

    if(NULL != this->query)
    {
        delete this->query;
        this->query = NULL;

#if debug_mode
        qDebug()<<"delete query";   //输出：释放query的空间
#endif
    }

    this->db->close();   //关闭数据库

    if(NULL != this->db)
    {
        delete this->db;
        this->db = NULL;

#if debug_mode
        qDebug()<<"delete db";   //输出：释放db的空间
#endif
    }
}

QString DBconnt::getDBinfo() const
{
    if(false == this->db->isOpen())  //判断数据库是否已经打开
    {
        qDebug() << "数据库没有打开";
        return NULL;
    }
    //数据库信息
    QString info = QString("DBName:%1 , DBHostName:%2 , DBPort:%3 , DBUserName:%4")
            .arg(this->db->databaseName())
            .arg(this->db->hostName())
            .arg(this->db->port())
            .arg(this->db->userName());
    return info;
}

void DBconnt::closeDB()
{
    if(false == this->db->isOpen() || NULL == this->db)  //判断数据库是否已经打开
    {
        qDebug() << "数据库没有打开或没有初始化";
        return;
    }
    qDebug() << "关闭数据库:" <<this->db->databaseName();
    delete this->query;
    this->query = NULL;
    this->db->close();   //关闭数据库
}

void DBconnt::openDB()
{
    if(true == this->db->isOpen())
    {
        qDebug() << "数据库已经打开";
        return;
    }
    *(this->db) = QSqlDatabase::addDatabase("QMYSQL"); //载入MySQL数据库驱动

    //this->db = QSqlDatabase::addDatabase("QMYSQL");

    this->db->setHostName(this->HostName);    //设置数据库地址
    this->db->setUserName(this->UserName); //数据库用户名
    this->db->setPassword(this->Password); //数据库密码
    this->db->setDatabaseName(this->DatabaseName);   //数据库名字

    if(!this->db->open())
    {
        qDebug() << this->db->lastError().text();
        return;
    }
    this->query = new QSqlQuery();  //开辟空间：数据库操作类
}

int DBconnt::readConfig()
{
    qDebug()<<QDir::currentPath();
    QFile configFile("config.ini");
    if(!configFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"打开配置文件错误"<<endl;
        return 0;
    }
    QTextStream txtInput(&configFile);
    qDebug()<<configFile.fileName();
    QStringList linelist;
    QString line;
    QString key;
    QString value;
    while(!txtInput.atEnd())
    {
        line = txtInput.readLine();
        if(line.startsWith("$"))
        {
           linelist = line.split("=");
           key=linelist[0];
           value=linelist[1];
           if(key.trimmed() == "$HostName")
           {
//               hostname = value.trimmed();
               this->HostName = value.trimmed();
           }
           if(key.trimmed() == "$UserName")
           {
               this->UserName = value.trimmed();
           }
           if(key.trimmed() == "$Password")
           {
               this->Password = value.trimmed();
           }
           if(key.trimmed() == "$DatabaseName")
           {
               this->DatabaseName = value.trimmed();
           }
           if(key.trimmed() == "$Port")
           {
               this->Port = value.trimmed().toInt();
           }
        }
    }
    return 1;
}
