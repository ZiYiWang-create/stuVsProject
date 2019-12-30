#include "RegisterDialog.h"
#include "SqlQuery.h"

#include"msginterface.h"
RegisterDialog::RegisterDialog(QWidget* parent) :
    QWidget(parent)
{
    ui.setupUi(this);
}

RegisterDialog::~RegisterDialog()
{
}

void RegisterDialog::on_backBtn_clicked()
{
    emit backToLogin();
    this->close();
}

void RegisterDialog::on_sureBtn_clicked()
{
    QString type, table_name;
    if (ui.stuRadioButton->isChecked()) { type = "学生"; table_name = "student_info"; }
    else if (ui.teacherRadioButton->isChecked()) { type = "老师"; table_name = "teacher_info"; }
    else {
        MsgInterface::show_error("警告", "请勾选类型");
        return;
    }
    QString id = ui.idlineEdit->text();
    QString name = ui.namelineEdit->text();
    QString pwd1 = ui.pwd1lineEdit->text();
    QString pwd2 = ui.pwd2lineEdit->text();

    if (!SqlQuery::isInTable(id, table_name))
    {
        MsgInterface::show_error("警告", "学号/工号不存在");
        return;
    }

    if (pwd1 != pwd2)
    {
        MsgInterface::show_error("警告", "密码输入错误");
        return;
    }

    if (id == "" || name == "" || pwd1 == "")
    {
        MsgInterface::show_error("警告", "请输入全部信息");
        return;
    }
    if (SqlQuery::isInTable(id, name, table_name))
    {
        if (SqlQuery::upgradePwd(id, pwd1, table_name))
        {
            MsgInterface msg;
            msg.show_info("成功", "修改成功");
            ui.namelineEdit->clear();
            ui.idlineEdit->clear();
            ui.pwd1lineEdit->clear();
            ui.pwd2lineEdit->clear();
            return;
        }
        else {
            MsgInterface::show_error("失败", "信息有误");
            return;
        }
    }
    else {
        MsgInterface::show_error("修改失败", "用户不存在");
    }

}
