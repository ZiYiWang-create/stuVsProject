#pragma once
#pragma execution_character_set("utf-8")
#include<qsqldatabase.h>
#include<QDebug>
#include<QSqlQuery>
#include "MsgInterface.h"
/* 用于实现数据库的连接，增删改查*/
class SqlQuery
{
public:
    SqlQuery(){}
    // 连接数据库
    static QSqlDatabase createConnection()
    {
        // 打开MySQL   
        QSqlDatabase db;
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");
        db.setDatabaseName("student_manager");
        db.setUserName("root");
        db.setPassword("wangziyi2000");
        return db;
    }

    //登录查询确认
    static bool LoginQuery(QString id, QString pwd, QString type)
    {
        QSqlDatabase db = createConnection();
        if (!db.open()) {
            MsgInterface::show_error("错误", "连接服务器错误");
            return false;
        }
        QSqlQuery query(db);
        QString table_name;
        if (type == "学生") table_name = "student_info";
        else if (type == "教师") table_name = "teacher_info";
        else {
            table_name = "root_user";
        }
        QString str = QString("select * from %1 where id=\"%2\" and pwd=\"%3\";").arg(table_name, id, pwd);
        query.exec(str);
        if (query.next())
        {
            qDebug() << "登录成功";
            query.clear();
            db.close();
            return 1;
        }
        else {
            qDebug() << "登录失败";
            query.clear();
            db.close();
            return 0;
        }
    }

    //判断是否在数据库里
    static bool isInTable(QString id, QString table_name)
    {
        QSqlDatabase db = createConnection();
        if (!db.open()) {
            MsgInterface::show_error("错误", "连接服务器错误");
            return false;
        }
        QSqlQuery query(db);
        QString str = QString("select * from %1 where id=\"%2\";").arg(table_name, id);
        query.exec(str);
        if (query.next())// 如果有一个元素
        {
            db.close();
            return true;
        }
        else
        {
            db.close();
            return false;
        }
    }
    static bool isInTable(QString id, QString name, QString table_name)
    {
        QSqlDatabase db = createConnection();
        if (!db.open()) {
            MsgInterface::show_error("错误", "连接服务器错误");
            return false;
        }
        QSqlQuery query(db);
        QString str = QString("select * from %1 where id=\"%2\" and name=\"%3\";").arg(table_name, id, name);
        query.exec(str);
        if (query.next())// 如果有一个元素
        {
            db.close();
            return true;
        }
        else
        {
            db.close();
            return false;
        }
    }
    
    //更新密码
    static bool upgradePwd(QString id, QString new_pwd, QString table_name)
    {
        QSqlDatabase db = createConnection();
        if (!db.open()) {
            MsgInterface::show_error("错误", "连接服务器错误");
            return false;
        }
        QSqlQuery query(db);
        QString str = QString("update %1 set pwd=\"%2\" where id=\"%3\";").arg(table_name, new_pwd, id);
        query.exec(str);
        db.close();
        return true;
    }

    //添加人员
    static bool addStudent(QString id, QString name, QString sex, QString navite,QString tel,QString college, QString major, QString className,QString dormitory,QString pwd="123456")
    {
        QSqlDatabase db = createConnection();
        if (!db.open()) {
            MsgInterface::show_error("错误", "连接服务器错误");
            return false;
        }
        QString table_name = "student_info";
        QSqlQuery query(db);
        QString str= QString("insert into student_info values(\"" + id + "\",\""+ name +"\",\""+ sex + "\",\""+ navite +"\",\""+ tel +"\",\""+ college +"\",\""+ major +"\",\""+ className +"\",\""+ dormitory + "\",\""+pwd + "\")");
        if(query.exec(str)){
            db.close();
            return true;
        }
        else {
            db.close();
            return false;
        }
    }
    static bool addTeacher(QString id, QString name, QString sex, QString navite, QString tel, QString college, QString major, QString title, QString pwd="123465")
    {
        QSqlDatabase db = createConnection();
        if (!db.open()) {
            MsgInterface::show_error("错误", "连接服务器错误");
            return false;
        }
        QString table_name = "teacher_info";
        QSqlQuery query(db);
        QString str = QString("insert into teacher_info values(\"" + id + "\",\"" + name + "\",\"" + sex + "\",\"" + navite + "\",\"" + tel + "\",\"" + college + "\",\"" + major + "\",\"" + title + "\",\"" + pwd + "\")");
        if (query.exec(str)) {
            db.close();
            return true;
        }
        else {
            db.close();
            return false;
        }
    }

    //通过id删除数据
    static bool delDataById(QString id,QString type)
    {
        QSqlDatabase db = createConnection();
        if (!db.open()) {
            MsgInterface::show_error("错误", "连接服务器错误");
            return false;
        }
        QString table_name;
        if (type == "student") table_name = "student_info";
        else if (type == "teacher") table_name = "teacher_info";
        else {
            throw("函数错误");
        }
        QString str = QString("delete from %1 where id=\"%2\";").arg(table_name, id);
        if (type == "student") {
            QSqlQuery query(db);
            if (!query.exec(QString("delete from scores where studentId=\"%1\";").arg(id))) { MsgInterface::show_error("错误", "分数删除错误"); query.clear(); return false;   }
        }
        QSqlQuery query(db);
        if (query.exec(str)) {
            db.close();
            return true;
        }
        else {
            db.close();
            return false;
        }
    }

};

