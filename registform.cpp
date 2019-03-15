#include "registform.h"
#include "ui_registform.h"

registForm::registForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registForm)
{

    this->setWindowFlags(Qt::Widget | Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);   //设置为模态窗口

    ui->setupUi(this);

    this->db = new DBconnt();   //初始化数据库类
    this->us = new user();  //初始化用户类
    this->tch = new teacher();  //初始化教师类
    this->rx.setPattern(QString("^[A-Za-z0-9]+$")); //设置密码格式为数字与大小写字母
    //加入教师按钮组
    this->btnGroup.addButton(ui->radioButton_male,1);
    this->btnGroup.addButton(ui->radioButton_female,0);
    ui->comboBox->addItem("教师");
    ui->comboBox->addItem("社团");
    ui->widget_group->hide();
    connect(ui->comboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),    //通过选择下拉框来选择注册用户类型
            [=](int index){if(index == 0)
        {
            this->SetNULLGroupEdit();
            ui->widget_group->hide();
            ui->widget_teacher->show();
        }
        if(index == 1)
        {
            this->SetNULLTeacherEdit();
            ui->widget_teacher->hide();
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
    connect(ui->lineEdit_teacher_userPasswd2,&QLineEdit::editingFinished,[=](){
        if(ui->lineEdit_teacher_userPasswd2->text() != ui->lineEdit_teacher_userPasswd->text()) //密码检查
        {
            QMessageBox::warning(this,"警告","两次输入的密码不对，这样会可能会导致注册失败，请检查输入的密码！");
            return;
        }
    });
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
        this->us->setUserType(1);

        this->tch->setTeacherName(ui->lineEdit_teacherName->text());
        this->tch->setTeacherSex(btnGroup.checkedId());

        //插入数据库
        bool ret = false;
        this->db->openDB();
        this->db->query->prepare("insert into user (user_name,user_passwd,user_type) values(:username,:userpasswd,:usertype)");
        this->db->query->bindValue(":username",us->getUserName());
        this->db->query->bindValue(":userpasswd",us->getUserPasswd());
        this->db->query->bindValue(":usertype",us->getUserType());
        ret = this->db->query->exec();
        if(!ret)
        {
            QMessageBox::critical(this,"系统错误",this->db->query->lastError().text());
            return;
        }
        else
        {
            ret = false;
            this->db->openDB();
            this->db->query->prepare("select * from user where user_name = :username");
            this->db->query->bindValue(":username",us->getUserName());
            ret = db->query->exec();
            if(db->query->next())
            {
                this->us->setUserID(db->query->value("user_id").toInt());
                this->tch->setTeahcerUserID(us);
                ret = false;
                this->db->query->prepare("insert into teacher (teacher_user_id,teacher_name,teacher_sex) values(:userID,:name,:sex)");
                this->db->query->bindValue(":userID",tch->getTeacherUserID());
                this->db->query->bindValue(":name",tch->getTeacherName());
                this->db->query->bindValue(":sex",tch->getTeacherSex());
                ret = this->db->query->exec();
                if(!ret)
                {
                    QMessageBox::critical(this,"系统错误",this->db->query->lastError().text());
                    return;
                }
            }
            else
            {
                if(!ret)
                {
                    QMessageBox::critical(this,"系统错误",this->db->query->lastError().text());
                    return;
                }
            }
        }
        QMessageBox::critical(this,"注册成功",QString("注册成功！请牢记您的个人信息：%1").arg(this->us->getinfo()));
    }
    this->db->closeDB();
    if(ui->comboBox->currentText()=="社团")
    {
    }

}
