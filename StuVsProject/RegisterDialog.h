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
	//�˻ص�¼���ź�
	void backToLogin();

private slots:
	//������ص�¼��ť
	void on_backBtn_clicked();
	//���ȷ���޸İ�ť
	void on_sureBtn_clicked();
private:
	Ui::RegisterDialog ui;
};
