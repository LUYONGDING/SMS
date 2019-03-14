#include "registform.h"
#include "ui_registform.h"

registForm::registForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registForm)
{

    this->setWindowFlags(Qt::Widget | Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);   //设置为模态窗口



    ui->setupUi(this);
    ui->comboBox->addItem("教师");
    ui->comboBox->addItem("社团");
    ui->widget_group->hide();
    connect(ui->comboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),    //通过选择下拉框来选择注册用户类型
            [=](int index){if(index == 0)
        {
            ui->widget_group->hide();
            ui->widget_teacher->show();
        }
        if(index == 1)
        {
            ui->widget_teacher->hide();
            ui->widget_group->show();
        }});


}

registForm::~registForm()
{
    delete ui;
}
