#include "teachermainwindow.h"
#include "ui_teachermainwindow.h"

TeacherMainWindow::TeacherMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TeacherMainWindow)
{
    ui->setupUi(this);
    this->us = new user();
    this->db = new DBconnt();
    this->tch = new teacher();
    this->grp = new group();
    this->dpment = new department();
    this->mainTableView = new QSqlQueryModel(this);
    this->MainTableView = NULL;
    this->setWindowIcon(QIcon(":/mainWin/Icon/guishen_0131ev05b08mg01.png"));
    QWidget * tempWidget = new QWidget(this);
    ui->dockWidget_left->setTitleBarWidget(tempWidget);
    ui->widget->hide();
    this->setMarginSpacing();
    ui->treeView_2->setContextMenuPolicy(Qt::CustomContextMenu);
    //    this->actionopenGrpTableView = new QAction("打开",this->ui->treeView_2);
    //    this->actionopendpmentTableView = new QAction("打开",this->ui->treeView_2);
    //    this->actionopendpmentTableViewByGrp = new QAction("打开该部门所在的社团",this->ui->treeView_2);
    connect(ui->treeView_2,&QTreeView::doubleClicked,this,&TeacherMainWindow::openTableViewByDC);
    connect(ui->actionabout,&QAction::triggered,[=](){
        QString about = "Based on Qt 5.8.0(MSVC 2015 , 32 bit)\n\nBuilt on Mon Mar 11 21:31:43 2019 +0800\n\nDemo ver 1.0\n\nCopyright © 2019 luyongding. All Rights Reserved.\n\nThis progarm only used by personal graduation project.If you want to use it for other purposes,please ask the auther first.\nlyd2233970479@163.com";
        QMessageBox::about(this,"关于",about);
    });
    connect(ui->actionloginout,&QAction::triggered,[=](){
        int lgnout = QMessageBox::question(this,"登出","确定登出吗？");
        if(lgnout==QMessageBox::Yes)
        {
            qDebug()<<"用户登出";
            emit loginOut();
            this->close();
        }
        else
        {
            return;
        }
    });
}

TeacherMainWindow::~TeacherMainWindow()
{
    if(this->db != NULL)
    {
        delete this->db;
    }
    if(this->db != NULL)
    {
        delete this->tch;
    }
    if(this->grp != NULL)
    {
        delete this->grp;
    }
    if(this->us != NULL)
    {
        delete this->us;
    }
    delete ui;
}
void TeacherMainWindow::setMarginSpacing()
{
    this->layout()->setSpacing(0);
    this->layout()->setMargin(0);
    this->centralWidget()->layout()->setSpacing(0);
    this->centralWidget()->layout()->setMargin(0);
    this->ui->dockWidgetContents_4->layout()->setSpacing(0);
    this->ui->dockWidgetContents_4->layout()->setMargin(1);
    this->ui->dockWidget_left->layout()->setMargin(0);
    this->ui->dockWidget_left->layout()->setSpacing(0);
    this->ui->widget->layout()->setSpacing(0);
    this->ui->widget->layout()->setMargin(1);
}

void TeacherMainWindow::setSearchWidget()
{
    this->ui->comboBox->clear();
    if(this->controlInfo == "group")
    {
        this->ui->comboBox->addItem("部门ID");
//        this->ui->comboBox->addItem("社团/机构ID");
        this->ui->comboBox->addItem("部门名称");
        this->ui->comboBox->addItem("部门简介");
    }
    else if(this->controlInfo == "department")
    {
//        this->ui->comboBox->addItem("社团/机构ID");
//        this->ui->comboBox->addItem("所属部门");
        this->ui->comboBox->addItem("归属ID");
//        this->ui->comboBox->addItem("学生姓名");
    }
}
void TeacherMainWindow::paintEvent(QPaintEvent *event) //使用绘图事件设置背景
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/mainWin/background/guishen_0039ev05a07.jpg"));
}

