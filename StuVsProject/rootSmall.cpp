#include "rootSmall.h"
#include <qsqldatabase.h>
#include "SqlQuery.h"
#include "MsgInterface.h"
rootSmall::rootSmall(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    //添加按钮点击事件
    //刷新按钮
    connect(ui.flashBtn, &QPushButton::clicked, [=]()
        {
            show_tableview();
        });


}

rootSmall::~rootSmall()
{
}

void rootSmall::set_type(QString type)
{
    this->type = type;
}

void rootSmall::on_addBtn_clicked()
{
    //QString id = ui.idLineEdit->text();
    //QString name = ui.nameLineEdit->text();
    //QString pwd = "123456";
    //if (SqlQuery::add(id, name, pwd, type)) MsgInterface::show_info("", "添加成功");
    //else MsgInterface::show_error("", "添加失败");
    //ui.idLineEdit->clear();
    //ui.nameLineEdit->clear();
}

void rootSmall::on_delBtn_clicked()
{
    QString id = ui.dellineEdit->text();
    if (!SqlQuery::isInTable(id, type + "_info")) {MsgInterface::show_error("错误", "用户不存在"); return;}
    if (SqlQuery::delDataById(id, type))
    {
        MsgInterface::show_info("成功", "删除成功");
        return;
    }
    else {
        MsgInterface::show_error("失败", "删除失败");
        return;
    }
}


void rootSmall::show_tableview()
{
    QSqlDatabase db = SqlQuery::createConnection();
    if (!db.open()) {
        MsgInterface::show_error("错误", "连接服务器错误");
        return;
    }
    this->model = new QSqlTableModel(this);
    if (type == "student") {
        ui.tabWidget->setTabText(0,"学生");
        ui.stackedWidget->setCurrentWidget(ui.studentPage);
        model->setTable("student_info");
        ui.stuTableView->setModel(model);
        model->select();
        model->setHeaderData(0, Qt::Horizontal, tr("学号/工号"));
        model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        model->setHeaderData(2, Qt::Horizontal, tr("密码"));
    }
    else if (type == "teacher")
    {
        ui.tabWidget->setTabText(0, "教师");
        model->setTable("teacher_info");
        ui.stackedWidget->setCurrentWidget(ui.teacherPage);
        ui.stuTableView->setModel(model);
        model->select();
        model->setHeaderData(0, Qt::Horizontal, tr("学号/工号"));
        model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        model->setHeaderData(2, Qt::Horizontal, tr("密码"));
    }
    ui.stuTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void rootSmall::setAddPage()
{
    if (type == "student") ui.stackedWidget->setCurrentIndex(1);
    else if (type == "teacher") ui.stackedWidget->setCurrentIndex(0);
    else throw "setAddPage error";
}