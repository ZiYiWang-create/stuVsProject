#pragma once

#include <QWidget>
#include "ui_TeacherWidget.h"
#include <QSqlTableModel>
class TeacherWidget : public QWidget
{
	Q_OBJECT

public:
	TeacherWidget(QWidget *parent = Q_NULLPTR);
	~TeacherWidget();
	
	void show_enter_page();
signals:
	void backToLogin();

private:
	Ui::TeacherWindow ui;
	QSqlTableModel* model;
};
