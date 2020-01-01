#include "StuWidget.h"
#include "SqlQuery.h"
#include <qtablewidget.h>
StuWidget::StuWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.exitBtn, &QPushButton::clicked, [=]() {
		emit backToLogin();
		this->close();
		});
	
	connect(ui.ScoreSearchBtn, &QPushButton::clicked, [=]() {
		ui.stackedWidget->setCurrentWidget(ui.searchPage);
		searchPage_show();
		});
	connect(ui.modifyBtn, &QPushButton::clicked, [=]() {
		ui.stackedWidget->setCurrentWidget(ui.modifyPage);
		modifyPage_show();	
		});

}

StuWidget::~StuWidget()
{
}

void StuWidget::searchPage_show()
{
	QStringList header;
	header << "�γ̱��" << "�γ�����" << "�γ�ѧ��" << "ƽʱ�ɼ�" << "ʵ��ɼ�" << "����ɼ�" << "�ۺϳɼ�" << "ʵ��ѧ��";
	ui.tableWidget->setColumnCount(header.count());
	ui.tableWidget->setHorizontalHeaderLabels(header);
	QSqlDatabase db = SqlQuery::createConnection();
	if (!db.open()) {
		MsgInterface::show_error("����", "���ӷ���������");
		return;
	}

	QSqlQuery query(db);
	QString str = QString("select courseId,courseName,score,usualPerformance,experiment,paperScore,actualGrade,actualScore "
		"from scores where studentId=\"%1\";").arg(id);
	query.exec(str);
	int count = query.size();
	ui.tableWidget->setRowCount(count);
	double totalScore = 0;
	if (query.next())
	{
		for (int i = 0; i < count; i++)
		{
			ui.tableWidget->setItem(i, 0, new QTableWidgetItem(query.value(0).toString()));
			ui.tableWidget->setItem(i, 1, new QTableWidgetItem(query.value(1).toString()));
			ui.tableWidget->setItem(i, 2, new QTableWidgetItem(query.value(2).toString()));
			ui.tableWidget->setItem(i, 3, new QTableWidgetItem(query.value(3).toString()));
			ui.tableWidget->setItem(i, 4, new QTableWidgetItem(query.value(4).toString()));
			ui.tableWidget->setItem(i, 5, new QTableWidgetItem(query.value(5).toString()));
			ui.tableWidget->setItem(i, 6, new QTableWidgetItem(query.value(6).toString()));
			ui.tableWidget->setItem(i, 7, new QTableWidgetItem(query.value(7).toString()));
			totalScore += query.value(7).toDouble();
			query.next();
		}
	}
	ui.tableWidget->show();
	ui.show_label->setText("��ѧ��: "+ QString::number(totalScore) + " ��");

}

void StuWidget::setId(QString id)
{
	this->id = id;
}

QString StuWidget::getId()
{
	return this->id;
}


void StuWidget::modifyPage_show()
{
	QSqlDatabase db = SqlQuery::createConnection();
	if (!db.open()) {
		MsgInterface::show_error("����", "���ӷ���������");
		return;
	}

	QSqlQuery query(db);
	QString str = QString("select name,sex,native,tel,college,major,class,dormitory from student_info "
		"where id=\"%1\";").arg(id);

	query.exec(str);
	if (query.next())
	{
		ui.nameLineEdit->setText(query.value(0).toString());
		if (query.value(1).toString() == "��")
			ui.manRadioBtn->clicked(1);
		else if (query.value(1).toString() == "Ů")
			ui.womanRadioBtn->clicked(1);
		else MsgInterface::show_error("����", "�Ա����");
		ui.nativelineEdit->setText(query.value(2).toString());
		ui.tellineEdit->setText(query.value(3).toString());
		ui.collegelineEdit->setText(query.value(4).toString());
		ui.majorlineEdit->setText(query.value(5).toString());
		ui.classlineEdit->setText(query.value(6).toString());
		ui.dormitorylineEdit->setText(query.value(7).toString());
	}
	else MsgInterface::show_error("����", "δ֪����");
}

void StuWidget::on_sureBtn_clicked()
{
	QString name = ui.nameLineEdit->text();
	QString native = ui.nativelineEdit->text();
	QString tel = ui.tellineEdit->text();
	QString college = ui.collegelineEdit->text();
	QString major = ui.majorlineEdit->text();
	QString class_name = ui.classlineEdit->text();
	QString dormitory = ui.dormitorylineEdit->text();
	
	QString sex;
	if (ui.manRadioBtn->isChecked()) sex = "��";
	else if (ui.womanRadioBtn->isChecked()) sex = "Ů";
	else MsgInterface::show_error("����", "�Ա�������ԣ�");


	if (SqlQuery::updateStuInfo(id, name, sex, native, tel, college, major, class_name, dormitory))MsgInterface::show_info("�ɹ�", "�޸ĳɹ�");
	else MsgInterface::show_error("�޸�ʧ��", "�޸�ʧ��");

}