void TeacherMainWindow::getUserInfo(user * us){ //获得登陆用户的槽函数
    this->us = us;
    this->setWindowTitle(QString("%1 [教师] - 学生社团管理系统").arg(this->us->getUserName()));   //设置窗口标题
    setGroupModel();
    connect(ui->treeView_2,&QTreeView::customContextMenuRequested,this,&TeacherMainWindow::CustomContextMenu);
    connect(ui->actionuserInfo,&QAction::triggered,[=](){
        QString userinfo = QString("用户名：%1\n用户类型：教师").arg(this->us->getUserName());
        QMessageBox::about(this,"用户信息",userinfo);
    });
    return;
}
void TeacherMainWindow::setGroupModel()
{
    bool ret = 0;
    this->model = new QStandardItemModel(ui->treeView_2);
    ui->treeView_2->setEditTriggers(0);
    ui->treeView_2->header()->hide();
    QStandardItem * item = new QStandardItem("我管理的社团");
    this->db->openDB();
    //    qDebug()<<us->getinfo();
    this->db->query->prepare("SELECT * FROM teacher where teacher_user_id = :ID");
    this->db->query->bindValue(":ID",this->us->getUserID());
    ret = this->db->query->exec();
    if(!ret)
    {
        QMessageBox::critical(NULL,"错误",this->db->query->lastError().text());
        this->db->closeDB();
        return;
    }
    else
    {
        if(this->db->query->next())
        {
            this->tch->setTeahcerUserID(us);
            this->tch->setTeacherID(this->db->query->value("teacher_id").toInt());
            this->tch->setTeacherName(this->db->query->value("teacher_name").toString());
            this->tch->setTeacherSex(this->db->query->value("teacher_sex").toBool());
            qDebug()<<this->tch->getInfo();
        }
        else
        {
            QMessageBox::warning(NULL,"警告","查找不到");
            this->db->closeDB();
            return;
        }
    }
    this->db->query->prepare("SELECT * FROM `group` WHERE `group_teacher_id` = :ID");
    this->db->query->bindValue(":ID",this->tch->getTeacherID());
    ret = this->db->query->exec();
    if(!ret)
    {
        QMessageBox::critical(NULL,"错误",this->db->query->lastError().text());
        this->db->closeDB();
        return;
    }
    else
    {
        while(this->db->query->next())
        {
            QString group_str;
            this->grp->setGroupName(this->db->query->value("group_name").toString());
            this->grp->setGroupTeacherID(this->tch);
            this->grp->setGroupType(this->db->query->value("group_type").toInt());
            this->grp->setGroupID(this->db->query->value("group_user_id").toInt());
            this->grp->getinfo();
            if(this->grp->getGroupType()==0)
            {
                group_str = QString("%1-[%2]").arg(this->grp->getGroupName()).arg("学生机构");
            }
            else if(this->grp->getGroupType()==1)
            {
                group_str = QString("%1-[%2]").arg(this->grp->getGroupName()).arg("学生社团");
            }
            QStandardItem * my_group = new QStandardItem(group_str);
            item->appendRow(my_group);
            QSqlQuery query;
            query.prepare("SELECT * FROM `department` WHERE `department_group_id` = :ID");
            query.bindValue(":ID",this->grp->getGroupID());
            ret = query.exec();
            if(!ret)
            {
                QMessageBox::critical(NULL,"错误",query.lastError().text());
                this->db->closeDB();
                return;
            }
            else
            {
                while(query.next())
                {
                    this->dpment->setDepartmentGroupID(query.value("department_group_id").toInt());
                    this->dpment->setDepartmentName(query.value("department_name").toString());
                    this->dpment->setDepartmentIntroduction(query.value("department_introdution").toString());
                    QStandardItem * group_dpment = new QStandardItem(QString("%1-[%2]").arg(this->dpment->getDepartmentName()).arg("部门"));
                    my_group->appendRow(group_dpment);
                    this->dpment->getInfo();
                }
            }
        }
    }
    model->appendRow(item);
    ui->treeView_2->setModel(model);
    this->db->closeDB();
    //    QStandardItemModel * model = new QStandardItemModel(ui->treeView_2);
    //    ui->treeView_2->setEditTriggers(0);
    //    ui->treeView_2->header()->hide();
    //    QStandardItem * item = new QStandardItem("我管理的社团");
    //    QStandardItem * child = new QStandardItem("社团1");
    //    item->appendRow(child);
    //    model->appendRow(item);
    //    ui->treeView_2->setModel(model);
}
void TeacherMainWindow::CustomContextMenu(const QPoint & pos)
{
    QModelIndex index = ui->treeView_2->indexAt(pos);
    QMenu * tree_menu = new QMenu(this);
    QStandardItem * tmpItem = model->itemFromIndex(index);
    QAction * reflash = new QAction(this);
    reflash->setText("刷新");
    connect(reflash,&QAction::triggered,this,&TeacherMainWindow::setGroupModel);
    if(index.isValid())
    {
        //        qDebug()<<index.row()<<","<<index.column()<<"->"<<tmpItem->text();
        //        qDebug()<<tmpItem->text();
        if(tmpItem->text() == "我管理的社团")
        {
            tree_menu->addAction(reflash);
        }
        else
        {
            QStringList list = tmpItem->text().split("-");
            //            qDebug()<<list[0];
            //            qDebug()<<list[1];
            if(list[1] == "[学生机构]" || list[1] == "[学生社团]")
            {
                //                QAction * openGrp = new QAction("打开",this);

                //                tree_menu->addAction(openGrp);
                //                connect(openGrp,&QAction::triggered,[=](){
                //                    connect(this,&TeacherMainWindow::sendOpenInfo,this,&TeacherMainWindow::openGrpTableView);
                //                    emit sendOpenInfo(list);
                //                });

                //                tree_menu->addAction("打开",[=](){
                //                    emit sendOpenInfo(list);
                //                });
                //                connect(this,&TeacherMainWindow::sendOpenInfo,this,&TeacherMainWindow::openGrpTableView,Qt::UniqueConnection);
                QAction * openGrp = new QAction(this);
                openGrp->setText("打开");
                tree_menu->addAction(openGrp);
                connect(openGrp,&QAction::triggered,[=](){
                    connect(this,&TeacherMainWindow::sendOpenInfo,this,&TeacherMainWindow::openGrpTableView,Qt::UniqueConnection);
                    emit sendOpenInfo(list);
                });
            }
            else
            {
                QAction * openDpment = new QAction(this);
                openDpment->setText("打开");
                tree_menu->addAction(openDpment);
                connect(openDpment,&QAction::triggered,[=](){
                    connect(this,&TeacherMainWindow::sendOpenInfo2,this,&TeacherMainWindow::opendpmentTableView,Qt::UniqueConnection);
                    emit sendOpenInfo2(list);
                });
                //                tree_menu->addAction("打开部门所在的社团",[=](){

                //                    emit sendOpenInfo3(list);
                //                });
                //                connect(this,&TeacherMainWindow::sendOpenInfo3,this,&TeacherMainWindow::opendpmentTableViewByGrp,Qt::UniqueConnection);
                //                tree_menu->addAction("刷新",this->ui->treeView_2,&TeacherMainWindow::setGroupModel);
                QAction * openGrpByDpment = new QAction(this);
                openGrpByDpment->setText("打开部门所在的社团");
                tree_menu->addAction(openGrpByDpment);
                connect(openGrpByDpment,&QAction::triggered,[=](){
                    connect(this,&TeacherMainWindow::sendOpenInfo3,this,&TeacherMainWindow::opendpmentTableViewByGrp,Qt::UniqueConnection);
                    emit sendOpenInfo3(list);
                });
            }
            tree_menu->addAction(reflash);
            list.clear();
        }
    }
    else
    {
        tree_menu->addAction(reflash);
    }
    tree_menu->exec(QCursor::pos());
}
void TeacherMainWindow::openGrpTableView(QStringList list)
{
    ui->widget->show();
    this->controlInfo = "group";
    setSearchWidget();
    this->grp->setGroupName(list[0]);
    if(list[1] == "[学生机构]")
    {
        this->grp->setGroupType(0);
    }
    else
    {
        this->grp->setGroupType(1);
    }
    bool ret = false;
    this->db->openDB();
    this->db->query->prepare("SELECT * FROM `group` WHERE `group_name` = :NAME");
    this->db->query->bindValue(":NAME",this->grp->getGroupName());
    ret = this->db->query->exec();
    if(!ret)
    {
        QMessageBox::critical(NULL,"错误",this->db->query->lastError().text());
        this->db->closeDB();
        return;
    }
    if(this->db->query->next())
    {
        this->grp->setGroupID(this->db->query->value("group_user_id").toInt());
        this->grp->setGroupTeacherID(this->db->query->value("group_teacher_id").toInt());
    }
    else
    {
        QMessageBox::critical(NULL,"错误",QString("查询无结果@").arg(this->db->query->lastQuery()));
        this->db->closeDB();
        return;
    }
    //    this->db->query->prepare("SELECT * FROM `department` WHERE `department_group_id` = :ID");
    //    this->db->query->bindValue(":ID",this->grp->getGroupID());
    //    ret = this->db->query->exec();
    //    if(!ret)
    //    {
    //        QMessageBox::critical(NULL,"错误",this->db->query->lastError().text());
    //        this->db->closeDB();
    //        return;
    //    }
    //    if(this->db->query->next())
    //    {
    //        this->mainTableView->setQuery(*(this->db->query));
    //        this->mainTableView->removeColumn(0);
    //        this->mainTableView->removeColumn(1);
    //        this->mainTableView->setHeaderData(0,Qt::Horizontal,"部门名称");
    //        this->mainTableView->setHeaderData(1,Qt::Horizontal,"部门简介");
    //        ui->tableView->setModel(this->mainTableView);
    //        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //设置表对齐
    //        ui->tableView->show();
    //    }
    //    else
    //    {
    //        QMessageBox::information(NULL,"信息","没有部门");
    //        this->db->closeDB();
    //        return;
    //    }

    this->MainTableView = new QSqlTableModel(this);

    this->MainTableView->setTable("department");
    this->MainTableView->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->MainTableView->setFilter(QString("department_group_id = %1").arg(this->grp->getGroupID()));
    //    this->MainTableView->removeColumn(1);
    //    this->MainTableView->removeColumn(0);
    this->MainTableView->setHeaderData(0,Qt::Horizontal,"部门ID");
    this->MainTableView->setHeaderData(1,Qt::Horizontal,"社团/机构ID");
    this->MainTableView->setHeaderData(2,Qt::Horizontal,"部门名称");
    this->MainTableView->setHeaderData(3,Qt::Horizontal,"部门简介");
    this->MainTableView->select();
    ui->tableView->setModel(this->MainTableView);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //设置表对齐
    ui->tableView->show();
    //    this->db->closeDB();
    return;
}
void TeacherMainWindow::opendpmentTableView(QStringList list)
{
    ui->widget->show();
    this->controlInfo = "department";
    setSearchWidget();
    this->dpment->setDepartmentName(list[0]);   //获取社团名
    int ret = false;
    this->db->openDB();
    this->db->query->prepare("SELECT * FROM `department` WHERE `department_name` = :NAME");
    this->db->query->bindValue(":NAME",this->dpment->getDepartmentName());
    ret = this->db->query->exec();
    if(!ret)
    {
        QMessageBox::critical(NULL,"错误",this->db->query->lastError().text());
        this->db->closeDB();
        return;
    }
    if(this->db->query->next())
    {
        this->dpment->setDepartmentID(this->db->query->value("department_id").toInt());
        this->dpment->setDepartmentGroupID(this->db->query->value("department_group_id").toInt());
        this->dpment->setDepartmentIntroduction(this->db->query->value("department_introdution").toString());
    }
    else
    {
        QMessageBox::critical(NULL,"错误",QString("查询无结果@").arg(this->db->query->lastQuery()));
        this->db->closeDB();
        return;
    }
    //    this->db->query->prepare("SELECT * FROM `student` WHERE `student_id` IN (SELECT `studentdependence_student_id` FROM `studentdependence` WHERE `studentdependence_department_id` = :ID)");
    //    this->db->query->bindValue(":ID",this->dpment->getDepartmentID());
    //    ret = this->db->query->exec();
    //    if(!ret)
    //    {
    //        QMessageBox::critical(NULL,"错误",this->db->query->lastError().text());
    //        this->db->closeDB();
    //        return;
    //    }
    //    if(this->db->query->next())
    //    {
    //        this->mainTableView->setQuery(*(this->db->query));
    //        this->mainTableView->setHeaderData(0,Qt::Horizontal,"学生ID");
    //        this->mainTableView->setHeaderData(1,Qt::Horizontal,"学生性别");
    //        this->mainTableView->setHeaderData(2,Qt::Horizontal,"学生姓名");
    //        ui->tableView->setModel(this->mainTableView);
    //        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //设置表对齐
    //        ui->tableView->show();
    //    }
    //    else
    //    {
    //        QMessageBox::information(NULL,"信息","没有成员");
    //        this->db->closeDB();
    //        return;
    //    }
    this->RMainTableView = new QSqlRelationalTableModel(this);
    this->RMainTableView->setTable("studentdependence");
    this->RMainTableView->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->RMainTableView->setRelation(3,QSqlRelation("student","student_id","student_name"));
    this->RMainTableView->setRelation(1,QSqlRelation("department","department_id","department_name"));
    this->RMainTableView->setFilter(QString("studentdependence_department_id = %1").arg(this->dpment->getDepartmentID()));
    //    this->RMainTableView->removeColumn(2);
    //    this->RMainTableView->removeColumn(0);
    this->RMainTableView->select();
    this->RMainTableView->setHeaderData(0,Qt::Horizontal,"社团/机构ID");
    this->RMainTableView->setHeaderData(1,Qt::Horizontal,"所属部门（修改请输入部门ID）");
    this->RMainTableView->setHeaderData(2,Qt::Horizontal,"归属ID");
    this->RMainTableView->setHeaderData(3,Qt::Horizontal,"学生姓名（修改请输入学生ID）");
    ui->tableView->setModel(this->RMainTableView);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //设置表对齐
    ui->tableView->show();
    //    this->db->closeDB();
    return;
}

