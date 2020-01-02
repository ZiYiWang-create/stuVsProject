#pragma once

#include <QWidget>
#include "ui_TeacherWidget.h"
#include <QSqlTableModel>
#include <QSqlQueryModel>

class TeacherWidget : public QWidget
{
	Q_OBJECT

public:
	TeacherWidget(QWidget *parent = Q_NULLPTR);
	~TeacherWidget();
	
	void show_enter_page();
	private slots:
	void on_addBtn_clicked();
	void on_sureAddBtn_clicked();
	void on_pushButton_1_clicked();
	void on_pushButton_2_clicked();
	void on_allInfoBtn_clicekd();
	void on_searchBtn_clicked();
	void on_radioButton_clicked();
	void on_searchBtn_2_clicked();
	void value_change(QString value);
	void on_mod_sure_Btn_clicked();

signals:
	void backToLogin();

private:
	Ui::TeacherWidget ui;
	QSqlTableModel* model;
};
