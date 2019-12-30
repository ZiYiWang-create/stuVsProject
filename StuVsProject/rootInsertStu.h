#pragma once

#include <QWidget>
#include "ui_rootInsertStu.h"

class rootInsertStu : public QWidget
{
	Q_OBJECT

public:
	rootInsertStu(QWidget *parent = Q_NULLPTR);
	~rootInsertStu();

protected slots:
	void on_sureBtn_clicked();
private:
	Ui::rootInsertStu ui;
};


