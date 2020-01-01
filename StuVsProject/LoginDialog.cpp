#include "LoginDialog.h"
#include "SqlQuery.h"

LoginDialog::LoginDialog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

LoginDialog::~LoginDialog()
{
}

void LoginDialog::on_LogInBtn_clicked()
{
    QString usr_id = ui.userLineEdit->text();
    QString pwd = ui.pwdLineEdit->text();
    QString type;
    //不用输密码直接进

    //emit openStudentWidget(usr_id);
    //return;
    //////////////////////////////////////

   
    if (ui.StuRadioButton->isChecked()) type = "学生";
    else if (ui.TeacherRadioButton->isChecked()) type = "教师";
    else if (ui.rootRadioButton->isChecked()) type = "root";


    else {
        MsgInterface::show_error("错误","未勾选类型");
        return;
    }
    if (SqlQuery::LoginQuery(usr_id, pwd, type))
    {
        if (type == "root") emit openRootWidget();
        else if (type == "教师") emit openTeacherWidget();
        else emit openStudentWidget(usr_id);
    }
    else {
        MsgInterface::show_error("警告", "用户名或密码错误");
        return;
    }
}

void LoginDialog::on_exitBtn_clicked()
{
    //reject();
    close();
}

void LoginDialog::on_registerBtn_clicked()
{
    emit openResDialog();
    this->hide();
}
