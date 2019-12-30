#include "rootInsertStu.h"
#include"utils.h"
#include "MsgInterface.h"
#include "SqlQuery.h"
rootInsertStu::rootInsertStu(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(on_sureBtn_clicked()));
}

rootInsertStu::~rootInsertStu()
{
}

void rootInsertStu::on_sureBtn_clicked()
{
	QString id = ui.idlineEdit->text();
	if (!Utils::checkId(id)) {MsgInterface::show_error("����", "ѧ�Ÿ�ʽ�������"); return;}
	QString name = ui.namelineEdit->text();
	QString sex;
	if (ui.womanRadioBtn->isChecked()) sex = "Ů";
	else if (ui.manRadiBtn->isChecked()) sex = "��";
	else { MsgInterface::show_error("����", "��ѡ���Ա�"); return; }
	QString flag = ui.label->text();  /*/*/
	QString navite = ui.nativelineEdit->text();
	QString tel = ui.tellineEdit->text();
	if (!Utils::checkId(tel)) { MsgInterface::show_error("����", "�绰�����ʽ����"); return; }
	QString college = ui.collegelineEdit->text();
	QString major = ui.majorlineEdit->text();
	QString class_name = ui.classlineEdit->text();
	QString dormitory = ui.dormitoryLineEdit->text();
	if (SqlQuery::addStudent(id,name,sex,navite,tel,college,major,class_name,dormitory))
	{
		ui.idlineEdit->clear();
		ui.namelineEdit->clear();
		ui.nativelineEdit->clear();
		ui.classlineEdit->clear();
		ui.tellineEdit->clear();
		ui.collegelineEdit->clear();
		ui.majorlineEdit->clear();
		ui.dormitoryLineEdit->clear();
		MsgInterface::show_info("�ɹ�", "��ӳɹ�");
		return;
	}
	else MsgInterface::show_error("ʧ��", "���ʧ��");
	return;
}
