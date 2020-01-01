#pragma once
#pragma execution_character_set("utf-8")
#include <QWidget>
#include <qsqltablemodel.h>
#include "ui_RootWidget.h"
class RootWidget : public QWidget
{
	Q_OBJECT

public:
	RootWidget(QWidget *parent = Q_NULLPTR);
	~RootWidget();

signals:
	void backToLogin();
			
protected slots:
	//void show_view();

	//void set_modifiable();

	//void submit();
	//void add();

private:
	Ui::RootWidget ui;
	QSqlTableModel* model_sudent;
	QSqlTableModel* model_teacher;
};
