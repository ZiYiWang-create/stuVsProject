#pragma once
#pragma execution_character_set("utf-8")
#include <QWidget>
#include "ui_LoginDialog.h"
#include "MsgInterface.h"
#include "RegisterDialog.h"
class LoginDialog : public QWidget
{
	Q_OBJECT

public:
	LoginDialog(QWidget *parent = Q_NULLPTR);
	~LoginDialog();
signals:
    //打开修改密码窗口
    void openResDialog();
    //打开管理端窗口
    void openRootWidget();
    //打开学生端窗口 每个学生对应一个id 随意信号带着id发送
    void openStudentWidget(QString id);
    //打开教师端窗口
    void openTeacherWidget();
private slots:
    //点击登录按钮
    void on_LogInBtn_clicked();
    //点击退出登录按钮
    void on_exitBtn_clicked();
    //点击忘记密码按钮
    void on_registerBtn_clicked();
private:
	Ui::LoginDialog ui;
};
