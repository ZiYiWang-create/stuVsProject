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
    if (ui.stuRadioButton->isChecked()) { type = "ѧ��"; table_name = "student_info"; }
    else if (ui.teacherRadioButton->isChecked()) { type = "��ʦ"; table_name = "teacher_info"; }
    else {
        MsgInterface::show_error("����", "�빴ѡ����");
        return;
    }
    QString id = ui.idlineEdit->text();
    QString name = ui.namelineEdit->text();
    QString pwd1 = ui.pwd1lineEdit->text();
    QString pwd2 = ui.pwd2lineEdit->text();

    if (!SqlQuery::isInTable(id, table_name))
    {
        MsgInterface::show_error("����", "ѧ��/���Ų�����");
        return;
    }

    if (pwd1 != pwd2)
    {
        MsgInterface::show_error("����", "�����������");
        return;
    }

    if (id == "" || name == "" || pwd1 == "")
    {
        MsgInterface::show_error("����", "������ȫ����Ϣ");
        return;
    }
    if (SqlQuery::isInTable(id, name, table_name))
    {
        if (SqlQuery::upgradePwd(id, pwd1, table_name))
        {
            MsgInterface msg;
            msg.show_info("�ɹ�", "�޸ĳɹ�");
            ui.namelineEdit->clear();
            ui.idlineEdit->clear();
            ui.pwd1lineEdit->clear();
            ui.pwd2lineEdit->clear();
            return;
        }
        else {
            MsgInterface::show_error("ʧ��", "��Ϣ����");
            return;
        }
    }
    else {
        MsgInterface::show_error("�޸�ʧ��", "�û�������");
    }

}