void TeacherMainWindow::openTableViewByDC(const QModelIndex & index)
{
    QStandardItem * item = model->itemFromIndex(index);
    QString str = item->text();
    if(str == "我管理的社团")
        return;
    QStringList list = str.split("-");
    //    qDebug()<<list[0]<<","<<list[1];
    if(list[1]=="[学生机构]" || list[1] == "[学生社团]")
    {
        openGrpTableView(list);
    }
    else if(list[1]=="[部门]")
    {
        opendpmentTableView(list);
    }
}
void TeacherMainWindow::opendpmentTableViewByGrp(QStringList list)
{
    ui->widget->show();
    bool ret = false;
    this->dpment->setDepartmentName(list[0]);
    this->db->openDB();
    this->db->query->prepare("SELECT * FROM `group` WHERE `group_user_id` IN (SELECT `department_group_id` FROM `department` WHERE `department_name` = :NAME)");
    this->db->query->bindValue(":NAME",this->dpment->getDepartmentName());
    ret = this->db->query->exec();
    if(!ret)
    {
        QMessageBox::critical(NULL,"错误",this->db->query->lastError().text());
        this->db->closeDB();
        return;
    }
    if(this->db->query->next())
    {
        QStringList list;
        list<<this->db->query->value("group_name").toString();
        int type = this->db->query->value("group_type").toInt();
        if(type == 0)
        {
            list<<"[学生机构]";
        }
        else if(type == 1)
        {
            list<<"[学生社团]";
        }
        openGrpTableView(list);
    }
    else
    {
        QMessageBox::critical(NULL,"错误","数据库无法查询到该信息");
        this->db->closeDB();
        return;
    }
}

