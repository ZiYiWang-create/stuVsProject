#include "TeacherWidget.h"
#include "SqlQuery.h"
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
		});

	// �޸���Ϣ����
	connect(ui.modifyBtn, &QPushButton::clicked, [=]() {
		ui.stackedWidget->setCurrentWidget(ui.modifyPage);
		});

	//������Ϣ��ѯ����
	connect(ui.infoSearchBtn, &QPushButton::clicked, [=]() {
		ui.stackedWidget->setCurrentWidget(ui.infoSearchPage);
		});

	//������ѯ����
	connect(ui.scoreSearchBtn, &QPushButton::clicked, [=]() {
		ui.stackedWidget->setCurrentWidget(ui.scoreSearchPage);
		});


}

TeacherWidget::~TeacherWidget()
{
}

void TeacherWidget::show_enter_page()
{
	QSqlDatabase db = SqlQuery::createConnection();

	model = new QSqlTableModel(this,db);

	model->setTable("scores");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->select();
	ui.enterTableView->show();
}