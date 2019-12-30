#pragma once
#pragma execution_character_set("utf-8")
#include<QMessageBox>
class  MsgInterface {
public:
    void static show_error(QString title, QString waring) {
        QMessageBox* msg = new QMessageBox(QMessageBox::Critical, title, waring,
            QMessageBox::Ok | QMessageBox::No);
        msg->setAttribute(Qt::WA_DeleteOnClose);
        msg->show();
    }
    void static show_info(QString title, QString content) {
        QMessageBox* msg = new QMessageBox(QMessageBox::Information, title, content,
            QMessageBox::Ok | QMessageBox::No);
        msg->setAttribute(Qt::WA_DeleteOnClose);
        msg->show();
    }
};