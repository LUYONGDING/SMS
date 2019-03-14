#ifndef REGISTFORM_H
#define REGISTFORM_H

#include <QWidget>
#include <QComboBox>

namespace Ui {
class registForm;
}

class registForm : public QWidget
{
    Q_OBJECT

public:
    explicit registForm(QWidget *parent = 0);
    ~registForm();

private:
    Ui::registForm *ui;
};

#endif // REGISTFORM_H
