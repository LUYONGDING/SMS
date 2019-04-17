#include "rootmainwindow.h"
#include "ui_rootmainwindow.h"

RootMainWindow::RootMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RootMainWindow)
{
    ui->setupUi(this);
    this->us = new user();
    this->db = new DBconnt();
    this->tch = new teacher();
    this->grp = new group();
    this->dpment = new department();
    setMarginSpacing();
    this->setWindowIcon(QIcon(":/mainWin/Icon/guishen_0131ev05b08mg01.png"));
    QWidget * tempWidget = new QWidget(this);
    ui->dockWidget_left->setTitleBarWidget(tempWidget);
    this->ui->widget_2->hide();
}

RootMainWindow::~RootMainWindow()
{
    delete ui;
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
    this->userModel->appendRow(item_0);
    this->ui->treeView_user->setModel(this->userModel);
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
}

void RootMainWindow::getUserInfo(user *us)
{
    this->us = us;
    this->setWindowTitle(QString("%1 [管理员] - 学生社团管理系统").arg(this->us->getUserName()));
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
        }
        else if(tmpItem->text()=="教师用户")
        {
            QAction * openTch = new QAction(this);
            openTch->setText("打开教师用户");
            tree_menu->addAction(openTch);
        }
        else if(tmpItem->text()=="管理员用户")
        {
            QAction * openRt = new QAction(this);
            openRt->setText("打开管理员用户");
            tree_menu->addAction(openRt);
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
    QStringList list = tmpItem->text().split("-");
    if(index.isValid())
    {
        if(tmpItem->text()=="学生社团")
        {
            QAction * openAllGrp_1 = new QAction(this);
            openAllGrp_1->setText("打开学生社团");
            tree_menu->addAction(openAllGrp_1);
        }
        else if(tmpItem->text()=="学生机构")
        {
            QAction * openAllGrp_0 = new QAction(this);
            openAllGrp_0->setText("打开学生机构");
            tree_menu->addAction(openAllGrp_0);
        }
        else if(list[1]=="[学生社团]" || list[1] == "[学生机构]")
        {
            QAction * openGrp = new QAction(this);
            openGrp->setText("打开");
            tree_menu->addAction(openGrp);
        }
        else if(list[1] == "[部门]")
        {
            QAction * openDpment = new QAction(this);
            openDpment->setText("打开");
            tree_menu->addAction(openDpment);
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
    }
    tree_menu->exec(QCursor::pos());
}
