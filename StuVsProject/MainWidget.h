#pragma once
#pragma execution_character_set("utf-8")
#include <QWidget>
#include "logindialog.h"
#include"registerdialog.h"
#include"rootwidget.h"
#include "ui_MainWidget.h"
#include "TeacherWidget.h"
#include "StuWidget.h"
class MainWidget : public QWidget
{
    Q_OBJECT

public:
     MainWidget(QWidget* parent = nullptr);
    ~MainWidget();

protected slots:
    void showMainWidget();
    void showRootWidget();
    void showStudentWidget(QString id);
    void showTeacherWidget();

private:
    Ui::MainWidget ui;
    LoginDialog* Logindialog;
    RegisterDialog* resDialog;
    RootWidget* rootWidget;
    TeacherWidget* teacherWidget;
    StuWidget* studentWidget;
};