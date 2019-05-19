#include "selectteacherform.h"
#include "ui_selectteacherform.h"

selectTeacherForm::selectTeacherForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::selectTeacherForm)
{
    this->db = new DBconnt(this);
    this->tch = new teacher(this);
    ui->setupUi(this);
//    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->comboBox_search->addItem("ID");
    ui->comboBox_search->addItem("姓名");
    ui->comboBox_search->addItem("性别");

    this->setWindowTitle("选择社团教师");   //设置窗口标题
    this->setWindowIcon(QIcon(":/mainWin/Icon/guishen_0131ev05b08mg01.png"));   //设置窗口图标

    connect(ui->pushButton_cancel,&QPushButton::clicked,[=](){   //关闭按钮的信号与槽函数连接
        this->close();
    });
    //    this->db->openDB();
    //    this->teacherModel = new QSqlTableModel(this);  //为教师Model开辟空间
    //    teacherModel->setTable("teacher");  //选择teacher表
    //    teacherModel->select(); //选择所有数据

    //    ui->tableView->setModel(teacherModel);  //将教师Model设置到tableView
    //    ui->tableView->show();  //显示

    this->db->openDB();
    this->teacherModel = new QSqlQueryModel(this); //为教师Model开辟空间
    this->teacherModel->setQuery("SELECT * FROM TEACHER");  //设置sql语句
    this->teacherModel->removeColumn(1);
    this->teacherModel->setHeaderData(0,Qt::Horizontal,"教师ID");
    this->teacherModel->setHeaderData(1,Qt::Horizontal, "教师姓名");
    this->teacherModel->setHeaderData(2,Qt::Horizontal,"教师性别（1为男性，0为女性）");
    ui->tableView->setModel(this->teacherModel); //将教师Model设置到tableView
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //设置表对齐
    ui->tableView->show(); //显示
    this->db->closeDB();
    //    connect(ui->tableView,SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(slotRowDoubleClicked(const QModelIndex &)));
    connect(ui->tableView,&QTableView::doubleClicked,this,&selectTeacherForm::slotRowDoubleClicked);    //连接双击与获取表中数据的槽函数
    connect(ui->pushButton_ok,&QPushButton::clicked,this,&selectTeacherForm::returnTeacherID);  //连接确定按钮与获得表中数据的槽函数
    connect(ui->pushButton_search,&QPushButton::clicked,this,&selectTeacherForm::searchTeacher);
    connect(ui->pushButton_reset,&QPushButton::clicked,this,&selectTeacherForm::resetTable);
}

selectTeacherForm::~selectTeacherForm()
{
//    if(this->db != NULL)
//    {
//        delete this->db;
//    }
//    if(this->tch != NULL)
//    {
//        delete this->tch;
//    }
    delete ui;
}
void selectTeacherForm::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/mainWin/background/guishen_0039ev05a07.jpg"));
    event->accept();
    return QWidget::paintEvent(event);
}
void selectTeacherForm::slotRowDoubleClicked(const QModelIndex & index)
{
    if(index.isValid())
    {
        QSqlRecord record = teacherModel->record(index.row());
        QString ID = record.value("teacher_id").toString();
//        qDebug()<<"点击了"<<ID;
        emit selectedID(ID);    //发送ID信号
    }
}
void selectTeacherForm::returnTeacherID()
{
    QSqlRecord record = teacherModel->record(ui->tableView->currentIndex().row());
    QString ID = record.value("teacher_id").toString();
//    qDebug()<<"返回了"<<ID;
    emit selectedID(ID);    //发送ID信号
}
void selectTeacherForm::searchTeacher()
{
    QString condition = ui->comboBox_search->currentText();
//    qDebug()<<condition;
    if(condition == "ID")
    {
        this->tch->setTeacherID(ui->lineEdit_search->text().toInt());
        this->db->openDB();
        bool ret = 0;
        this->db->query->prepare("SELECT * FROM TEACHER WHERE teacher_id = :value ");
        this->db->query->bindValue(":value",tch->getTeacherID());
//        qDebug()<<this->db->query->lastQuery();
        ret = this->db->query->exec();
        if(!ret)
        {
            QMessageBox::critical(this,"系统错误",this->teacherModel->query().lastError().text());
        }
        if(this->db->query->next()) //获得数据
        {
//            qDebug()<<"有数据";
            this->teacherModel->setQuery(*(this->db->query));   //将Query设置为Model的Query
            this->teacherModel->removeColumn(1);
            ui->tableView->setModel(this->teacherModel); //将教师Model设置到tableView
            ui->tableView->show(); //显示
        }
        else
        {
            QMessageBox::information(this,"查询","没有找到此信息");
            this->resetTable(); //重置表
        }
        this->db->closeDB();
        return;
    }
    else if(condition == "姓名")
    {
        this->tch->setTeacherName(ui->lineEdit_search->text());
        this->db->openDB();
        bool ret = 0;
        this->db->query->prepare("SELECT * FROM TEACHER WHERE teacher_name = :value");
        this->db->query->bindValue(":value",tch->getTeacherName());
        ret = this->db->query->exec();
        qDebug()<<this->db->query->lastQuery();
        if(!ret)
        {
            QMessageBox::critical(this,"系统错误",this->teacherModel->query().lastError().text());
        }
        if(this->db->query->next()) //是否获得数据
        {
//            qDebug()<<"有数据";
            this->teacherModel->setQuery(*(this->db->query));   //将Query设置为Model的Query
            this->teacherModel->removeColumn(1);
            ui->tableView->setModel(this->teacherModel); //将教师Model设置到tableView
            ui->tableView->show(); //显示
        }
        this->db->closeDB();
        return;
    }
    else if(condition == "性别")
    {
        bool sex;
        if("男"==ui->lineEdit_search->text() || 1 == ui->lineEdit_search->text().toInt())
        {
            sex = 1;
        }
        else if("女" == ui->lineEdit_search->text() || 0 == ui->lineEdit_search->text().toInt())
        {
            sex = 0;
        }
        else
        {
            QMessageBox::warning(this,"警告","请输入男（1）或女（0）");
            return;
        }
        tch->setTeacherSex(sex);
        this->db->openDB();
        bool ret = 0;
        this->db->query->prepare("SELECT * FROM TEACHER WHERE teacher_sex = :value ");
        this->db->query->bindValue(":value",tch->getTeacherSex());
        ret = this->db->query->exec();
        if(!ret)
        {
            QMessageBox::critical(this,"系统错误",this->teacherModel->query().lastError().text());
        }
        if(this->db->query->next()) //获得数据
        {
//            qDebug()<<"有数据";
            this->teacherModel->setQuery(*(this->db->query));   //将Query设置为Model的Query
            this->teacherModel->removeColumn(1);
            ui->tableView->setModel(this->teacherModel); //将教师Model设置到tableView
            ui->tableView->show(); //显示
        }
        else
        {
            QMessageBox::information(this,"查询","没有找到此信息");
            this->resetTable(); //重置表
        }
        this->db->closeDB();
        return;
    }
}
void selectTeacherForm::resetTable()
{
    if(NULL == tch)
    {
        return;
    }
    this->db->openDB();
    this->teacherModel->setQuery("SELECT * FROM TEACHER");  //设置sql语句
    this->teacherModel->removeColumn(1);
    ui->tableView->setModel(this->teacherModel); //将教师Model设置到tableView
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->show(); //显示
    this->db->closeDB();
}
