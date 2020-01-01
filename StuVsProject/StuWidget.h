#pragma once

#include <QWidget>
#include "ui_StuWidget.h"

class StuWidget : public QWidget
{
	Q_OBJECT

public:
	StuWidget(QWidget *parent = Q_NULLPTR);
	~StuWidget();

	void searchPage_show();

	void setId(QString id);

	QString getId();

	void modifyPage_show();

private slots:
	void on_sureBtn_clicked();

signals:
	void backToLogin();

private:
	Ui::StuWidget ui;
	QString id;
};
