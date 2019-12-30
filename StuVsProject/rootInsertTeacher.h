#pragma once

#include <QWidget>
#include "ui_rootInsertTeacher.h"

class rootInsertTeacher : public QWidget
{
	Q_OBJECT

public:
	rootInsertTeacher(QWidget *parent = Q_NULLPTR);
	~rootInsertTeacher();

protected slots:
	void on_sureBtn_clicked();
private:
	Ui::rootInsertTeacher ui;
};