void TeacherMainWindow::on_pushButton_add_clicked()
{
    if(this->ui->widget->isHidden())
    {
        return;
    }
    this->db->openDB();
    if(this->controlInfo == "group")
    {
        int rowNum = this->MainTableView->rowCount();
        int ID = this->MainTableView->record(rowNum - 1).value("department_id").toInt();
        this->MainTableView->insertRow(rowNum);
        this->MainTableView->setData(this->MainTableView->index(rowNum,0),ID+1);
        this->MainTableView->submitAll();
    }
    if(this->controlInfo == "department")
    {
        int rowNum = this->RMainTableView->rowCount();
        int ID = this->RMainTableView->record(rowNum - 1).value("studentdependence_id").toInt();
        this->RMainTableView->insertRow(rowNum);
        this->RMainTableView->setData(this->RMainTableView->index(rowNum,2),ID+1);
        this->RMainTableView->submitAll();
        qDebug()<<this->controlInfo;
    }
    return;
}

void TeacherMainWindow::on_pushButton_change_clicked()
{
    if(this->ui->widget->isHidden())
    {
        return;
    }
    if(this->controlInfo == "group")
    {
        int info = QMessageBox::question(this,"修改","确定修改吗？");
        if(info==QMessageBox::Yes)
        {
            this->MainTableView->database().transaction();
            if(this->MainTableView->submitAll())
            {
                this->MainTableView->database().commit();
                QMessageBox::information(this,"提交","提交成功");
                setGroupModel();
            }
            else
            {
                QMessageBox::critical(this,"错误",QString("数据库错误:%1").arg(this->MainTableView->lastError().text()));
            }
        }
        else
        {
            this->MainTableView->database().rollback();
        }
    }
    if(this->controlInfo == "department")
    {
        int info = QMessageBox::question(this,"修改","确定修改吗？");
        if(info==QMessageBox::Yes)
        {
            this->RMainTableView->database().transaction();
            if(this->RMainTableView->submitAll())
            {
                this->RMainTableView->database().commit();
                QMessageBox::information(this,"提交","提交成功");
                setGroupModel();
            }
            else
            {
                QMessageBox::critical(this,"错误",QString("数据库错误:%1").arg(this->RMainTableView->lastError().text()));
            }
        }
        else
        {
            this->RMainTableView->database().rollback();
        }
    }
}

