#include "rootSmall.h"
#include <qsqldatabase.h>
#include "SqlQuery.h"
#include "MsgInterface.h"
rootSmall::rootSmall(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    //��Ӱ�ť����¼�
    //ˢ�°�ť
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
    //if (SqlQuery::add(id, name, pwd, type)) MsgInterface::show_info("", "��ӳɹ�");
    //else MsgInterface::show_error("", "���ʧ��");
    //ui.idLineEdit->clear();
    //ui.nameLineEdit->clear();
}

void rootSmall::on_delBtn_clicked()
{
    QString id = ui.dellineEdit->text();
    if (!SqlQuery::isInTable(id, type + "_info")) {MsgInterface::show_error("����", "�û�������"); return;}
    if (SqlQuery::delDataById(id, type))
    {
        MsgInterface::show_info("�ɹ�", "ɾ���ɹ�");
        return;
    }
    else {
        MsgInterface::show_error("ʧ��", "ɾ��ʧ��");
        return;
    }
}


void rootSmall::show_tableview()
{
    QSqlDatabase db = SqlQuery::createConnection();
    if (!db.open()) {
        MsgInterface::show_error("����", "���ӷ���������");
        return;
    }
    this->model = new QSqlTableModel(this);
    if (type == "student") {
        ui.tabWidget->setTabText(0,"ѧ��");
        ui.stackedWidget->setCurrentWidget(ui.studentPage);
        model->setTable("student_info");
        ui.stuTableView->setModel(model);
        model->select();
        model->setHeaderData(0, Qt::Horizontal, tr("ѧ��/����"));
        model->setHeaderData(1, Qt::Horizontal, tr("����"));
        model->setHeaderData(2, Qt::Horizontal, tr("����"));
    }
    else if (type == "teacher")
    {
        ui.tabWidget->setTabText(0, "��ʦ");
        model->setTable("teacher_info");
        ui.stackedWidget->setCurrentWidget(ui.teacherPage);
        ui.stuTableView->setModel(model);
        model->select();
        model->setHeaderData(0, Qt::Horizontal, tr("ѧ��/����"));
        model->setHeaderData(1, Qt::Horizontal, tr("����"));
        model->setHeaderData(2, Qt::Horizontal, tr("����"));
    }
    ui.stuTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void rootSmall::setAddPage()
{
    if (type == "student") ui.stackedWidget->setCurrentIndex(1);
    else if (type == "teacher") ui.stackedWidget->setCurrentIndex(0);
    else throw "setAddPage error";
}