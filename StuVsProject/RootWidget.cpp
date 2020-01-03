#include "RootWidget.h"
#include <qsqlquerymodel.h>
#include "SqlQuery.h"
#include "qsqlrecord.h"
RootWidget::RootWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    ui.student_page->set_type("student");
    //点击退出登录按钮
    connect(ui.exitBtn, &QPushButton::clicked, [=]() {
        emit backToLogin();
        this->close();
        });
    //点击学生管理按钮
    connect(ui.stuBtn, &QPushButton::clicked, [=]() {
        ui.student_page->set_type("student");
        ui.student_page->show_tableview();
        ui.stackedWidget->setCurrentWidget(ui.student_page);
     });
    //点击教师管理按钮
    connect(ui.teacherBtn, &QPushButton::clicked, [=]() {
        ui.teacher_page->set_type("teacher");
        ui.teacher_page->show_tableview();
        ui.stackedWidget->setCurrentWidget(ui.teacher_page);
     });
}

RootWidget::~RootWidget()
{
}