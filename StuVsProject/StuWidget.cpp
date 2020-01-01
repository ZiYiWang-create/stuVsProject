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
	header << "课程编号" << "课程名称" << "课程学分" << "平时成绩" << "实验成绩" << "卷面成绩" << "综合成绩" << "实得学分";
	ui.tableWidget->setColumnCount(header.count());
	ui.tableWidget->setHorizontalHeaderLabels(header);
	QSqlDatabase db = SqlQuery::createConnection();
	if (!db.open()) {
		MsgInterface::show_error("错误", "连接服务器错误");
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
	ui.show_label->setText("总学分: "+ QString::number(totalScore) + " 分");

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
		MsgInterface::show_error("错误", "连接服务器错误");
		return;
	}

	QSqlQuery query(db);
	QString str = QString("select name,sex,native,tel,college,major,class,dormitory from student_info "
		"where id=\"%1\";").arg(id);

	query.exec(str);
	if (query.next())
	{
		ui.nameLineEdit->setText(query.value(0).toString());
		if (query.value(1).toString() == "男")
			ui.manRadioBtn->clicked(1);
		else if (query.value(1).toString() == "女")
			ui.womanRadioBtn->clicked(1);
		else MsgInterface::show_error("错误", "性别出错");
		ui.nativelineEdit->setText(query.value(2).toString());
		ui.tellineEdit->setText(query.value(3).toString());
		ui.collegelineEdit->setText(query.value(4).toString());
		ui.majorlineEdit->setText(query.value(5).toString());
		ui.classlineEdit->setText(query.value(6).toString());
		ui.dormitorylineEdit->setText(query.value(7).toString());
	}
	else MsgInterface::show_error("错误", "未知错误");
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
	if (ui.manRadioBtn->isChecked()) sex = "男";
	else if (ui.womanRadioBtn->isChecked()) sex = "女";
	else MsgInterface::show_error("错误", "性别出错（测试）");


	if (SqlQuery::updateStuInfo(id, name, sex, native, tel, college, major, class_name, dormitory))MsgInterface::show_info("成功", "修改成功");
	else MsgInterface::show_error("修改失败", "修改失败");

}