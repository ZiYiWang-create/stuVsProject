#pragma once
#pragma execution_character_set("utf-8")
#include <QWidget>
#include "ui_RegisterDialog.h"

class RegisterDialog : public QWidget
{
	Q_OBJECT

public:
	RegisterDialog(QWidget *parent = Q_NULLPTR);
	~RegisterDialog();
signals:
	//退回登录框信号
	void backToLogin();

private slots:
	//点击返回登录按钮
	void on_backBtn_clicked();
	//点击确认修改按钮
	void on_sureBtn_clicked();
private:
	Ui::RegisterDialog ui;
};
