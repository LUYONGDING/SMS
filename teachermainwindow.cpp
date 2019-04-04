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

    this->setWindowIcon(QIcon(":/mainWin/Icon/guishen_0131ev05b08mg01.png"));
    QWidget * tempWidget = new QWidget(this);
    ui->dockWidget_left->setTitleBarWidget(tempWidget);
    this->setMarginSpacing();
    ui->treeView_2->setContextMenuPolicy(Qt::CustomContextMenu);
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
    this->ui->widget->layout()->setMargin(0);
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
    return;
}
void TeacherMainWindow::setGroupModel()
{
    bool ret = 0;
    QStandardItemModel * model = new QStandardItemModel(ui->treeView_2);
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
                    QStandardItem * group_dpment = new QStandardItem(this->dpment->getDepartmentName());
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
void TeacherMainWindow::CustomContextMenu(const QPoint &)
{
    QMenu * tree_menu = new QMenu(this);
    tree_menu->addAction("刷新",this,&TeacherMainWindow::setGroupModel);
    tree_menu->exec(QCursor::pos());

}
