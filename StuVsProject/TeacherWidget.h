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
	//显示录入页面
	void show_enter_page();
private slots:
	//点击录取按钮
	void on_addBtn_clicked();
	//点击确认按钮
	void on_sureAddBtn_clicked();
	//点击按学号/姓名查询按钮
	void on_pushButton_1_clicked();
	//点击按宿舍查询按钮
	void on_pushButton_2_clicked();
	//点击显示所有学生信息按钮
	void on_allInfoBtn_clicekd();
	//点击查询按钮
	void on_searchBtn_clicked();
	//点击显示成绩细节radioButton
	void on_radioButton_clicked();
	//点击查询按钮2
	void on_searchBtn_2_clicked();
	//下拉框值变化槽函数
	void value_change(QString value);
	//修改界面点击确认修改按钮
	void on_mod_sure_Btn_clicked();
signals:
	//返回登录页面
	void backToLogin();
private:
	Ui::TeacherWidget ui;
	QSqlTableModel* model;
};
