#include "registform.h"
#include "ui_registform.h"

registForm::registForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registForm)
{

    this->setWindowFlags(Qt::Widget | Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);   //设置为模态窗口

    this->db = new DBconnt();   //初始化数据库类
    this->us = new user();  //初始化用户类
    this->tch = new teacher();  //初始化教师类
    ui->setupUi(this);
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
    connect(ui->lineEdit_teacher_userPasswd2,&QLineEdit::editingFinished,[=](){
        if(ui->lineEdit_teacher_userPasswd2->text() != ui->lineEdit_teacher_userPasswd->text()) //密码检查
        {
            QMessageBox::warning(this,"警告","两次输入的密码不对，这样会可能会导致注册失败，请检查输入的密码");
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
void registForm::userRegist()
{
    if(ui->comboBox->currentText()=="教师")
    {
        if(ui->lineEdit_teacher_userPasswd2->text() != ui->lineEdit_teacher_userPasswd->text()) //再次进行密码检查
        {
            QMessageBox::critical(this,"错误","两次输入的密码不一致，无法注册");
            return;
        }
        if(ui->lineEdit_teacher_userPasswd->text() == "")
        {
            QMessageBox::critical(this,"错误","密码不能为空");
            return;
        }
        if(ui->lineEdit_teacher_userName->text() == "")
        {
            QMessageBox::critical(this,"错误","用户名不能为空");
            return;
        }
        if(ui->label_teacherName->text() == "")
        {
            QMessageBox::critical(this,"错误","姓名不能为空");
            return;
        }
        if(!ui->radioButton_male->isChecked() && !ui->radioButton_female->isChecked())
        {
            QMessageBox::critical(this,"错误","性别不能为空");
            return;
        }
//        if(ui->lineEdit_teacher_userPasswd->text() == ui->lineEdit_teacher_userPasswd2->text())
//        {
//            us->setUserName(ui->lineEdit_teacher_userName->text());
//        }
//        else
//        {
//            QMessageBox::critical(this,"密码错误","两次输入的密码不正确请确认");
//        }
//        this->db->query
    }
    if(ui->comboBox->currentText()=="社团")
    {
    }
}
