#include "registform.h"
#include "ui_registform.h"

registForm::registForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registForm)
{

    this->setWindowFlags(Qt::Widget | Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);   //设置为模态窗口
    ui->setupUi(this);
    sltTeacher = NULL;
    this->setWindowTitle("用户注册");   //设置窗口标题
    this->setWindowIcon(QIcon(":/mainWin/Icon/guishen_0131ev05b08mg01.png"));   //设置窗口图标


    this->db = new DBconnt();   //初始化数据库类
    this->us = new user();  //初始化用户类
    this->tch = new teacher();  //初始化教师类
    this->grp = new group();
    this->rx.setPattern(QString("^[A-Za-z0-9]+$")); //设置密码格式为数字与大小写字母
    //加入教师按钮组
    this->btnGroup.addButton(ui->radioButton_male,1);
    this->btnGroup.addButton(ui->radioButton_female,0);
    //加入社团按钮组
    this->btnGroup2.addButton(ui->radioButton_agency,0);
    this->btnGroup2.addButton(ui->radioButton_group,1);
    ui->comboBox->addItem("教师");
    ui->comboBox->addItem("社团");
    ui->widget_group->hide();
    connect(ui->comboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),    //通过选择下拉框来选择注册用户类型
            [=](int index){if(index == 0)
        {
            this->SetNULLGroupEdit();
            ui->widget_group->close();
            ui->widget_teacher->show();
        }
        if(index == 1)
        {
            this->SetNULLTeacherEdit();
            ui->widget_teacher->close();
            ui->widget_group->show();
        }});
    connect(ui->pushButton_cancel,&QPushButton::clicked,[=](){  //取消按钮关闭窗口
        this->close();
    });
    connect(ui->pushButton_regist,&QPushButton::clicked,this,&registForm::userRegist);  //连接注册按钮点击信号与注册槽函数
    connect(ui->lineEdit_teacher_userPasswd,&QLineEdit::editingFinished,[=](){
        if(!rx.exactMatch(ui->lineEdit_teacher_userPasswd->text())
                && !ui->lineEdit_teacher_userPasswd->text().isEmpty())  //检查密码是否符合格式
        {
            QMessageBox::warning(this,"警告","密码只能是数字或者大小写字母！");
            return;
        }
    });
    connect(ui->lineEdit_group_user_passwd,&QLineEdit::editingFinished,[=](){
        if(!rx.exactMatch(ui->lineEdit_group_user_passwd->text())
                && !ui->lineEdit_group_user_passwd->text().isEmpty())
        {
            QMessageBox::warning(this,"警告","密码只能是数字或者大小写字母！");
            return;
        }
    });
    connect(ui->lineEdit_teacher_userPasswd2,&QLineEdit::editingFinished,[=](){
        if(ui->lineEdit_teacher_userPasswd2->text() != ui->lineEdit_teacher_userPasswd->text()) //密码检查
        {
            QMessageBox::warning(this,"警告","两次输入的密码不对，这样会可能会导致注册失败，请检查输入的密码！");
            return;
        }
    });
    connect(ui->lineEdit_group_userPasswd2,&QLineEdit::editingFinished,[=](){
        if(ui->lineEdit_group_userPasswd2->text() != ui->lineEdit_group_user_passwd->text())
        {
            QMessageBox::warning(this,"警告","两次输入的密码不对，这样会可能会导致注册失败，请检查输入的密码！");
            return;
        }
    });
    connect(ui->toolButton_select_teacher,&QToolButton::clicked,[=](){
        sltTeacher = new selectTeacherForm();
        connect(this->sltTeacher,&selectTeacherForm::selectedID,[=](QString & ID){  //连接返回教师ID的信号与设置教师ID的槽
            ui->lineEdit_groupTeacher->setText(ID); //设置教师ID输入栏
            if(sltTeacher != NULL)
            {
                sltTeacher->close();    //关闭教师选择窗口
            }
        });
        sltTeacher->show();
    });
    //    connect(this->sltTeacher,&selectTeacherForm::selectedID,[=](QString ID){
    //        qDebug()<<ID;
    //        //ui->lineEdit_groupTeacher->setText(ID);
    //    });

}

