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
    //����������ֱ�ӽ�

    //emit openStudentWidget(usr_id);
    //return;
    //////////////////////////////////////

   
    if (ui.StuRadioButton->isChecked()) type = "ѧ��";
    else if (ui.TeacherRadioButton->isChecked()) type = "��ʦ";
    else if (ui.rootRadioButton->isChecked()) type = "root";


    else {
        MsgInterface::show_error("����","δ��ѡ����");
        return;
    }
    if (SqlQuery::LoginQuery(usr_id, pwd, type))
    {
        if (type == "root") emit openRootWidget();
        else if (type == "��ʦ") emit openTeacherWidget();
        else emit openStudentWidget(usr_id);
    }
    else {
        MsgInterface::show_error("����", "�û������������");
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
