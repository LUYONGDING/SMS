#include "rootmainwindow.h"
#include "ui_rootmainwindow.h"

RootMainWindow::RootMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RootMainWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->us = new user(this);
    this->infoUs = new user(this);
    this->db = new DBconnt(this);
    this->tch = new teacher(this);
    this->grp = new group(this);
    this->dpment = new department(this);
    this->stu = new student(this);
    this->timer = new QTimer(this);
    this->currentTimeLabel = new QLabel(this);
    setMarginSpacing();
    this->setWindowIcon(QIcon(":/mainWin/Icon/guishen_0131ev05b08mg01.png"));
    QWidget * tempWidget = new QWidget(this);
    ui->dockWidget_left->setTitleBarWidget(tempWidget);
    this->ui->widget_2->hide();
    connect(ui->actionabout,&QAction::triggered,[=](){
        QString about = "Based on Qt 5.8.0(MSVC 2015 , 32 bit)\n\nBuilt on Mon Mar 11 21:31:43 2019 +0800\n\nDemo ver 1.0\n\nCopyright © 2019 luyongding. All Rights Reserved.\n\nThis progarm only used by personal graduation project.If you want to use it for other purposes,please ask the auther first.\nlyd2233970479@163.com";
        QMessageBox::about(this,"关于",about);
    });
    connect(ui->actionaboutQt,&QAction::triggered,[=](){
        QMessageBox::aboutQt(this);
    });
    connect(ui->actionuserInfo,&QAction::triggered,this,[=](){
        QString info = QString("用户名：%1\n\n用户类型:管理员").arg(this->infoUs->getUserName());
        QMessageBox::information(this,"用户信息",info);
    });
    connect(ui->actionloginOut,&QAction::triggered,this,[=](){
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
    connect(this->ui->actionshow_control_widget,&QAction::triggered,this,[=](){
        this->ui->dockWidget_ToolButton->show();
    });
    connect(this->ui->actionshow_search_widget,&QAction::triggered,this,[=](){
        this->ui->dockWidget->show();
    });
    this->ui->statusbar->addWidget(this->currentTimeLabel);
    connect(this->timer,&QTimer::timeout,this,[=](){
        QDateTime current_time = QDateTime::currentDateTime();
        QString timestr = current_time.toString("yyyy年MM月dd日 hh:mm:ss");
        this->currentTimeLabel->setText(timestr);
    });
}

RootMainWindow::~RootMainWindow()
{
    delete ui;
//    delete this->dpment;
//    delete this->grp;
//    delete this->tch;
//    delete this->db;
//    delete this->us;
//    delete this->infoUs;
}

void RootMainWindow::setMarginSpacing()
{
    this->layout()->setMargin(0);
    this->layout()->setSpacing(0);
    this->ui->dockWidget_left->layout()->setMargin(0);
    this->ui->dockWidget_left->layout()->setSpacing(0);
    this->ui->dockWidgetContents->layout()->setMargin(0);
    this->ui->dockWidgetContents->layout()->setSpacing(0);
    this->ui->tab_user->layout()->setMargin(0);
    this->ui->tab_user->layout()->setSpacing(0);
    this->ui->tab_group->layout()->setMargin(0);
    this->ui->tab_group->layout()->setSpacing(0);
    this->ui->tab_student->layout()->setMargin(0);
    this->ui->tab_student->layout()->setSpacing(0);
    this->ui->tab_teacher->layout()->setMargin(0);
    this->ui->tab_teacher->layout()->setSpacing(0);
    this->ui->centralwidget->layout()->setMargin(0);
    this->ui->centralwidget->layout()->setSpacing(0);
    this->ui->widget_2->layout()->setMargin(0);
    this->ui->widget_2->layout()->setSpacing(0);
}

void RootMainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/mainWin/background/guishen_0039ev05a07.jpg"));

}

void RootMainWindow::setUserModel()
{
    bool ret = 0;
    this->userModel = new QStandardItemModel(this);
    ui->treeView_user->setEditTriggers(0);
    ui->treeView_user->header()->hide();
    QStandardItem * item_2 = new QStandardItem("社团用户");
    QStandardItem * item_1 = new QStandardItem("教师用户");
    QStandardItem * item_0 = new QStandardItem("管理员用户");
    this->db->openDB();
    this->db->query->prepare("SELECT * FROM `user` WHERE `user_name` != :NAME");
    this->db->query->bindValue(":NAME","root");
    ret = this->db->query->exec();
    if(!ret)
    {
        QMessageBox::critical(NULL,"错误",this->db->query->lastError().text());
        this->db->closeDB();
        return;
    }
    while(this->db->query->next())
    {
        //code
        this->us->setUserID(this->db->query->value("user_id").toInt());
        this->us->setUserName(this->db->query->value("user_name").toString());
        this->us->setUserPasswd(this->db->query->value("user_passwd").toString());
        this->us->setUserType(this->db->query->value("user_type").toInt());
        if(this->us->getUserType() == 2)
        {
            QStandardItem * user_2 = new QStandardItem(QString(this->us->getUserName()));
            item_2->appendRow(user_2);
        }
        if(this->us->getUserType() == 1)
        {
            QStandardItem * user_1 = new QStandardItem(QString(this->us->getUserName()));
            item_1->appendRow(user_1);
        }
        if(this->us->getUserType() == 0)
        {
            QStandardItem * user_0 = new QStandardItem(QString(this->us->getUserName()));
            item_0->appendRow(user_0);
        }
    }
    this->userModel->appendRow(item_2);
    this->userModel->appendRow(item_1);
    if(this->isRoot)
    {
        this->userModel->appendRow(item_0);
    }
    this->ui->treeView_user->setModel(this->userModel);
    connect(ui->treeView_user,&QTreeView::doubleClicked,this,&RootMainWindow::openTableViewInUserByDC);
}

