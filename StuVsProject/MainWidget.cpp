#include "mainwidget.h"
//#include "ui_mainwidget.h"
#include"SqlQuery.h"

MainWidget::MainWidget(QWidget* parent) :
    QWidget(parent)
{
    ui.setupUi(this);

    //////////////////////////////////////////// 登录对话框////////////////////////////////////////////
    Logindialog = new LoginDialog;
    Logindialog->show();
    connect(Logindialog, SIGNAL(openMainWidget()), this, SLOT(showMainWidget()));
    connect(Logindialog, SIGNAL(openRootWidget()), this, SLOT(showRootWidget()));
    connect(Logindialog, SIGNAL(openTeacherWidget()), this, SLOT(showTeacherWidget()));

    /////////////////////////////////////////// 注册对话框/////////////////////////////////////////////
    resDialog = new RegisterDialog;
    connect(Logindialog, SIGNAL(openResDialog()), resDialog, SLOT(show()));
    /////*点击返回登录*/
    connect(resDialog, SIGNAL(backToLogin()), Logindialog, SLOT(show()));


    /////////////////////////////////////////与root界面的交互//////////////////////////////////////

}

MainWidget::~MainWidget()
{
    //delete ui;
}

void MainWidget::showMainWidget()
{
    this->show();
    Logindialog->close();
}

void MainWidget::showRootWidget()
{
    rootWidget = new RootWidget;
    rootWidget->show();
    Logindialog->close();
    connect(rootWidget, SIGNAL(backToLogin()), Logindialog, SLOT(show()));
}
void MainWidget::showTeacherWidget()
{
    teacherWidget = new TeacherWidget;
    teacherWidget->show();
    Logindialog->close();
    connect(teacherWidget, SIGNAL(backToLogin()), Logindialog, SLOT(show()));
}