registForm::~registForm()
{
    if(NULL != db)
    {
        delete db;
        db = NULL;
    }
    if(NULL != us)
    {
        delete us;
    }
    if(NULL != tch)
    {
        delete tch;
    }
    delete ui;
}
void registForm::paintEvent(QPaintEvent *event) //使用绘图事件设置背景
{
    QPainter painter(this);
    painter.drawPixmap(0,0,610,610,QPixmap(":/mainWin/background/guishen_0039ev05a07.jpg"));
}
void registForm::SetNULLTeacherEdit()
{
    ui->lineEdit_teacherName->setText("");
    ui->lineEdit_teacher_userName->setText("");
    ui->lineEdit_teacher_userPasswd->setText("");
    ui->lineEdit_teacher_userPasswd2->setText("");
    ui->radioButton_male->setChecked(false);
}
void registForm::SetNULLGroupEdit()
{
    ui->lineEdit_groupName->setText("");
    ui->lineEdit_groupTeacher->setText("");
    ui->lineEdit_group_userName->setText("");
    ui->lineEdit_group_user_passwd->setText("");
    ui->lineEdit_group_userPasswd2->setText("");
    ui->radioButton_agency->setChecked(false);
}
bool registForm::teacherRegistCheck()
{
    if(!rx.exactMatch(ui->lineEdit_teacher_userPasswd->text())
            && !ui->lineEdit_teacher_userPasswd->text().isEmpty())  //再次进行密码格式检查
    {
        QMessageBox::critical(this,"错误","密码只能是数字或者大小写字母！");
        return false;
    }
    if(ui->lineEdit_teacher_userPasswd2->text() != ui->lineEdit_teacher_userPasswd->text()) //再次进行密码检查
    {
        QMessageBox::critical(this,"错误","两次输入的密码不一致，无法注册");
        return false;
    }
    if(ui->lineEdit_teacher_userPasswd->text().isEmpty())
    {
        QMessageBox::critical(this,"错误","密码不能为空");
        return false;
    }
    if(ui->lineEdit_teacher_userName->text().isEmpty())
    {
        QMessageBox::critical(this,"错误","用户名不能为空");
        return false;
    }
    if(ui->label_teacherName->text().isEmpty())
    {
        QMessageBox::critical(this,"错误","姓名不能为空");
        return false;
    }
    if(!ui->radioButton_male->isChecked() && !ui->radioButton_female->isChecked())
    {
        QMessageBox::critical(this,"错误","性别不能为空");
        return false;
    }
    return true;
}
bool registForm::groupRegistCheck()
{
    if(!rx.exactMatch(ui->lineEdit_group_user_passwd->text())
            && !ui->lineEdit_group_user_passwd->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","密码只能是数字或者大小写字母！");
        return false;
    }
    if(ui->lineEdit_group_userPasswd2->text() != ui->lineEdit_group_user_passwd->text())
    {
        QMessageBox::warning(this,"警告","两次输入的密码不对，这样会可能会导致注册失败，请检查输入的密码！");
        return false;
    }
    if(ui->lineEdit_groupName->text().isEmpty())
    {
        QMessageBox::critical(this,"错误","社团名不能为空");
        return false;
    }
    if(ui->lineEdit_groupTeacher->text().isEmpty())
    {
        QMessageBox::critical(this,"错误","社团指导老师不能为空");
        return false;
    }
    if(ui->lineEdit_group_userName->text().isEmpty())
    {
        QMessageBox::critical(this,"错误","用户名不能为空");
        return false;
    }
    if(ui->lineEdit_group_user_passwd->text().isEmpty())
    {
        QMessageBox::critical(this,"错误","用户密码不能为空");
        return false;
    }
    return true;
}
void registForm::userRegist()
{
    if(ui->comboBox->currentText()=="教师")
    {
        bool check = teacherRegistCheck();  //进行注册前检查
        if(!check)  //检查失败则返回
        {
            return;
        }
        //获取值
        this->us->setUserName(ui->lineEdit_teacher_userName->text());
        this->us->setUserPasswd(ui->lineEdit_teacher_userPasswd->text());
        this->us->setUserType(1);   //1代表教师

        this->tch->setTeacherName(ui->lineEdit_teacherName->text());
        this->tch->setTeacherSex(btnGroup.checkedId());

        //插入数据库
        bool ret = false;
        this->db->openDB();
        this->db->db->transaction();
        this->db->query->prepare("insert into user (user_name,user_passwd,user_type) values(:username,:userpasswd,:usertype)");
        this->db->query->bindValue(":username",us->getUserName());
        this->db->query->bindValue(":userpasswd",us->getUserPasswd());
        this->db->query->bindValue(":usertype",us->getUserType());
        ret = this->db->query->exec();
        if(!ret)
        {
            QMessageBox::critical(this,"系统错误",this->db->query->lastError().text());
            this->db->db->rollback();
            this->db->closeDB();
            return;
        }
        else
        {
            ret = false;
            this->db->openDB();
            this->db->query->prepare("select * from user where user_name = :username"); //查询出用户ID
            this->db->query->bindValue(":username",us->getUserName());
            ret = db->query->exec();
            if(db->query->next())
            {
                this->us->setUserID(db->query->value("user_id").toInt());   //设置用户ID
                this->tch->setTeahcerUserID(us);    //设置teacher类中的用户ID
                //插入用户类
                ret = false;
                this->db->query->prepare("insert into teacher (teacher_user_id,teacher_name,teacher_sex) values (:userID,:name,:sex)");
                this->db->query->bindValue(":userID",tch->getTeacherUserID());
                this->db->query->bindValue(":name",tch->getTeacherName());
                this->db->query->bindValue(":sex",tch->getTeacherSex());
                ret = this->db->query->exec();
                if(!ret)
                {
                    QMessageBox::critical(this,"系统错误",this->db->query->lastError().text());
                    this->db->db->rollback();
                    this->db->closeDB();
                    return;
                }
            }
            else
            {
                if(!ret)
                {
                    QMessageBox::critical(this,"系统错误",this->db->query->lastError().text());
                    this->db->db->rollback();
                    this->db->closeDB();
                    return;
                }
            }
        }
        this->db->db->commit();
        QMessageBox::information(this,"注册成功",QString("注册成功！请牢记您的个人信息：%1").arg(this->us->getinfo()));
        this->SetNULLTeacherEdit();
        this->db->closeDB();
    }
    if(ui->comboBox->currentText()=="社团")
    {
        bool check =groupRegistCheck();
        if(!check)
        {
            return;
        }
        //获取值
        this->us->setUserName(ui->lineEdit_group_userName->text());
        this->us->setUserPasswd(ui->lineEdit_group_user_passwd->text());
        this->us->setUserType(2);

        this->grp->setGroupName(ui->lineEdit_groupName->text());
        this->grp->setGroupType(btnGroup2.checkedId());
        //从教师表中查询是否存在该教师
        bool ret = 0;
        this->db->openDB();
        this->db->db->transaction();
        this->db->query->prepare("SELECT * FROM TEACHER where teacher_id = :value");
        this->db->query->bindValue(":value",ui->lineEdit_groupTeacher->text().toInt());
        ret = this->db->query->exec();
        if(!ret)    //如果执行不成功则事务回滚
        {
            QMessageBox::critical(this,"系统错误",this->db->query->lastError().text());
            this->db->db->rollback();
            this->db->closeDB();
            return;
        }
        else
        {
            if(this->db->query->next()) //如果存在该行数据
            {
                this->tch->setTeacherID(this->db->query->value("teacher_id").toInt()); //设置教师ID
                this->grp->setGroupTeacherID(this->tch);    //设置社团指导老师
                //                qDebug()<<this->grp->getinfo();
                //为社团注册一个用户插入用户表
                this->db->query->prepare("insert into user (user_name,user_passwd,user_type) values(:username,:userpasswd,:usertype)");
                this->db->query->bindValue(":username",us->getUserName());
                this->db->query->bindValue(":userpasswd",us->getUserPasswd());
                this->db->query->bindValue(":usertype",us->getUserType());
                ret = this->db->query->exec();
                if(!ret)
                {
                    QMessageBox::critical(this,"系统错误",this->db->query->lastError().text());
                    this->db->db->rollback();
                    this->db->closeDB();
                    return;
                }
                else
                {
                    //获得用户表中社团用户的用户ID
                    this->db->query->prepare("SELECT * FROM user WHERE user_name = :value");
                    this->db->query->bindValue(":value",this->us->getUserName());
                    ret = this->db->query->exec();
                    if(!ret)
                    {
                        QMessageBox::critical(this,"系统错误",this->db->query->lastError().text());
                        this->db->db->rollback();
                        this->db->closeDB();
                        return;
                    }
                    else
                    {
                        if(this->db->query->next())    //如果存在数据
                        {
                            this->us->setUserID(this->db->query->value("user_id").toInt()); //设置用户ID
                            //将社团插入社团表
                            this->grp->setGroupID(this->us);
                            qDebug()<<this->grp->getinfo();
                            this->db->query->prepare("INSERT INTO `group_manager_system`.`group` (`group_user_id`, `group_name`, `group_teacher_id`, `group_type`) VALUES (:userID, :name, :teacherID, :type);");
                            this->db->query->bindValue(":userID",this->grp->getGroupID());
                            this->db->query->bindValue(":name",this->grp->getGroupName());
                            this->db->query->bindValue(":teacherID",this->grp->getGroupTeacherID());
                            this->db->query->bindValue(":type",this->grp->getGroupType());
                            ret = this->db->query->exec();
                            if(!ret)
                            {
                                QMessageBox::critical(this,"系统错误",this->db->query->lastError().text());
                                this->db->db->rollback();
                                this->db->closeDB();
                                return;
                            }
                        }
                        else
                        {
                            QMessageBox::critical(this,"系统错误","获取userID失败");
                        }
                    }

                }
            }
            else
            {
                QMessageBox::warning(this,"注册失败",QString("不存在ID为%1的教师").arg(ui->lineEdit_groupTeacher->text().toInt()));
                this->db->closeDB();
                return;
            }
        }
        this->db->db->commit();
        QMessageBox::information(this,"注册成功",QString("注册成功，请牢记您的个人信息!用户ID：%1,用户名：%2,用户密码：%3").arg(us->getUserID()).arg(us->getUserName()).arg(us->getUserPasswd()));
        this->SetNULLGroupEdit();
        this->db->closeDB();
    }
}
void registForm::closeEvent(QCloseEvent *event) //窗口关闭事件
{
    if(sltTeacher!=NULL)  //如果选择教师窗口存在则一并关闭
    {
        sltTeacher->close();
        delete this->sltTeacher;
    }
    event->accept();
}
