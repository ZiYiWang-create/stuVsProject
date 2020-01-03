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

	//¼����Ϣ����
	connect(ui.enterBtn, &QPushButton::clicked, [=]() {
		ui.stackedWidget->setCurrentWidget(ui.enterPage);
		show_enter_page();
		ui.enterBtn->setDown(true);
		ui.modifyBtn->setDown(false);
		ui.infoSearchBtn->setDown(false);
		ui.scoreSearchBtn->setDown(false);
		ui.allInfoBtn->setDown(false);
		});	

	// �޸���Ϣ����
	connect(ui.modifyBtn, &QPushButton::clicked, [=]() {
		ui.stackedWidget->setCurrentWidget(ui.modifyPage);
		ui.enterBtn->setDown(false);
		ui.modifyBtn->setDown(true);
		ui.infoSearchBtn->setDown(false);
		ui.scoreSearchBtn->setDown(false);
		ui.allInfoBtn->setDown(false);
		});

	//������Ϣ��ѯ����
	connect(ui.infoSearchBtn, &QPushButton::clicked, [=]() {
		ui.stackedWidget->setCurrentWidget(ui.infoSearchPage);
		ui.enterBtn->setDown(false);
		ui.modifyBtn->setDown(false);
		ui.infoSearchBtn->setDown(true);
		ui.scoreSearchBtn->setDown(false);
		ui.allInfoBtn->setDown(false);
		});

	//������ѯ����
	connect(ui.scoreSearchBtn, &QPushButton::clicked, [=]() {
		ui.stackedWidget->setCurrentWidget(ui.scoreSearchPage);
		ui.enterBtn->setDown(false);
		ui.modifyBtn->setDown(false);
		ui.infoSearchBtn->setDown(false);
		ui.scoreSearchBtn->setDown(true);
		ui.allInfoBtn->setDown(false);
		});
	//������Ϣ��ѯ����
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