void TeacherMainWindow::on_pushButton_delete_clicked()
{
    if(this->ui->widget->isHidden())
    {
        return;
    }
    if(this->controlInfo == "group")
    {
        int curRow = this->ui->tableView->currentIndex().row();
        this->MainTableView->removeRow(curRow);
        int info = QMessageBox::question(this,"删除","确定删除吗？");
        if(info==QMessageBox::Yes)
        {
            this->MainTableView->database().transaction();
            if(this->MainTableView->submitAll())
            {
                this->MainTableView->database().commit();
                QMessageBox::information(this,"删除","删除成功");
                setGroupModel();
            }
            else
            {
                QMessageBox::critical(this,"错误",QString("数据库错误:%1").arg(this->MainTableView->lastError().text()));
            }
        }
        else
        {
            this->MainTableView->database().rollback();
        }
    }
    if(this->controlInfo == "department")
    {
        int curRow = this->ui->tableView->currentIndex().row();
        this->RMainTableView->removeRow(curRow);
        int info = QMessageBox::question(this,"删除","确定删除吗？");
        if(info==QMessageBox::Yes)
        {
            this->RMainTableView->database().transaction();
            if(this->RMainTableView->submitAll())
            {
                this->RMainTableView->database().commit();
                QMessageBox::information(this,"删除","删除成功");
                setGroupModel();
            }
            else
            {
                QMessageBox::critical(this,"错误",QString("数据库错误:%1").arg(this->RMainTableView->lastError().text()));
            }
        }
        else
        {
            this->RMainTableView->database().rollback();
        }
    }
}