void RootMainWindow::setGroupModel()
{
    bool ret = 0;
    this->groupModel = new QStandardItemModel(this);
    ui->treeView_group->setEditTriggers(0);
    ui->treeView_group->header()->hide();
    QStandardItem * item1 = new QStandardItem("学生社团");
    QStandardItem * item0 = new QStandardItem("学生机构");
    this->db->openDB();
    this->db->query->prepare("SELECT * FROM `group`");
    ret = this->db->query->exec();
    if(!ret)
    {
        QMessageBox::critical(NULL,"错误",this->db->query->lastError().text());
        this->db->closeDB();
        return;
    }
    while(this->db->query->next())
    {
        this->grp->setGroupID(this->db->query->value("group_user_id").toInt());
        this->grp->setGroupName(this->db->query->value("group_name").toString());
        this->grp->setGroupTeacherID(this->db->query->value("group_teacher_id").toInt());
        this->grp->setGroupType(this->db->query->value("group_type").toInt());
        if(0==this->grp->getGroupType())   //学生机构
        {
            QStandardItem * group_0 = new QStandardItem(QString("%1-[学生机构]").arg(this->grp->getGroupName()));
            item0->appendRow(group_0);
            QSqlQuery queryForGroup_0;
            queryForGroup_0.prepare("SELECT * FROM `department` WHERE `department_group_id` = :ID");
            queryForGroup_0.bindValue(":ID",this->grp->getGroupID());
            ret = queryForGroup_0.exec();
            if(!ret)
            {
                QMessageBox::critical(NULL,"错误",queryForGroup_0.lastError().text());
                this->db->closeDB();
                return;
            }
            while(queryForGroup_0.next())
            {
                this->dpment->setDepartmentID(queryForGroup_0.value("department_id").toInt());
                this->dpment->setDepartmentGroupID(queryForGroup_0.value("department_group_id").toInt());
                this->dpment->setDepartmentName(queryForGroup_0.value("department_name").toString());
                this->dpment->setDepartmentIntroduction(queryForGroup_0.value("department_introdution").toString());
                QStandardItem * dpment_0 = new QStandardItem(QString("%1-[部门]").arg(this->dpment->getDepartmentName()));
                group_0->appendRow(dpment_0);
            }
        }
        if(1==this->grp->getGroupType())
        {
            QStandardItem * group_1 = new QStandardItem(QString("%1-[学生社团]").arg(this->grp->getGroupName()));
            item1->appendRow(group_1);
            QSqlQuery queryForGroup_1;
            queryForGroup_1.prepare("SELECT * FROM `department` WHERE `department_group_id` = :ID");
            queryForGroup_1.bindValue(":ID",this->grp->getGroupID());
            ret = queryForGroup_1.exec();
            if(!ret)
            {
                QMessageBox::critical(NULL,"错误",queryForGroup_1.lastError().text());
                this->db->closeDB();
                return;
            }
            while(queryForGroup_1.next())
            {
                this->dpment->setDepartmentID(queryForGroup_1.value("department_id").toInt());
                this->dpment->setDepartmentGroupID(queryForGroup_1.value("department_group_id").toInt());
                this->dpment->setDepartmentName(queryForGroup_1.value("department_name").toString());
                this->dpment->setDepartmentIntroduction(queryForGroup_1.value("department_introdution").toString());
                QStandardItem * dpment_1 = new QStandardItem(QString("%1-[部门]").arg(this->dpment->getDepartmentName()));
                group_1->appendRow(dpment_1);
            }
        }
    }
    this->groupModel->appendRow(item0);
    this->groupModel->appendRow(item1);
    ui->treeView_group->setModel(this->groupModel);
    connect(ui->treeView_group,&QTreeView::doubleClicked,this,&RootMainWindow::openTableViewInGrpByDC);
}

void RootMainWindow::setStuModel()
{
    bool ret = false;
    this->stuModel = new QStandardItemModel(this);
    ui->treeView_student->setEditTriggers(0);
    ui->treeView_student->header()->hide();
    QStandardItem * item = new QStandardItem("学生表");
    this->stuModel->appendRow(item);
    this->ui->treeView_student->setModel(this->stuModel);
    connect(ui->treeView_student,&QTreeView::doubleClicked,this,&RootMainWindow::openTableViewInStuByDC);
}

void RootMainWindow::setTchModel()
{
    bool ret = false;
    this->tchModel = new QStandardItemModel(this);
    ui->treeView_teacher->setEditTriggers(0);
    ui->treeView_teacher->header()->hide();
    QStandardItem * item = new QStandardItem("教师表");
    this->tchModel->appendRow(item);
    this->ui->treeView_teacher->setModel(this->tchModel);
    connect(ui->treeView_teacher,&QTreeView::doubleClicked,this,&RootMainWindow::openTableViewInTchByDC);
}

