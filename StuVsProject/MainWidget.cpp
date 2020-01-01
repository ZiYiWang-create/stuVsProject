#include "mainwidget.h"
//#include "ui_mainwidget.h"
#include"SqlQuery.h"

MainWidget::MainWidget(QWidget* parent) :
    QWidget(parent)
{
    ui.setupUi(this);

    //////////////////////////////////////////// ��¼�Ի���////////////////////////////////////////////
    Logindialog = new LoginDialog;
    Logindialog->show();
    //connect(Logindialog, SIGNAL(openMainWidget()), this, SLOT(showMainWidget()));
    connect(Logindialog, SIGNAL(openRootWidget()), this, SLOT(showRootWidget()));
    connect(Logindialog, SIGNAL(openTeacherWidget()), this, SLOT(showTeacherWidget()));
    connect(Logindialog, SIGNAL(openStudentWidget(QString)), this, SLOT(showStudentWidget(QString)));
    /////////////////////////////////////////// ע��Ի���/////////////////////////////////////////////
    resDialog = new RegisterDialog;
    connect(Logindialog, SIGNAL(openResDialog()), resDialog, SLOT(show()));
    /////*������ص�¼*/
    connect(resDialog, SIGNAL(backToLogin()), Logindialog, SLOT(show()));


    /////////////////////////////////////////��root����Ľ���//////////////////////////////////////

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
void MainWidget::showStudentWidget(QString id)
{
    studentWidget = new StuWidget;
    studentWidget->show();
    studentWidget->setId(id);
    Logindialog->close();
    connect(studentWidget, SIGNAL(backToLogin()), Logindialog, SLOT(show()));
}