//¼�����
void TeacherWidget::show_enter_page()
{
	ui.enterBtn->setDown(true);
	ui.modifyBtn->setDown(false);
	ui.infoSearchBtn->setDown(false);
	ui.scoreSearchBtn->setDown(false);
	ui.allInfoBtn->setDown(false);
	QSqlDatabase db = SqlQuery::createConnection();
	if (!db.open()) {
		QMessageBox::warning(NULL, "����", "���ӷ���������");
		return;
	}
	QStringList header;
	header << "ѧ��" << "�γ̱��" << "�γ�����" << "ƽʱ����" << "ʵ�����" << "����ɼ�" << "�γ�ѧ��";
	ui.enterTableWidget->setColumnCount(header.count());
	ui.enterTableWidget->setRowCount(1);
	ui.enterTableWidget->setHorizontalHeaderLabels(header);
	ui.enterTableWidget->show();
}
//��ӽ�������һ�а�ť
void TeacherWidget::on_addBtn_clicked()
{
	ui.enterBtn->setDown(true);
	ui.modifyBtn->setDown(false);
	ui.infoSearchBtn->setDown(false);
	ui.scoreSearchBtn->setDown(false);
	ui.allInfoBtn->setDown(false);
	QStringList header;
	header << "ѧ��" << "�γ̱��" << "�γ�����" << "ƽʱ�ɼ�" << "ʵ��ɼ�" << "����ɼ�" << "ѧ��";
	ui.enterTableWidget->setColumnCount(header.count());
	ui.enterTableWidget->setHorizontalHeaderLabels(header);
	int nRow = ui.enterTableWidget->rowCount();

	ui.enterTableWidget->horizontalHeader()->setVisible(1);
	ui.enterTableWidget->insertRow(nRow);
	ui.enterTableWidget->show();
}
//��ӽ���ȷ����Ӱ�ť����ۺ���
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
		int nRow = ui.enterTableWidget->rowCount()-1; // ��ȡ���һ��
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
		//���Ϸ���
		if (!SqlQuery::isInTable_standard("id", id, "student_info")) { MsgInterface::show_error("����", id + "ѧ�Ų�����"); return; }
		if (!SqlQuery::isInTable_standard("courseId", courseId, "course")) { MsgInterface::show_error("����", courseId + "�γ̺Ų�����"); return; }
		if (!SqlQuery::isInTable_standard("courseId", courseId, "courseName", courseName, "course")) { MsgInterface::show_error("����", nRow + "�пγ̺Ż�γ������������"); return; }
		if (!SqlQuery::addScore(id, courseId, courseName, usualScore, experimentScore, paperScore, score)) 
		{
			MsgInterface::show_error("��Ӵ���", id + " " + courseName + "�����"); 
			ui.enterTableWidget->setRowCount(nRow);
			return;
		}
		ui.enterTableWidget->clearContents();
		//ui.enterTableWidget->setColumnCount(--nRow);
	}
	qDebug() << "done";
}
//������Ϣ��ѯ���� ѧ�����ֲ�ѯ ��ť���
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
			MsgInterface::show_error("����", "���ӷ���������");
			return;
		}
		QSqlQuery query(db);
		QString str = QString("select * from student_info where id=\"%1\";").arg(id);
		query.exec(str);

		if (query.next())
		{
			qDebug() << query.value(0) << query.value(1);
			QStringList header;
			header << "ѧ��" << "����" << "�Ա�" << "����" << "�绰" << "ѧԺ" << "רҵ" << "�༶" << "����";
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
			MsgInterface::show_info("�ɹ�", "��ѯ�ɹ�");
		}
		else MsgInterface::show_error("����", "û���ҵ�����");
	}

	else if (ui.nameRadioButton->isChecked())
	{
		QString name = ui.inputLineEdit_1->text();
		QSqlDatabase db = SqlQuery::createConnection();
		if (!db.open()) {
			MsgInterface::show_error("����", "���ӷ���������");
			return;
		}
		QSqlQuery query(db);
		QString str = QString("select * from student_info where name=\"%1\";").arg(name);
		query.exec(str);

		if (query.next())
		{
			qDebug() << query.value(0) << query.value(1);
			QStringList header;
			header << "ѧ��" << "����" << "�Ա�" << "����" << "�绰" << "ѧԺ" << "רҵ" << "�༶" << "����";
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
			MsgInterface::show_info("�ɹ�", "��ѯ�ɹ�");
			ui.tableWidget_up->show();
		}
		else MsgInterface::show_error("����", "û���ҵ�����");
		
	}

	else MsgInterface::show_error("����", "��ѡ���ѯ����");
}
//������Ϣ��ѯ���� �����ѯ��ť�꼶
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
		MsgInterface::show_error("����", "���ӷ���������");
		return;
	}
	QSqlQuery query(db);
	QString str = QString("select * from student_info where dormitory=\"%1\"").arg(dor);
	
	query.exec(str);
	int counts = query.size();
	if (query.next()) {
		ui.tableWidget_down->setRowCount(counts);
		QStringList header;
		header << "ѧ��" << "����" << "�Ա�" << "����" << "�绰" << "ѧԺ" << "רҵ" << "�༶" << "����";
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
	else MsgInterface::show_error("����", "û���ҵ�");
}
//�鿴����ѧ����Ϣ���� ������Ϣ��ѯ���
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
		MsgInterface::show_error("����", "���ӷ���������");
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
		header << "ѧ��" << "����" << "�Ա�" << "����" << "�绰" << "ѧԺ" << "רҵ" << "�༶" << "����";
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
	else MsgInterface::show_error(" ", "���ݿ�Ϊ��");
}
//�ɼ���ѯ���� ��ѯ��ť���
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
		MsgInterface::show_error("����", "���ӷ���������");
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
		header << "ѧ��" << "����" << "�γ̱��" << "�γ���" << "�ۺϳɼ�" << "ʵ��ѧ��" ;
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
		ui.outputLineEidt->setText(QString("����%1�ƣ�ʵ��ѧ��").arg(counts) + QString::number(totalScore));
	}
	else MsgInterface::show_error(" ", "û���ҵ�");
}
//�ɼ���ѯ���� ϸ��չʾ
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
		MsgInterface::show_error("����", "���ӷ���������");
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
		header << "ѧ��" << "����" << "�γ̱��" << "�γ���" <<"ƽʱ�ɼ�"<<"ʵ��ɼ�"<<"����ɼ�"<< "�ۺϳɼ�" << "ʵ��ѧ��";
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
		ui.outputLineEidt->setText(QString("����%1�ƣ�ʵ��ѧ��").arg(counts) + QString::number(totalScore));
	}
	else MsgInterface::show_error(" ", "û���ҵ�");
}
//�ɼ��޸Ľ��� ��ѯ��ť���
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
		MsgInterface::show_error("����", "���ӷ���������");
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
		MsgInterface::show_error("", "ѧ�Ŵ����û�гɼ�");
	}

}
//�ɼ��޸Ľ��� ������ѡ���¼�
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
		MsgInterface::show_error("����", "���ӷ���������");
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
		MsgInterface::show_error("", "�ÿγ�û�гɼ�");
	}
}
//�ɼ��޸Ľ��� ȷ���޸ĵ���¼�
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
	if (SqlQuery::updateScore(id, courseId, courseName, usualScore, experimentScore, paperScore, score)) MsgInterface::show_info("�ɹ�", "�޸ĳɹ�");
	else MsgInterface::show_error("�޸�ʧ��", "�޸�ʧ��");
}