void RootMainWindow::setSearchWidget()
{
    this->ui->comboBox->clear();
    if(this->controlInfo == "GrpUser" || this->controlInfo=="TchUser" || this->controlInfo == "rootUser")
    {
        this->ui->comboBox->addItem("用户ID");
        this->ui->comboBox->addItem("用户名");
    }
    if(this->controlInfo == "Grp_0Grp" || this->controlInfo == "Grp_1Grp")
    {
        this->ui->comboBox->addItem("社团ID");
        this->ui->comboBox->addItem("社团名称");
        this->ui->comboBox->addItem("社团指导教师ID");
    }
    if(this->controlInfo=="DpmentGrp")
    {
        this->ui->comboBox->addItem("部门ID");
        this->ui->comboBox->addItem("部门名称");
    }
    if(this->controlInfo=="StuGrp")
    {
        this->ui->comboBox->addItem("学生ID");
        //       this->ui->comboBox->addItem("学生性别");
        this->ui->comboBox->addItem("学生姓名");
    }
    if(this->controlInfo=="StuStu")
    {
        this->ui->comboBox->addItem("学生ID");
        this->ui->comboBox->addItem("学生性别");
        this->ui->comboBox->addItem("学生姓名");
    }
    if(this->controlInfo=="TchTch")
    {
        this->ui->comboBox->addItem("教师ID");
        this->ui->comboBox->addItem("教师用户ID");
        this->ui->comboBox->addItem("教师姓名");
        this->ui->comboBox->addItem("教师性别");
    }
}

void RootMainWindow::getUserInfo(user & us)
{
    *(this->infoUs) = us;
    if(this->infoUs->getUserName()=="root")
    {
        this->isRoot = true;
        this->setWindowTitle(QString("%1 [ROOT管理员] - 学生社团管理系统").arg(this->infoUs->getUserName()));
    }
    else
    {
        this->setWindowTitle(QString("%1 [管理员] - 学生社团管理系统").arg(this->infoUs->getUserName()));
    }
    setGroupModel();
    setUserModel();
    setStuModel();
    setTchModel();
    connect(this->ui->treeView_user,&QTreeView::customContextMenuRequested,this,&RootMainWindow::CustomContextMenu_User);
    connect(this->ui->treeView_group,&QTreeView::customContextMenuRequested,this,&RootMainWindow::CustomContextMenu_Grp);
    connect(this->ui->treeView_student,&QTreeView::customContextMenuRequested,this,&RootMainWindow::CustomContextMenu_Stu);
    connect(this->ui->treeView_teacher,&QTreeView::customContextMenuRequested,this,&RootMainWindow::CustomContextMenu_Tch);
}

void RootMainWindow::CustomContextMenu_User(const QPoint &pos)
{
    QModelIndex index = ui->treeView_user->indexAt(pos);
    QMenu * tree_menu = new QMenu(this->ui->treeView_user);
    QStandardItem * tmpItem = this->userModel->itemFromIndex(index);
    QAction * reflash = new QAction(this);
    reflash->setText("刷新");
    connect(reflash,&QAction::triggered,this,&RootMainWindow::setUserModel);
    tree_menu->addAction(reflash);
    if(index.isValid())
    {
        if(tmpItem->text()=="社团用户")
        {
            QAction * openGrp = new QAction(this);
            openGrp->setText("打开社团用户");
            tree_menu->addAction(openGrp);
            connect(openGrp,&QAction::triggered,this,&RootMainWindow::openGrpTableViewInUser);
        }
        else if(tmpItem->text()=="教师用户")
        {
            QAction * openTch = new QAction(this);
            openTch->setText("打开教师用户");
            tree_menu->addAction(openTch);
            connect(openTch,&QAction::triggered,this,&RootMainWindow::openTchTableViewInUser);
        }
        else if(tmpItem->text()=="管理员用户")
        {
            QAction * openRt = new QAction(this);
            openRt->setText("打开管理员用户");
            tree_menu->addAction(openRt);
            connect(openRt,&QAction::triggered,this,&RootMainWindow::openRtTableViewInUser);
        }
    }
    tree_menu->exec(QCursor::pos());
}

