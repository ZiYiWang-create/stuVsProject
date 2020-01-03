#pragma once

#include <QWidget>
#include "ui_StuWidget.h"

class StuWidget : public QWidget
{
	Q_OBJECT

public:
	StuWidget(QWidget *parent = Q_NULLPTR);
	~StuWidget();
	//成绩查询页面
	void searchPage_show();
	//设置id
	void setId(QString id);
	//获取id
	QString getId();
	//显示修改信息页面
	void modifyPage_show();
private slots:
	//点击确认修改按钮
	void on_sureBtn_clicked();
signals:
	//返回登录页面
	void backToLogin();
private:
	Ui::StuWidget ui;
	QString id;
};
