#include "TeacherWidget.h"
#include "SqlQuery.h"
#include "QSqlQuery"
TeacherWidget::TeacherWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.exitBtn, &QPushButton::clicked, [=]() {
		emit backToLogin();
		this->close();
		});
	ui.stackedWidget->setCurrentWidget(ui.blankpage);

	//录入信息界面
	connect(ui.enterBtn, &QPushButton::clicked, [=]() {
		ui.stackedWidget->setCurrentWidget(ui.enterPage);
		show_enter_page();
		ui.enterBtn->setDown(true);
		ui.modifyBtn->setDown(false);
		ui.infoSearchBtn->setDown(false);
		ui.scoreSearchBtn->setDown(false);
		ui.allInfoBtn->setDown(false);
		});	

	// 修改信息界面
	connect(ui.modifyBtn, &QPushButton::clicked, [=]() {
		ui.stackedWidget->setCurrentWidget(ui.modifyPage);
		ui.enterBtn->setDown(false);
		ui.modifyBtn->setDown(true);
		ui.infoSearchBtn->setDown(false);
		ui.scoreSearchBtn->setDown(false);
		ui.allInfoBtn->setDown(false);
		});

	//基本信息查询界面
	connect(ui.infoSearchBtn, &QPushButton::clicked, [=]() {
		ui.stackedWidget->setCurrentWidget(ui.infoSearchPage);
		ui.enterBtn->setDown(false);
		ui.modifyBtn->setDown(false);
		ui.infoSearchBtn->setDown(true);
		ui.scoreSearchBtn->setDown(false);
		ui.allInfoBtn->setDown(false);
		});

	//分数查询界面
	connect(ui.scoreSearchBtn, &QPushButton::clicked, [=]() {
		ui.stackedWidget->setCurrentWidget(ui.scoreSearchPage);
		ui.enterBtn->setDown(false);
		ui.modifyBtn->setDown(false);
		ui.infoSearchBtn->setDown(false);
		ui.scoreSearchBtn->setDown(true);
		ui.allInfoBtn->setDown(false);
		});
	//所有信息查询界面
	connect(ui.allInfoBtn, &QPushButton::clicked, [=]() {
		ui.stackedWidget->setCurrentWidget(ui.allInfoPage);
		ui.enterBtn->setDown(false);
		ui.modifyBtn->setDown(false);
		ui.infoSearchBtn->setDown(false);
		ui.scoreSearchBtn->setDown(false);
		ui.allInfoBtn->setDown(true);
		this->on_allInfoBtn_clicekd();
		});
	connect(ui.comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(value_change(QString)));

}

TeacherWidget::~TeacherWidget()
{
}