void RootMainWindow::CustomContextMenu_Grp(const QPoint &pos)
{
    QModelIndex index = ui->treeView_group->indexAt(pos);
    QMenu * tree_menu = new QMenu(this->ui->treeView_group);
    QStandardItem * tmpItem = this->groupModel->itemFromIndex(index);
    QAction * reflash = new QAction(this);
    reflash->setText("刷新");
    connect(reflash,&QAction::triggered,this,&RootMainWindow::setGroupModel);
    tree_menu->addAction(reflash);

    if(index.isValid())
    {
        if(tmpItem->text()=="学生社团")
        {
            QAction * openAllGrp_1 = new QAction(this);
            openAllGrp_1->setText("打开学生社团");
            tree_menu->addAction(openAllGrp_1);
            connect(openAllGrp_1,&QAction::triggered,this,&RootMainWindow::openGrp_1TableViewInGrp);
        }
        else if(tmpItem->text()=="学生机构")
        {
            QAction * openAllGrp_0 = new QAction(this);
            openAllGrp_0->setText("打开学生机构");
            tree_menu->addAction(openAllGrp_0);
            connect(openAllGrp_0,&QAction::triggered,this,&RootMainWindow::openGrp_0TableViewInGrp);
        }
        else
        {
            QStringList list = tmpItem->text().split("-");
            if(list[1]=="[学生社团]" || list[1] == "[学生机构]")
            {
                QAction * openGrp = new QAction(this);
                openGrp->setText("打开");
                tree_menu->addAction(openGrp);
                connect(openGrp,&QAction::triggered,[=](){
                    connect(this,&RootMainWindow::sendOpenInfoList_Grp,this,&RootMainWindow::openGrpTableViewInGrp,Qt::UniqueConnection);
                    emit sendOpenInfoList_Grp(list);
                });
            }
            else if(list[1] == "[部门]")
            {
                QAction * openDpment = new QAction(this);
                openDpment->setText("打开");
                tree_menu->addAction(openDpment);
                connect(openDpment,&QAction::triggered,[=](){
                    connect(this,&RootMainWindow::sendOpenInfoList_Dpment,this,&RootMainWindow::openDpmentTableViewInGrp,Qt::UniqueConnection);
                    emit sendOpenInfoList_Dpment(list);
                });
            }
        }
    }
    tree_menu->exec(QCursor::pos());
}

void RootMainWindow::CustomContextMenu_Stu(const QPoint &pos)
{
    QModelIndex index = ui->treeView_student->indexAt(pos);
    QMenu * tree_menu = new QMenu(this->ui->treeView_student);
    QStandardItem * tmpItem = this->stuModel->itemFromIndex(index);
    QAction * reflash = new QAction(this);
    reflash->setText("刷新");
    connect(reflash,&QAction::triggered,this,&RootMainWindow::setStuModel);
    if(index.isValid())
    {
        QAction * openStu = new QAction(this);
        openStu->setText("打开学生表");
        tree_menu->addAction(openStu);
        connect(openStu,&QAction::triggered,this,&RootMainWindow::openStuTableViewInStu);
    }
    tree_menu->exec(QCursor::pos());
}

void RootMainWindow::CustomContextMenu_Tch(const QPoint &pos)
{
    QModelIndex index = ui->treeView_teacher->indexAt(pos);
    QMenu * tree_menu = new QMenu(this->ui->treeView_teacher);
    QStandardItem * tmpItem = this->tchModel->itemFromIndex(index);
    QAction * reflash = new QAction(this);
    reflash->setText("刷新");
    connect(reflash,&QAction::triggered,this,&RootMainWindow::setTchModel);
    if(index.isValid())
    {
        QAction * openTch = new QAction(this);
        openTch->setText("打开教师表");
        tree_menu->addAction(openTch);
        connect(openTch,&QAction::triggered,this,&RootMainWindow::openTchTableViewInTch);
    }
    tree_menu->exec(QCursor::pos());
}

void RootMainWindow::openGrpTableViewInUser()
{
    this->controlInfo = "GrpUser";
    setSearchWidget();
    this->ui->widget_2->show();
    this->db->openDB();
    this->MainTableView = new QSqlTableModel(this);
    this->MainTableView->setTable("user");
    this->MainTableView->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->MainTableView->setFilter(QString("user_type = %1").arg("2"));
    this->MainTableView->select();
    this->MainTableView->setHeaderData(0,Qt::Horizontal,"用户ID");
    this->MainTableView->setHeaderData(1,Qt::Horizontal,"用户名");
    this->MainTableView->setHeaderData(2,Qt::Horizontal,"用户密码");
    this->MainTableView->setHeaderData(3,Qt::Horizontal,"用户类型");
    ui->tableView->setModel(this->MainTableView);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->show();
    return;
}

void RootMainWindow::openTchTableViewInUser()
{
    this->controlInfo = "TchUser";
    setSearchWidget();
    this->ui->widget_2->show();
    this->db->openDB();
    this->MainTableView = new QSqlTableModel(this);
    this->MainTableView->setTable("user");
    this->MainTableView->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->MainTableView->setFilter("user_type = 1");
    this->MainTableView->select();
    this->MainTableView->setHeaderData(0,Qt::Horizontal,"用户ID");
    this->MainTableView->setHeaderData(1,Qt::Horizontal,"用户名");
    this->MainTableView->setHeaderData(2,Qt::Horizontal,"用户密码");
    this->MainTableView->setHeaderData(3,Qt::Horizontal,"用户类型");
    ui->tableView->setModel(this->MainTableView);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->show();
}

void RootMainWindow::openRtTableViewInUser()
{
    this->controlInfo = "rootUser";
    setSearchWidget();
    this->ui->widget_2->show();
    this->db->openDB();
    this->MainTableView = new QSqlTableModel(this);
    this->MainTableView->setTable("user");
    this->MainTableView->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->MainTableView->setFilter("user_type = 0 AND user_name != 'root'");
    this->MainTableView->select();
    //    this->MainTableView->removeColumn(3);
    this->MainTableView->setHeaderData(0,Qt::Horizontal,"用户ID");
    this->MainTableView->setHeaderData(1,Qt::Horizontal,"用户名");
    this->MainTableView->setHeaderData(2,Qt::Horizontal,"用户密码");
    this->MainTableView->setHeaderData(3,Qt::Horizontal,"用户类型");
    ui->tableView->setModel(this->MainTableView);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->show();
}

