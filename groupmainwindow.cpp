#include "groupmainwindow.h"
#include "ui_groupmainwindow.h"

GroupMainWindow::GroupMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GroupMainWindow)
{
    ui->setupUi(this);
    this->db = new DBconnt();
    this->us = new user();
    this->grp = new group();
    this->dpment = new department();
    this->mainTableView = new QSqlQueryModel(this);
    this->setWindowIcon(QIcon(":/mainWin/Icon/guishen_0131ev05b08mg01.png"));
    setMarginSpacing();
    QWidget * tempWidget = new QWidget(this);
    ui->dockWidget_left->setTitleBarWidget(tempWidget);
    connect(this->ui->treeView,&QTreeView::doubleClicked,this,&GroupMainWindow::openTableViewByDC);
    connect(this->ui->actionabout,&QAction::triggered,[=](){
        QString about = "Based on Qt 5.8.0(MSVC 2015 , 32 bit)\n\nBuilt on Mon Mar 11 21:31:43 2019 +0800\n\nDemo ver 1.0\n\nCopyright © 2019 luyongding. All Rights Reserved.\n\nThis progarm only used by personal graduation project.If you want to use it for other purposes,please ask the auther first.\nlyd2233970479@163.com";
        QMessageBox::about(this,"关于",about);
    });
}

GroupMainWindow::~GroupMainWindow()
{
    delete this->db;
    delete this->us;
    delete this->grp;
    delete this->dpment;
    delete ui;
}
void GroupMainWindow::getUserInfo(user * us)
{
    this->us = us;
//    qDebug()<<this->us->getinfo();
    this->setWindowTitle(QString("%1 [学生社团/学生机构] - 学生社团管理系统").arg(this->us->getUserName()));
    setGroupModel();
    connect(ui->treeView,&QTreeView::customContextMenuRequested,this,&GroupMainWindow::CustomContextMenu);
    return;
}

void GroupMainWindow::CustomContextMenu(const QPoint &pos)
{
    QModelIndex index = ui->treeView->indexAt(pos);
    QMenu * tree_menu = new QMenu(this->ui->treeView);
    QStandardItem * tmpItem = model->itemFromIndex(index);
    QAction * reflash = new QAction(this);
    reflash->setText("刷新");
    connect(reflash,&QAction::triggered,this,&GroupMainWindow::setGroupModel);
    if(index.isValid())
    {

        tree_menu->addAction(reflash);
        QStringList list = tmpItem->text().split("-");
        if("[部门]"==list[1])
        {
            QAction * openDpment = new QAction(this);
            openDpment->setText("打开");
//            tree_menu->addAction("打开",this,[=](){
//                emit sendOpenInfo(list);
//            });
//            connect(this,&GroupMainWindow::sendOpenInfo,this,&GroupMainWindow::opendpmentTableView);
            tree_menu->addAction(openDpment);
            connect(openDpment,&QAction::triggered,[=](){
                connect(this,&GroupMainWindow::sendOpenInfo,this,&GroupMainWindow::opendpmentTableView);
                emit sendOpenInfo(list);
            });
        }
        else
        {
            tree_menu->addAction("新增部门");
        }
    }
    else
    {
        tree_menu->addAction(reflash);
    }
    tree_menu->exec(QCursor::pos());
}

void GroupMainWindow::opendpmentTableView(QStringList list)
{
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
    this->db->query->prepare("SELECT * FROM `student` WHERE `student_id` IN (SELECT `studentdependence_student_id` FROM `studentdependence` WHERE `studentdependence_department_id` = :ID)");
    this->db->query->bindValue(":ID",this->dpment->getDepartmentID());
    ret = this->db->query->exec();
    if(!ret)
    {
        QMessageBox::critical(NULL,"错误",this->db->query->lastError().text());
        this->db->closeDB();
        return;
    }
    if(this->db->query->next())
    {
        this->mainTableView->setQuery(*(this->db->query));
        this->mainTableView->setHeaderData(0,Qt::Horizontal,"学生ID");
        this->mainTableView->setHeaderData(1,Qt::Horizontal,"学生性别");
        this->mainTableView->setHeaderData(2,Qt::Horizontal,"学生姓名");
        ui->tableView->setModel(this->mainTableView);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //设置表对齐
        ui->tableView->show();
    }
    else
    {
        QMessageBox::information(NULL,"信息","没有成员");
        this->db->closeDB();
        return;
    }
    this->db->closeDB();
    return;
}

void GroupMainWindow::openTableViewByDC(const QModelIndex &index)
{
    QStandardItem * item = model->itemFromIndex(index);
    QStringList list = item->text().split("-");
    if(list[1]!="[部门]")
        return;
    opendpmentTableView(list);
}
void GroupMainWindow::paintEvent(QPaintEvent *event)
{
    painter = new QPainter(this);
    painter->drawPixmap(0,0,this->width(),this->height(),QPixmap(":/mainWin/background/guishen_0039ev05a07.jpg"));
}
void GroupMainWindow::setMarginSpacing()
{
    this->layout()->setSpacing(0);
    this->layout()->setMargin(0);
//    this->ui->dockWidgetContents->layout()->setSpacing(0);
    this->ui->dockWidgetContents->layout()->setMargin(1);
    this->ui->centralwidget->layout()->setMargin(0);
    this->ui->centralwidget->layout()->setSpacing(0);
    this->ui->widget->layout()->setMargin(0);
    this->ui->widget->layout()->setSpacing(0);
}

void GroupMainWindow::setGroupModel()
{
    bool ret = 0;
    this->model = new QStandardItemModel(ui->tableView);
    ui->treeView->setEditTriggers(0);
    ui->treeView->header()->hide();
    this->db->openDB();
    this->db->query->prepare("SELECT * FROM `group` WHERE `group_user_id` = :ID");
    this->db->query->bindValue(":ID",this->us->getUserID());
    ret = this->db->query->exec();
    if(!ret)
    {
        QMessageBox::critical(NULL,"错误",this->db->query->lastError().text());
        this->db->closeDB();
        return;
    }
    if(this->db->query->next())
    {
        this->grp->setGroupID(this->us->getUserID());
        this->grp->setGroupName(this->db->query->value("group_name").toString());
        this->grp->setGroupTeacherID(this->db->query->value("group_teacher_id").toInt());
        this->grp->setGroupType(this->db->query->value("group_type").toInt());
    }
    else
    {
        QMessageBox::critical(NULL,"错误","没有查询到信息");
        this->db->closeDB();
        return;
    }
    QStandardItem * item = new QStandardItem(QString("%1-[我的社团]").arg(this->grp->getGroupName()));
    this->db->query->prepare("SELECT * FROM `department` WHERE `department_group_id` = :ID");
    this->db->query->bindValue(":ID",this->grp->getGroupID());
    ret = this->db->query->exec();
    if(!ret)
    {
        QMessageBox::critical(NULL,"错误",this->db->query->lastError().text());
        this->db->closeDB();
        return;
    }
    while(this->db->query->next())
    {
        this->dpment->setDepartmentGroupID(this->db->query->value("department_group_id").toInt());
        this->dpment->setDepartmentID(this->db->query->value("department_id").toInt());
        this->dpment->setDepartmentName(this->db->query->value("department_name").toString());
        this->dpment->setDepartmentIntroduction(this->db->query->value("department_introdution").toString());
        QStandardItem * my_dpment = new QStandardItem(QString("%1-[部门]").arg(this->dpment->getDepartmentName()));
        item->appendRow(my_dpment);
    }
    this->model->appendRow(item);
    ui->treeView->setModel(this->model);
    this->db->closeDB();
}
