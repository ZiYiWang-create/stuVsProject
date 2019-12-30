#include "RootWidget.h"
#include <qsqlquerymodel.h>
#include "SqlQuery.h"
#include "qsqlrecord.h"
RootWidget::RootWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    ui.student_page->set_type("student");
    connect(ui.exitBtn, &QPushButton::clicked, [=]() {
        emit backToLogin();
        this->close();
        });

    connect(ui.stuBtn, &QPushButton::clicked, [=]() {
        ui.student_page->set_type("student");
        ui.student_page->show_tableview();
        ui.stackedWidget->setCurrentWidget(ui.student_page);
     });
    connect(ui.teacherBtn, &QPushButton::clicked, [=]() {
        ui.teacher_page->set_type("teacher");
        ui.teacher_page->show_tableview();
        ui.stackedWidget->setCurrentWidget(ui.teacher_page);
     });
    

}

RootWidget::~RootWidget()
{
}


//void RootWidget::show_view()
//{
//    QSqlDatabase db = SqlQuery::createConnection();
//    if (!db.open()) {
//        QMessageBox::warning(NULL, "错误", "连接服务器错误");
//        return;
//    }
//    model = new QSqlTableModel(this);
//    model->setTable("student_info");
//    ui.tableView->setModel(model);
//    model->select();
//    model->setHeaderData(0, Qt::Horizontal, tr("学号/工号"));
//    model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
//    model->setHeaderData(2, Qt::Horizontal, tr("密码"));
//    ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui.groupBox->setTitle("查询结果，不可修改");
//    ui.modefyBtn->setEnabled(1);
//    ui.sureBtn->setEnabled(0);
//    ui.addBtn->setEnabled(1);
//}
//
//
//void RootWidget::set_modifiable()
//{
//    //model->setEditStrategy(QSqlTableModel::OnManualSubmit);  // 设置可以修改的
//    ui.tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
//    ui.groupBox->setTitle("查询结果，可修改");
//    ui.addBtn->setEnabled(1);
//    ui.sureBtn->setEnabled(1);
//
//}
//
//void RootWidget::submit()
//{
//    model->submitAll();
//    ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    MsgInterface::show_info("success", "提交成功");
//    ui.groupBox->setTitle("查询结果，可修改");
//    ui.addBtn->setEnabled(0);
//    ui.sureBtn->setEnabled(0);
//    ui.modefyBtn->setEnabled(0);
//}
//
//void RootWidget::add()
//{
//    QSqlRecord record = model->record();
//    int row = model->rowCount();
//    model->insertRecord(row, record);
//    this->set_modifiable();
//}