void RootMainWindow::openGrpTableViewInGrp(QStringList list)
{
    qDebug()<<list[0]<<","<<list[1];
    this->ui->widget_2->show();
    this->db->openDB();
    this->grp->setGroupName(list[0]);
    if(list[1]=="[学生机构]")
    {
        this->grp->setGroupType(0);
        this->controlInfo = "DpmentGrp";
        setSearchWidget();
    }
    else if(list[1] == "[学生社团]")
    {
        this->grp->setGroupType(1);
        this->controlInfo = "DpmentGrp";
        setSearchWidget();
    }
    bool ret = false;
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
}

void RootMainWindow::openDpmentTableViewInGrp(QStringList list)
{
    this->controlInfo="StuGrp";
    setSearchWidget();
    qDebug()<<list[0]<<","<<list[1];
    this->ui->widget_2->show();
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
    this->MainTableView = new QSqlTableModel(this);
    this->MainTableView->setTable("student");
    this->MainTableView->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->MainTableView->setFilter(QString("`student_id` IN (SELECT `studentdependence_student_id` FROM `studentdependence` WHERE `studentdependence_department_id` = %1)").arg(this->dpment->getDepartmentID()));
    this->MainTableView->select();
    this->MainTableView->setHeaderData(0,Qt::Horizontal,"学生ID");
    this->MainTableView->setHeaderData(1,Qt::Horizontal,"学生性别");
    this->MainTableView->setHeaderData(2,Qt::Horizontal,"学生姓名");
    ui->tableView->setModel(this->MainTableView);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //设置表对齐
    ui->tableView->show();
}

void RootMainWindow::openGrp_0TableViewInGrp()
{
    this->controlInfo="Grp_0Grp";
    setSearchWidget();
    this->db->openDB();
    this->ui->widget_2->show();
    this->MainTableView = new QSqlTableModel(this);
    this->MainTableView->setTable("`group`");
    this->MainTableView->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->MainTableView->setFilter(QString("`group_type` = %1").arg("0"));
    this->MainTableView->select();
    this->MainTableView->setHeaderData(0,Qt::Horizontal,"社团ID");
    this->MainTableView->setHeaderData(1,Qt::Horizontal,"社团名称");
    this->MainTableView->setHeaderData(2,Qt::Horizontal,"社团指导老师ID");
    this->MainTableView->setHeaderData(3,Qt::Horizontal,"社团类别");
    ui->tableView->setModel(this->MainTableView);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->show();
}

void RootMainWindow::openGrp_1TableViewInGrp()
{
    this->controlInfo="Grp_1Grp";
    setSearchWidget();
    this->db->openDB();
    this->ui->widget_2->show();
    this->MainTableView = new QSqlTableModel(this);
    this->MainTableView->setTable("`group`");
    this->MainTableView->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->MainTableView->setFilter("`group_type` = 1");
    this->MainTableView->select();
    this->MainTableView->setHeaderData(0,Qt::Horizontal,"社团ID");
    this->MainTableView->setHeaderData(1,Qt::Horizontal,"社团名称");
    this->MainTableView->setHeaderData(2,Qt::Horizontal,"社团指导老师ID");
    this->MainTableView->setHeaderData(3,Qt::Horizontal,"社团类别");
    ui->tableView->setModel(this->MainTableView);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //设置表对齐
    ui->tableView->show();
}

void RootMainWindow::openStuTableViewInStu()
{
    this->controlInfo="StuStu";
    setSearchWidget();
    this->db->openDB();
    this->ui->widget_2->show();
    this->MainTableView = new QSqlTableModel(this);
    this->MainTableView->setTable("`student`");
    this->MainTableView->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->MainTableView->select();
    this->MainTableView->setHeaderData(0,Qt::Horizontal,"学生ID");
    this->MainTableView->setHeaderData(1,Qt::Horizontal,"学生性别");
    this->MainTableView->setHeaderData(2,Qt::Horizontal,"学生姓名");
    ui->tableView->setModel(this->MainTableView);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //设置表对齐
    ui->tableView->show();
}

void RootMainWindow::openTchTableViewInTch()
{
    this->controlInfo="TchTch";
    setSearchWidget();
    this->db->openDB();
    this->ui->widget_2->show();
    this->MainTableView = new QSqlTableModel(this);
    this->MainTableView->setTable("`teacher`");
    this->MainTableView->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->MainTableView->select();
    this->MainTableView->setHeaderData(0,Qt::Horizontal,"教师ID");
    this->MainTableView->setHeaderData(1,Qt::Horizontal,"教师用户ID");
    this->MainTableView->setHeaderData(2,Qt::Horizontal,"教师姓名");
    this->MainTableView->setHeaderData(3,Qt::Horizontal,"教师姓别");
    ui->tableView->setModel(this->MainTableView);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //设置表对齐
    ui->tableView->show();
}

void RootMainWindow::openTableViewInUserByDC(const QModelIndex &index)
{
    QStandardItem * item = this->userModel->itemFromIndex(index);
    QString str = item->text();
    if(str == "社团用户")
    {
        openGrpTableViewInUser();
    }
    else if(str == "教师用户")
    {
        openTchTableViewInUser();
    }
    else if(str == "管理员用户")
    {
        openRtTableViewInUser();
    }
    else
    {
        return ;
    }
}

