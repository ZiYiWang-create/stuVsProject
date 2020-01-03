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
    //���޸����봰��
    void openResDialog();
    //�򿪹���˴���
    void openRootWidget();
    //��ѧ���˴��� ÿ��ѧ����Ӧһ��id �����źŴ���id����
    void openStudentWidget(QString id);
    //�򿪽�ʦ�˴���
    void openTeacherWidget();
private slots:
    //�����¼��ť
    void on_LogInBtn_clicked();
    //����˳���¼��ť
    void on_exitBtn_clicked();
    //����������밴ť
    void on_registerBtn_clicked();
private:
	Ui::LoginDialog ui;
};
