#pragma once
#pragma execution_character_set("utf-8")

#include <QWidget>
#include "ui_rootSmall.h"
#include <qsqltablemodel.h>

class rootSmall : public QWidget
{
	Q_OBJECT

public:
	rootSmall(QWidget *parent = Q_NULLPTR);
	~rootSmall();

	void show_tableview();
	void setAddPage();
	void set_type(QString type);

private slots:
	void on_addBtn_clicked();
	void on_delBtn_clicked();

private:
	Ui::rootSmall ui;
	QSqlTableModel* model;
	QString type="student";
};