void RootMainWindow::openTableViewInGrpByDC(const QModelIndex &index)
{
    QStandardItem * item = this->groupModel->itemFromIndex(index);
    QString str = item->text();
    QStringList list = str.split("-");
    if(str == "学生机构")
    {
        openGrp_0TableViewInGrp();
    }
    else if(str == "学生社团")
    {
        openGrp_1TableViewInGrp();
    }
    else if(list[1]=="[学生社团]" || list[1]=="[学生机构]")
    {
        openGrpTableViewInGrp(list);
    }
    else if(list[1]=="[部门]")
    {
        openDpmentTableViewInGrp(list);
    }
    else
    {
        return;
    }
}

void RootMainWindow::openTableViewInStuByDC(const QModelIndex &index)
{
    QStandardItem * item = this->stuModel->itemFromIndex(index);
    QString str = item->text();
    if(str == "学生表")
    {
        openStuTableViewInStu();
    }
}

void RootMainWindow::openTableViewInTchByDC(const QModelIndex &index)
{
    QStandardItem * item = this->tchModel->itemFromIndex(index);
    QString str = item->text();
    if(str == "教师表")
    {
        openTchTableViewInTch();
    }
}

void RootMainWindow::on_pushButton_add_clicked()
{
    if(this->ui->widget_2->isHidden() || this->controlInfo=="")
    {
        return;
    }
    this->db->openDB();
    int rowNum = this->MainTableView->rowCount();
    if(this->controlInfo == "rootUser")
    {
        //        int ID = this->MainTableView->record(rowNum - 1).value("user_id").toInt();
        this->db->query->prepare("SELECT * FROM `user` WHERE `user_id` = (SELECT MAX(`user_id`) FROM `user`)");
        bool ret = this->db->query->exec();
        if(!ret)
        {
            QMessageBox::critical(this,"错误","数据库查询错误");
            return;
        }
        int ID = 0;
        if(this->db->query->next())
        {
            ID = this->db->query->value("user_id").toInt();
        }
        this->MainTableView->insertRow(rowNum);
        this->MainTableView->setData(this->MainTableView->index(rowNum,3),0);
        this->MainTableView->setData(this->MainTableView->index(rowNum,0),ID+1);
    }
    if(this->controlInfo == "TchUser")
    {
        this->db->query->prepare("SELECT * FROM `user` WHERE `user_id` = (SELECT MAX(`user_id`) FROM `user`)");
        bool ret = this->db->query->exec();
        if(!ret)
        {
            QMessageBox::critical(this,"错误","数据库查询错误");
            return;
        }
        int ID = 0;
        if(this->db->query->next())
        {
            ID = this->db->query->value("user_id").toInt();
        }
        //        int ID = this->MainTableView->record(rowNum - 1).value("user_id").toInt();
        this->MainTableView->insertRow(rowNum);
        this->MainTableView->setData(this->MainTableView->index(rowNum,3),1);
        this->MainTableView->setData(this->MainTableView->index(rowNum,0),ID+1);
    }
    if(this->controlInfo == "GrpUser")
    {
        this->db->query->prepare("SELECT * FROM `user` WHERE `user_id` = (SELECT MAX(`user_id`) FROM `user`)");
        bool ret = this->db->query->exec();
        if(!ret)
        {
            QMessageBox::critical(this,"错误","数据库查询错误");
            return;
        }
        int ID = 0;
        if(this->db->query->next())
        {
            ID = this->db->query->value("user_id").toInt();
        }
        //        int ID = this->MainTableView->record(rowNum - 1).value("user_id").toInt();
        this->MainTableView->insertRow(rowNum);
        this->MainTableView->setData(this->MainTableView->index(rowNum,3),2);
        this->MainTableView->setData(this->MainTableView->index(rowNum,0),ID+1);
    }
    if(this->controlInfo=="Grp_0Grp")
    {
        //        int rowNum = this->MainTableView->columnCount();
        this->MainTableView->insertRow(rowNum);
        this->MainTableView->setData(this->MainTableView->index(rowNum,3),0);
    }
    if(this->controlInfo=="Grp_1Grp")
    {
        //        int rowNum = this->MainTableView->columnCount();
        this->MainTableView->insertRow(rowNum);
        this->MainTableView->setData(this->MainTableView->index(rowNum,3),1);
    }
    if(this->controlInfo=="DpmentGrp")
    {
        //        qDebug()<<this->grp->getinfo();
        this->db->query->prepare("SELECT * FROM `department` WHERE `department_id` = (SELECT MAX(`department_id`) FROM `department`)");
        bool ret = this->db->query->exec();
        if(!ret)
        {
            QMessageBox::critical(this,"错误","数据库查询错误");
            return;
        }
        int ID = 0;
        if(this->db->query->next())
        {
            ID = this->db->query->value("department_id").toInt();
        }
        this->MainTableView->insertRow(rowNum);
        this->MainTableView->setData(this->MainTableView->index(rowNum,0),ID+1);
        this->MainTableView->setData(this->MainTableView->index(rowNum,1),this->grp->getGroupID());
    }
    if(this->controlInfo=="StuGrp")
    {
        this->db->query->prepare("SELECT * FROM `student` WHERE `student_id` = (SELECT MAX(`student_id`) FROM `student`)");
        bool ret = this->db->query->exec();
        if(!ret)
        {
            QMessageBox::critical(this,"错误","数据库查询错误");
            return;
        }
        int ID = 0;
        if(this->db->query->next())
        {
            ID = this->db->query->value("student_id").toInt();
        }
        this->MainTableView->insertRow(rowNum);
        this->MainTableView->setData(this->MainTableView->index(rowNum,0),ID+1);
        this->stu->setStudentID(ID+1);
    }
    if(this->controlInfo=="StuStu")
    {
        this->db->query->prepare("SELECT * FROM `student` WHERE `student_id` = (SELECT MAX(`student_id`) FROM `student`)");
        bool ret = this->db->query->exec();
        if(!ret)
        {
            QMessageBox::critical(this,"错误","数据库查询错误");
            return;
        }
        int ID = 0;
        if(this->db->query->next())
        {
            ID = this->db->query->value("student_id").toInt();
        }
        this->MainTableView->insertRow(rowNum);
        this->MainTableView->setData(this->MainTableView->index(rowNum,0),ID+1);
    }
    if(this->controlInfo=="TchTch")
    {
        this->db->query->prepare("SELECT * FROM `teacher` WHERE `teacher_id` = (SELECT MAX(`teacher_id`) FROM `teacher`)");
        bool ret = this->db->query->exec();
        if(!ret)
        {
            QMessageBox::critical(this,"错误","数据库查询错误");
            return;
        }
        int ID = 0;
        if(this->db->query->next())
        {
            ID = this->db->query->value("teacher_id").toInt();
        }
        this->MainTableView->insertRow(rowNum);
        this->MainTableView->setData(this->MainTableView->index(rowNum,0),ID+1);
    }
}

