#pragma once

#include <QWidget>
#include "ui_StuWidget.h"

class StuWidget : public QWidget
{
	Q_OBJECT

public:
	StuWidget(QWidget *parent = Q_NULLPTR);
	~StuWidget();

private:
	Ui::StuWidget ui;
};
