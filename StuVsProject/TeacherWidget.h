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
	//��ʾ¼��ҳ��
	void show_enter_page();
private slots:
	//���¼ȡ��ť
	void on_addBtn_clicked();
	//���ȷ�ϰ�ť
	void on_sureAddBtn_clicked();
	//�����ѧ��/������ѯ��ť
	void on_pushButton_1_clicked();
	//����������ѯ��ť
	void on_pushButton_2_clicked();
	//�����ʾ����ѧ����Ϣ��ť
	void on_allInfoBtn_clicekd();
	//�����ѯ��ť
	void on_searchBtn_clicked();
	//�����ʾ�ɼ�ϸ��radioButton
	void on_radioButton_clicked();
	//�����ѯ��ť2
	void on_searchBtn_2_clicked();
	//������ֵ�仯�ۺ���
	void value_change(QString value);
	//�޸Ľ�����ȷ���޸İ�ť
	void on_mod_sure_Btn_clicked();
signals:
	//���ص�¼ҳ��
	void backToLogin();
private:
	Ui::TeacherWidget ui;
	QSqlTableModel* model;
};
