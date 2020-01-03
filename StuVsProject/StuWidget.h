#pragma once

#include <QWidget>
#include "ui_StuWidget.h"

class StuWidget : public QWidget
{
	Q_OBJECT

public:
	StuWidget(QWidget *parent = Q_NULLPTR);
	~StuWidget();
	//�ɼ���ѯҳ��
	void searchPage_show();
	//����id
	void setId(QString id);
	//��ȡid
	QString getId();
	//��ʾ�޸���Ϣҳ��
	void modifyPage_show();
private slots:
	//���ȷ���޸İ�ť
	void on_sureBtn_clicked();
signals:
	//���ص�¼ҳ��
	void backToLogin();
private:
	Ui::StuWidget ui;
	QString id;
};
