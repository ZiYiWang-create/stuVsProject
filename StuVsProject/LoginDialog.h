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
    void openMainWidget();
    void openResDialog();
    void openRootWidget();
    void openStudentWidget(QString id);
    void openTeacherWidget();

private slots:
    void on_LogInBtn_clicked();
    void on_exitBtn_clicked();
    void on_registerBtn_clicked();

private:
	Ui::LoginDialog ui;
};