void RootMainWindow::on_pushButton_change_clicked()
{
    if(this->ui->widget_2->isHidden() || this->controlInfo=="")
    {
        return;
    }

    int info = QMessageBox::question(this,"修改","确定修改吗？");
    if(info==QMessageBox::Yes)
    {
        this->MainTableView->database().transaction();
        if(this->MainTableView->submitAll())
        {
            this->MainTableView->database().commit();
            QMessageBox::information(this,"提交","提交成功");
            if(this->controlInfo=="StuGrp")
            {
                QSqlQuery IQuery;
                IQuery.prepare("INSERT INTO `studentdependence`(`studentdependence_group_id`,`studentdependence_department_id`,`studentdependence_student_id`) VALUES(:GRPID,:DPMENTID,:STUID)");
                IQuery.bindValue(":GRPID",this->dpment->getDepartmentGroupID());
                IQuery.bindValue(":DPMENTID",this->dpment->getDepartmentID());
                IQuery.bindValue(":STUID",this->stu->getStudentID());
                bool ret = IQuery.exec();
                if(!ret)
                {
                    QMessageBox::critical(this,"错误","数据库插入错误");
                    return;
                }
            }
            //            this->controlInfo = "";
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

void RootMainWindow::on_pushButton_delete_clicked()
{
    int curRow = this->ui->tableView->currentIndex().row();
    //    int curCul = this->ui->tableView->currentIndex().column();
    int stuID;
    if(this->controlInfo=="StuGrp")
    {
        stuID = this->MainTableView->index(curRow,0).data().toInt();
        int info = QMessageBox::question(this,"删除","确定删除吗？");
        if(info==QMessageBox::Yes)
        {
            QSqlQuery DQuery;
            DQuery.prepare("DELETE FROM `studentdependence` WHERE `studentdependence_student_id` = :STUID AND `studentdependence_department_id` = :DPMENTID");
            DQuery.bindValue(":STUID",stuID);
            DQuery.bindValue(":DPMENTID",this->dpment->getDepartmentID());
            bool ret = DQuery.exec();
            if(!ret)
            {
                QMessageBox::critical(this,"错误","数据库删除错误");
                return;
            }
            QMessageBox::information(this,"删除","删除成功");
        }
        else
        {
            return;
        }
    }
    else
    {
        this->MainTableView->removeRow(curRow);
        int info = QMessageBox::question(this,"删除","确定删除吗？");
        if(info==QMessageBox::Yes)
        {
            this->MainTableView->database().transaction();
            if(this->MainTableView->submitAll())
            {
                this->MainTableView->database().commit();
                QMessageBox::information(this,"删除","删除成功");
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
}

void RootMainWindow::on_pushButton_search_clicked()
{
    if(this->ui->widget_2->isHidden() || this->controlInfo == "")
    {
        return;
    }
    QString search = this->ui->lineEdit->text();
    QString condition = this->ui->comboBox->currentText();
    if(this->controlInfo == "GrpUser" || this->controlInfo=="TchUser" || this->controlInfo == "rootUser")
    {
        int userType;
        if(this->controlInfo == "GrpUser")
        {
            userType = 2;
        }
        if(this->controlInfo == "TchUser")
        {
            userType = 1;
        }
        if(this->controlInfo == "rootUser")
        {
            userType = 0;
        }
        if(condition == "用户ID")
        {
            this->MainTableView->setFilter(QString("`user_id` = '%1' AND `user_type` = %2").arg(search).arg(userType));
            this->MainTableView->select();
        }
        if(condition == "用户名")
        {
            this->MainTableView->setFilter(QString("`user_name` = '%1' AND `user_type` = %2").arg(search).arg(userType));
            this->MainTableView->select();
        }
    }
    if(this->controlInfo == "Grp_0Grp" || this->controlInfo == "Grp_1Grp")
    {
        int grpType;
        if(this->controlInfo == "Grp_0Grp")
        {
            grpType = 0;
        }if(this->controlInfo == "Grp_1Grp")
        {
            grpType = 1;
        }
        if(condition == "社团ID")
        {
            this->MainTableView->setFilter(QString("`group_user_id` = %1 AND `group_type` = %2").arg(search).arg(grpType));
            this->MainTableView->select();
        }
        if(condition == "社团名称")
        {
            this->MainTableView->setFilter(QString("`group_name` = '%1' AND `group_type` = %2").arg(search).arg(grpType));
            this->MainTableView->select();
        }
        if(condition == "社团指导教师ID")
        {
            this->MainTableView->setFilter(QString("`group_teacher_id` = %1 AND `group_type` = %2").arg(search).arg(grpType));
            this->MainTableView->select();
        }
    }
    if(this->controlInfo=="DpmentGrp")
    {
        if(condition == "部门ID")
        {
            this->MainTableView->setFilter(QString("`department_id` = %1 AND `department_group_id` = %2").arg(search).arg(this->grp->getGroupID()));
            this->MainTableView->select();
        }
        if(condition == "部门名称")
        {
            this->MainTableView->setFilter(QString("`department_name` = '%1' AND `department_group_id` = %2").arg(search).arg(this->grp->getGroupID()));
            this->MainTableView->select();
        }
    }
    if(this->controlInfo=="StuGrp")
    {
        if(condition == "学生ID")
        {
            this->db->query->prepare("SELECT * FROM `studentdependence` WHERE `studentdependence_student_id` = :ID AND `studentdependence_department_id` = :DPMENTID");
            this->db->query->bindValue(":ID",search);
            this->db->query->bindValue(":DPMENTID",this->dpment->getDepartmentID());
            bool ret = this->db->query->exec();
            if(!ret)
            {
                QMessageBox::critical(this,"错误","数据库查询错误");
            }
            if(this->db->query->next())
            {
                this->MainTableView->setFilter(QString("`student_id` = %1 ").arg(search));
                this->MainTableView->select();
            }
            else
            {
                this->MainTableView->setFilter("`student_id` = -1");
                this->MainTableView->select();
            }
        }
        if(condition == "学生姓名")
        {
            //            this->db->query->prepare("SELECT * FROM `studentdependence` WHERE (`studentdependence_student_id` IN (SELECT `student_id` FROM `student` WHERE `student_name` = :NAME)) AND (`studentdependence_department_id` = :DPMENTID)");
            //            this->db->query->bindValue(":NAME",search);
            //            this->db->query->bindValue(":DPMENTID",this->dpment->getDepartmentID());
            //            bool ret = this->db->query->exec();
            //            if(!ret)
            //            {
            //                QMessageBox::critical(this,"错误","数据库查询错误");
            //            }
            //            if(this->db->query->next())
            //            {
            //                int dependence = this->db->query->value("studentdependence_student_id").toInt();
            //                qDebug()<<dependence;
            //                this->MainTableView->setFilter(QString("`student_id` = %1 ").arg(dependence));
            //                this->MainTableView->select();
            //            }
            this->MainTableView->setFilter(QString("`student_name` = '%1' AND (`student_id` IN (SELECT `studentdependence_student_id` FROM `studentdependence` WHERE `studentdependence_department_id` = %2))").arg(search).arg(this->dpment->getDepartmentID()));
            this->MainTableView->select();
//            else
//            {
//                this->MainTableView->setFilter("`student_name` = ''");
//                this->MainTableView->select();
//            }
        }
    }
    if(this->controlInfo=="StuStu")
    {
        if(condition=="学生ID")
        {
            this->MainTableView->setFilter(QString("`student_id` = %1").arg(search));
            this->MainTableView->select();
        }
        if(condition=="学生性别")
        {
            this->MainTableView->setFilter(QString("`student_sex` = %1").arg(search));
            this->MainTableView->select();
        }
        if(condition=="学生姓名")
        {
            this->MainTableView->setFilter(QString("student_name = '%1'").arg(search));
            this->MainTableView->select();
        }
    }
    if(this->controlInfo=="TchTch")
    {
        //           this->ui->comboBox->addItem("教师ID");
        //           this->ui->comboBox->addItem("教师用户ID");
        //           this->ui->comboBox->addItem("教师姓名");
        //           this->ui->comboBox->addItem("教师性别");
        if(condition=="教师ID")
        {
            this->MainTableView->setFilter(QString("`teacher_id` = %1").arg(search));
            this->MainTableView->select();
        }
        if(condition=="教师用户ID")
        {
            this->MainTableView->setFilter(QString("`teacher_id` = %1").arg(search));
            this->MainTableView->select();
        }
        if(condition=="教师姓名")
        {
            this->MainTableView->setFilter(QString("`teacher_name` = '%1'").arg(search));
            this->MainTableView->select();
        }
        if(condition=="教师性别")
        {
            this->MainTableView->setFilter(QString("`teacher_sex` = %1").arg(search));
            this->MainTableView->select();
        }
    }
}

void RootMainWindow::on_pushButton_reset_clicked()
{
    this->ui->lineEdit->clear();
}