//录入界面
void TeacherWidget::show_enter_page()
{
	ui.enterBtn->setDown(true);
	ui.modifyBtn->setDown(false);
	ui.infoSearchBtn->setDown(false);
	ui.scoreSearchBtn->setDown(false);
	ui.allInfoBtn->setDown(false);
	QSqlDatabase db = SqlQuery::createConnection();
	if (!db.open()) {
		QMessageBox::warning(NULL, "错误", "连接服务器错误");
		return;
	}
	QStringList header;
	header << "学号" << "课程编号" << "课程名称" << "平时分数" << "实验分数" << "卷面成绩" << "课程学分";
	ui.enterTableWidget->setColumnCount(header.count());
	ui.enterTableWidget->setRowCount(1);
	ui.enterTableWidget->setHorizontalHeaderLabels(header);
	ui.enterTableWidget->show();
}
//添加界面增加一行按钮
void TeacherWidget::on_addBtn_clicked()
{
	ui.enterBtn->setDown(true);
	ui.modifyBtn->setDown(false);
	ui.infoSearchBtn->setDown(false);
	ui.scoreSearchBtn->setDown(false);
	ui.allInfoBtn->setDown(false);
	QStringList header;
	header << "学号" << "课程编号" << "课程名称" << "平时成绩" << "实验成绩" << "卷面成绩" << "学分";
	ui.enterTableWidget->setColumnCount(header.count());
	ui.enterTableWidget->setHorizontalHeaderLabels(header);
	int nRow = ui.enterTableWidget->rowCount();

	ui.enterTableWidget->horizontalHeader()->setVisible(1);
	ui.enterTableWidget->insertRow(nRow);
	ui.enterTableWidget->show();
}
//添加界面确认添加按钮点击槽函数
void TeacherWidget::on_sureAddBtn_clicked()
{
	ui.enterBtn->setDown(true);
	ui.modifyBtn->setDown(false);
	ui.infoSearchBtn->setDown(false);
	ui.scoreSearchBtn->setDown(false);
	ui.allInfoBtn->setDown(false);
	qDebug() << ui.enterTableWidget->rowCount();
	qDebug() << ui.enterTableWidget->columnCount();
	while (ui.enterTableWidget->rowCount())
	{
		int nRow = ui.enterTableWidget->rowCount()-1; // 获取最后一行
		if (ui.enterTableWidget->item(nRow, 1) == NULL) {
			ui.enterTableWidget->setRowCount(nRow);
			continue;
		}
		int j = 0;
		QString id = ui.enterTableWidget->item(nRow, j++)->text();
		QString courseId = ui.enterTableWidget->item(nRow, j++)->text();
		QString courseName = ui.enterTableWidget->item(nRow, j++)->text();
		QString usualScore = ui.enterTableWidget->item(nRow, j++)->text();
		QString experimentScore = ui.enterTableWidget->item(nRow, j++)->text();
		QString paperScore = ui.enterTableWidget->item(nRow, j++)->text();
		QString score = ui.enterTableWidget->item(nRow, j++)->text();
		//检查合法性
		if (!SqlQuery::isInTable_standard("id", id, "student_info")) { MsgInterface::show_error("错误", id + "学号不存在"); return; }
		if (!SqlQuery::isInTable_standard("courseId", courseId, "course")) { MsgInterface::show_error("错误", courseId + "课程号不存在"); return; }
		if (!SqlQuery::isInTable_standard("courseId", courseId, "courseName", courseName, "course")) { MsgInterface::show_error("错误", nRow + "行课程号或课程名称输入错误"); return; }
		if (!SqlQuery::addScore(id, courseId, courseName, usualScore, experimentScore, paperScore, score)) 
		{
			MsgInterface::show_error("添加错误", id + " " + courseName + "已添加"); 
			ui.enterTableWidget->setRowCount(nRow);
			return;
		}
		ui.enterTableWidget->clearContents();
		//ui.enterTableWidget->setColumnCount(--nRow);
	}
	qDebug() << "done";
}
//基本信息查询界面 学号名字查询 按钮点击
void TeacherWidget::on_pushButton_1_clicked()
{
	ui.enterBtn->setDown(false);
	ui.modifyBtn->setDown(false);
	ui.infoSearchBtn->setDown(true);
	ui.scoreSearchBtn->setDown(false);
	ui.allInfoBtn->setDown(false);
	QString searchType = "";
	if (ui.idRadioButton->isChecked())
	{
		QString id = ui.inputLineEdit_1->text();
		QSqlDatabase db = SqlQuery::createConnection();
		if (!db.open()) {
			MsgInterface::show_error("错误", "连接服务器错误");
			return;
		}
		QSqlQuery query(db);
		QString str = QString("select * from student_info where id=\"%1\";").arg(id);
		query.exec(str);

		if (query.next())
		{
			qDebug() << query.value(0) << query.value(1);
			QStringList header;
			header << "学号" << "姓名" << "性别" << "民族" << "电话" << "学院" << "专业" << "班级" << "宿舍";
			ui.tableWidget_up->setColumnCount(header.count());
			ui.tableWidget_up->setRowCount(1);
			ui.tableWidget_up->setHorizontalHeaderLabels(header);
			ui.tableWidget_up->setItem(0, 0, new QTableWidgetItem(query.value(0).toString()));
			ui.tableWidget_up->setItem(0, 1, new QTableWidgetItem(query.value(1).toString()));
			ui.tableWidget_up->setItem(0, 2, new QTableWidgetItem(query.value(2).toString()));
			ui.tableWidget_up->setItem(0, 3, new QTableWidgetItem(query.value(3).toString()));
			ui.tableWidget_up->setItem(0, 4, new QTableWidgetItem(query.value(4).toString()));
			ui.tableWidget_up->setItem(0, 5, new QTableWidgetItem(query.value(5).toString()));
			ui.tableWidget_up->setItem(0, 6, new QTableWidgetItem(query.value(6).toString()));
			ui.tableWidget_up->setItem(0, 7, new QTableWidgetItem(query.value(7).toString()));
			ui.tableWidget_up->setItem(0, 8, new QTableWidgetItem(query.value(8).toString()));
			ui.tableWidget_up->show();
			MsgInterface::show_info("成功", "查询成功");
		}
		else MsgInterface::show_error("错误", "没有找到此人");
	}

	else if (ui.nameRadioButton->isChecked())
	{
		QString name = ui.inputLineEdit_1->text();
		QSqlDatabase db = SqlQuery::createConnection();
		if (!db.open()) {
			MsgInterface::show_error("错误", "连接服务器错误");
			return;
		}
		QSqlQuery query(db);
		QString str = QString("select * from student_info where name=\"%1\";").arg(name);
		query.exec(str);

		if (query.next())
		{
			qDebug() << query.value(0) << query.value(1);
			QStringList header;
			header << "学号" << "姓名" << "性别" << "民族" << "电话" << "学院" << "专业" << "班级" << "宿舍";
			ui.tableWidget_up->setColumnCount(header.count());
			ui.tableWidget_up->setRowCount(1);
			ui.tableWidget_up->setHorizontalHeaderLabels(header);
			ui.tableWidget_up->setItem(0, 0, new QTableWidgetItem(query.value(0).toString()));
			ui.tableWidget_up->setItem(0, 1, new QTableWidgetItem(query.value(1).toString()));
			ui.tableWidget_up->setItem(0, 2, new QTableWidgetItem(query.value(2).toString()));
			ui.tableWidget_up->setItem(0, 3, new QTableWidgetItem(query.value(3).toString()));
			ui.tableWidget_up->setItem(0, 4, new QTableWidgetItem(query.value(4).toString()));
			ui.tableWidget_up->setItem(0, 5, new QTableWidgetItem(query.value(5).toString()));
			ui.tableWidget_up->setItem(0, 6, new QTableWidgetItem(query.value(6).toString()));
			ui.tableWidget_up->setItem(0, 7, new QTableWidgetItem(query.value(7).toString()));
			ui.tableWidget_up->setItem(0, 8, new QTableWidgetItem(query.value(8).toString()));
			MsgInterface::show_info("成功", "查询成功");
			ui.tableWidget_up->show();
		}
		else MsgInterface::show_error("错误", "没有找到此人");
		
	}

	else MsgInterface::show_error("错误", "请选择查询类型");
}
//基本信息查询界面 宿舍查询按钮年级
void TeacherWidget::on_pushButton_2_clicked()
{
	ui.enterBtn->setDown(false);
	ui.modifyBtn->setDown(false);
	ui.infoSearchBtn->setDown(true);
	ui.scoreSearchBtn->setDown(false);
	ui.allInfoBtn->setDown(false);
	QString dor = ui.inputLineEdit_2->text();
	QSqlDatabase db = SqlQuery::createConnection();
	if (!db.open()) {
		MsgInterface::show_error("错误", "连接服务器错误");
		return;
	}
	QSqlQuery query(db);
	QString str = QString("select * from student_info where dormitory=\"%1\"").arg(dor);
	
	query.exec(str);
	int counts = query.size();
	if (query.next()) {
		ui.tableWidget_down->setRowCount(counts);
		QStringList header;
		header << "学号" << "姓名" << "性别" << "民族" << "电话" << "学院" << "专业" << "班级" << "宿舍";
		ui.tableWidget_down->setColumnCount(header.count());
		ui.tableWidget_down->setHorizontalHeaderLabels(header);
		for(int i=0;i<counts;i++){
			ui.tableWidget_down->setItem(i, 0, new QTableWidgetItem(query.value(0).toString()));
			ui.tableWidget_down->setItem(i, 1, new QTableWidgetItem(query.value(1).toString()));
			ui.tableWidget_down->setItem(i, 2, new QTableWidgetItem(query.value(2).toString()));
			ui.tableWidget_down->setItem(i, 3, new QTableWidgetItem(query.value(3).toString()));
			ui.tableWidget_down->setItem(i, 4, new QTableWidgetItem(query.value(4).toString()));
			ui.tableWidget_down->setItem(i, 5, new QTableWidgetItem(query.value(5).toString()));
			ui.tableWidget_down->setItem(i, 6, new QTableWidgetItem(query.value(6).toString()));
			ui.tableWidget_down->setItem(i, 7, new QTableWidgetItem(query.value(7).toString()));
			ui.tableWidget_down->setItem(i, 8, new QTableWidgetItem(query.value(8).toString()));
			query.next();
		}
		ui.tableWidget_down->show();
	}
	else MsgInterface::show_error("错误", "没有找到");
}
//查看所有学生信息界面 所有信息查询点击
void TeacherWidget::on_allInfoBtn_clicekd()
{
	ui.enterBtn->setDown(false);
	ui.modifyBtn->setDown(false);
	ui.infoSearchBtn->setDown(false);
	ui.scoreSearchBtn->setDown(false);
	ui.allInfoBtn->setDown(true);
	QString dor = ui.inputLineEdit_2->text();
	QSqlDatabase db = SqlQuery::createConnection();
	if (!db.open()) {
		MsgInterface::show_error("错误", "连接服务器错误");
		return;
	}
	QSqlQuery query(db);
	QString str = QString("select id,name,sex,native,tel,college,major,class,dormitory from student_info;");
	query.exec(str);
	int counts = query.size();
	if (query.next())
	{
		ui.allInfoTableWidget->setRowCount(counts);
		QStringList header;
		header << "学号" << "姓名" << "性别" << "民族" << "电话" << "学院" << "专业" << "班级" << "宿舍";
		ui.allInfoTableWidget->setColumnCount(header.count());
		ui.allInfoTableWidget->setHorizontalHeaderLabels(header);
		for(int i=0;i<counts;i++)
		{
			ui.allInfoTableWidget->setItem(i, 0, new QTableWidgetItem(query.value(0).toString()));
			ui.allInfoTableWidget->setItem(i, 1, new QTableWidgetItem(query.value(1).toString()));
			ui.allInfoTableWidget->setItem(i, 2, new QTableWidgetItem(query.value(2).toString()));
			ui.allInfoTableWidget->setItem(i, 3, new QTableWidgetItem(query.value(3).toString()));
			ui.allInfoTableWidget->setItem(i, 4, new QTableWidgetItem(query.value(4).toString()));
			ui.allInfoTableWidget->setItem(i, 5, new QTableWidgetItem(query.value(5).toString()));
			ui.allInfoTableWidget->setItem(i, 6, new QTableWidgetItem(query.value(6).toString()));
			ui.allInfoTableWidget->setItem(i, 7, new QTableWidgetItem(query.value(7).toString()));
			ui.allInfoTableWidget->setItem(i, 8, new QTableWidgetItem(query.value(8).toString()));
			query.next();
		}
		ui.allInfoTableWidget->show();

	}
	else MsgInterface::show_error(" ", "数据库为空");
}
//成绩查询界面 查询按钮点击
void TeacherWidget::on_searchBtn_clicked()
{
	ui.enterBtn->setDown(false);
	ui.modifyBtn->setDown(false);
	ui.infoSearchBtn->setDown(false);
	ui.scoreSearchBtn->setDown(true);
	ui.allInfoBtn->setDown(false);
	QString id = ui.idinputLineEdit->text();

	QSqlDatabase db = SqlQuery::createConnection();
	if (!db.open()) {
		MsgInterface::show_error("错误", "连接服务器错误");
		return;
	}
	QSqlQuery query(db);
	QString str = QString("select id,name,courseId,courseName,actualGrade,actualScore from student_info,"
				"scores where student_info.id=scores.studentId and studentId=\"%1\"; ").arg(id);
	query.exec(str);
	int counts = query.size();
	if (query.next())
	{
		double totalScore = 0;
		ui.scoreSearchTableWidget->setRowCount(counts);
		QStringList header;
		header << "学号" << "姓名" << "课程编号" << "课程名" << "综合成绩" << "实得学分" ;
		ui.scoreSearchTableWidget->setColumnCount(header.count());
		ui.scoreSearchTableWidget->setHorizontalHeaderLabels(header);
		for (int i = 0; i < counts; i++)
		{
			ui.scoreSearchTableWidget->setItem(i, 0, new QTableWidgetItem(query.value(0).toString()));
			ui.scoreSearchTableWidget->setItem(i, 1, new QTableWidgetItem(query.value(1).toString()));
			ui.scoreSearchTableWidget->setItem(i, 2, new QTableWidgetItem(query.value(2).toString()));
			ui.scoreSearchTableWidget->setItem(i, 3, new QTableWidgetItem(query.value(3).toString()));
			ui.scoreSearchTableWidget->setItem(i, 4, new QTableWidgetItem(query.value(4).toString()));
			ui.scoreSearchTableWidget->setItem(i, 5, new QTableWidgetItem(query.value(5).toString()));
			totalScore += query.value(5).toDouble();
			query.next();
		}
		ui.scoreSearchTableWidget->show();
		ui.outputLineEidt->setText(QString("共修%1科，实得学分").arg(counts) + QString::number(totalScore));
	}
	else MsgInterface::show_error(" ", "没有找到");
}
//成绩查询界面 细节展示
void TeacherWidget::on_radioButton_clicked()
{
	ui.enterBtn->setDown(false);
	ui.modifyBtn->setDown(false);
	ui.infoSearchBtn->setDown(false);
	ui.scoreSearchBtn->setDown(true);
	ui.allInfoBtn->setDown(false);
	if (!ui.radioButton->isChecked()) return this->on_searchBtn_clicked();
	QString id = ui.idinputLineEdit->text();
	QSqlDatabase db = SqlQuery::createConnection();
	if (!db.open()) {
		MsgInterface::show_error("错误", "连接服务器错误");
		return;
	}
	QSqlQuery query(db);
	QString str = QString("select id,name,courseId,courseName,usualPerformance,experiment,paperScore,actualGrade,actualScore from student_info,"
		"scores where student_info.id=scores.studentId and studentId=\"%1\"; ").arg(id);
	query.exec(str);
	int counts = query.size();
	if (query.next())
	{
		double totalScore = 0;
		ui.scoreSearchTableWidget->setRowCount(counts);
		QStringList header;
		header << "学号" << "姓名" << "课程编号" << "课程名" <<"平时成绩"<<"实验成绩"<<"卷面成绩"<< "综合成绩" << "实得学分";
		ui.scoreSearchTableWidget->setColumnCount(header.count());
		ui.scoreSearchTableWidget->setHorizontalHeaderLabels(header);
		for (int i = 0; i < counts; i++)
		{
			ui.scoreSearchTableWidget->setItem(i, 0, new QTableWidgetItem(query.value(0).toString()));
			ui.scoreSearchTableWidget->setItem(i, 1, new QTableWidgetItem(query.value(1).toString()));
			ui.scoreSearchTableWidget->setItem(i, 2, new QTableWidgetItem(query.value(2).toString()));
			ui.scoreSearchTableWidget->setItem(i, 3, new QTableWidgetItem(query.value(3).toString()));
			ui.scoreSearchTableWidget->setItem(i, 4, new QTableWidgetItem(query.value(4).toString()));
			ui.scoreSearchTableWidget->setItem(i, 5, new QTableWidgetItem(query.value(5).toString()));
			ui.scoreSearchTableWidget->setItem(i, 6, new QTableWidgetItem(query.value(6).toString()));
			ui.scoreSearchTableWidget->setItem(i, 7, new QTableWidgetItem(query.value(7).toString()));
			ui.scoreSearchTableWidget->setItem(i, 8, new QTableWidgetItem(query.value(8).toString()));
			totalScore += query.value(8).toDouble();
			query.next();
		}
		ui.scoreSearchTableWidget->show();
		ui.outputLineEidt->setText(QString("共修%1科，实得学分").arg(counts) + QString::number(totalScore));
	}
	else MsgInterface::show_error(" ", "没有找到");
}
//成绩修改界面 查询按钮点击
void TeacherWidget::on_searchBtn_2_clicked()
{
	ui.enterBtn->setDown(false);
	ui.modifyBtn->setDown(true);
	ui.infoSearchBtn->setDown(false);
	ui.scoreSearchBtn->setDown(false);
	ui.allInfoBtn->setDown(false);
	QString id = ui.lineEdit->text();
	QSqlDatabase db = SqlQuery::createConnection();
	if (!db.open()) {
		MsgInterface::show_error("错误", "连接服务器错误");
		return;
	}
	ui.comboBox->clear();
	QSqlQuery query1(db);
	QString str1 = QString("select courseName from scores where studentId=\"%1\";").arg(id);
	query1.exec(str1);
	int counts1 = query1.size();

	if (query1.next())
	{
		QStringList list;
		for (int i = 0; i < counts1; i++)
		{
			qDebug() << query1.value(0).toString();
			list.append(query1.value(0).toString());
			query1.next();
		}
		ui.comboBox->addItems(list);
	}
	else {
		MsgInterface::show_error("", "学号错误或没有成绩");
	}

}
//成绩修改界面 下拉框选择事件
void TeacherWidget::value_change(QString value)
{
	ui.enterBtn->setDown(false);
	ui.modifyBtn->setDown(true);
	ui.infoSearchBtn->setDown(false);
	ui.scoreSearchBtn->setDown(false);
	ui.allInfoBtn->setDown(false);
	QString id = ui.lineEdit->text();
	QSqlDatabase db = SqlQuery::createConnection();
	if (!db.open()) {
		MsgInterface::show_error("错误", "连接服务器错误");
		return;
	}
	QSqlQuery query(db);
	QString str = QString("select name,usualPerformance,experiment,paperScore,courseId,score from student_info,scores where "
		"scores.studentId = \"%1\" and student_info.id = scores.studentId and courseName = \"%2\"; ").arg(id,value);

	query.exec(str);
	if(query.next())
	{
		ui.mod_name_lineEdit->setText(query.value(0).toString());
		ui.mod_usual_lineEdit->setText(query.value(1).toString());
		ui.mod_exp_lineEdit->setText(query.value(2).toString());
		ui.mod_paper_lineEdit->setText(query.value(3).toString());

		ui.mod_courseId_lineEdit->setText(query.value(4).toString());
		ui.mod_score_lineEdit->setText(query.value(5).toString());

		ui.mod_courseId_lineEdit->setEnabled(0);
		ui.mod_score_lineEdit->setEnabled(0);
	}
	else {
		MsgInterface::show_error("", "该课程没有成绩");
	}
}
//成绩修改界面 确认修改点击事件
void TeacherWidget::on_mod_sure_Btn_clicked()
{
	ui.enterBtn->setDown(false);
	ui.modifyBtn->setDown(true);
	ui.infoSearchBtn->setDown(false);
	ui.scoreSearchBtn->setDown(false);
	ui.allInfoBtn->setDown(false);
	QString id = ui.lineEdit->text();
	QString usualScore = ui.mod_usual_lineEdit->text();
	QString experimentScore = ui.mod_exp_lineEdit->text();
	QString paperScore = ui.mod_paper_lineEdit->text();
	QString courseId = ui.mod_courseId_lineEdit->text();
	QString score = ui.mod_score_lineEdit->text();
	QString courseName = ui.comboBox->currentText();
	if (SqlQuery::updateScore(id, courseId, courseName, usualScore, experimentScore, paperScore, score)) MsgInterface::show_info("成功", "修改成功");
	else MsgInterface::show_error("修改失败", "修改失败");
}