void TeacherMainWindow::on_pushButton_search_clicked()
{
    if(this->ui->widget->isHidden())
    {
        return;
    }
    QString search = this->ui->lineEdit->text();
    QString condition = this->ui->comboBox->currentText();
    if(this->controlInfo == "group")
    {
        if(condition == "部门ID")
        {
            this->MainTableView->setFilter(QString("department_id = %1").arg(search));
            this->MainTableView->select();
        }
//        if(condition == "社团/机构ID")
//        {
//            this->MainTableView->setFilter(QString("department_group_id = %1").arg(search));
//            this->MainTableView->select();
//        }
        if(condition == "部门名称")
        {
//            QString str = QString("department_name = %1").arg(search);
            this->MainTableView->setFilter(QString("department_name = '%1'").arg(search));
//            qDebug()<<str;
            this->MainTableView->select();
        }
        if(condition == "部门简介")
        {
            this->MainTableView->setFilter(QString("department_introdution = '%1'").arg(search));
            this->MainTableView->select();
        }
    }
    if(this->controlInfo == "department")
    {
//        if(condition == "社团/机构ID")
//        {
//            this->RMainTableView->setFilter(QString("studentdependence_group_id = %1").arg(search));
//            this->RMainTableView->select();
//        }
//        if(condition == "所属部门")
//        {
//            this->RMainTableView->setFilter(QString("studentdependence_department_id = %1").arg(search));
//            this->RMainTableView->select();
//        }
        if(condition == "归属ID")
        {
            this->RMainTableView->setFilter(QString("studentdependence_id = %1").arg(search));
            this->RMainTableView->select();
        }
//        if(condition == "学生姓名")
//        {
//            this->RMainTableView->setFilter(QString("studentdependence_student_id = %1").arg(search));
//            this->RMainTableView->select();
//        }
    }
}

void TeacherMainWindow::on_pushButton_reset_clicked()
{
    this->ui->lineEdit->clear();
}
