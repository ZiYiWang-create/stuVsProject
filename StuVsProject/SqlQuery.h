#pragma once
#pragma execution_character_set("utf-8")
#include<qsqldatabase.h>
#include<QDebug>
#include<QSqlQuery>
#include "MsgInterface.h"
/* ����ʵ�����ݿ�����ӣ���ɾ�Ĳ�*/
class SqlQuery
{
public:
    SqlQuery(){}
    // �������ݿ�
    static QSqlDatabase createConnection()
    {
        // ��MySQL   
        QSqlDatabase db;
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");
        db.setDatabaseName("student_manager");
        db.setUserName("root");
        db.setPassword("wangziyi2000");
        return db;
    }

    //��¼��ѯȷ��
    static bool LoginQuery(QString id, QString pwd, QString type)
    {
        QSqlDatabase db = createConnection();
        if (!db.open()) {
            MsgInterface::show_error("����", "���ӷ���������");
            return false;
        }
        QSqlQuery query(db);
        QString table_name;
        if (type == "ѧ��") table_name = "student_info";
        else if (type == "��ʦ") table_name = "teacher_info";
        else {
            table_name = "root_user";
        }
        QString str = QString("select * from %1 where id=\"%2\" and pwd=\"%3\";").arg(table_name, id, pwd);
        query.exec(str);
        if (query.next())
        {
            qDebug() << "��¼�ɹ�";
            query.clear();
            db.close();
            return 1;
        }
        else {
            qDebug() << "��¼ʧ��";
            query.clear();
            db.close();
            return 0;
        }
    }

    //�ж��Ƿ������ݿ���
    static bool isInTable(QString id, QString table_name)
    {
        QSqlDatabase db = createConnection();
        if (!db.open()) {
            MsgInterface::show_error("����", "���ӷ���������");
            return false;
        }
        QSqlQuery query(db);
        QString str = QString("select * from %1 where id=\"%2\";").arg(table_name, id);
        query.exec(str);
        if (query.next())// �����һ��Ԫ��
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
            MsgInterface::show_error("����", "���ӷ���������");
            return false;
        }
        QSqlQuery query(db);
        QString str = QString("select * from %1 where id=\"%2\" and name=\"%3\";").arg(table_name, id, name);
        query.exec(str);
        if (query.next())// �����һ��Ԫ��
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
    static bool isInTable_standard(QString field,QString field_value,QString table_name)
    {
        QSqlDatabase db = createConnection();
        if (!db.open()) {
            MsgInterface::show_error("����", "���ӷ���������");
            return false;
        }
        QString str = QString("select * from %1 where %2=\"%3\";").arg(table_name, field, field_value);
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
    static bool isInTable_standard(QString field, QString field_value, QString field2, QString field2_value, QString table_name)
    {
        QSqlDatabase db = createConnection();
        if (!db.open()) {
            MsgInterface::show_error("����", "���ӷ���������");
            return false;
        }
        QString str = QString("select * from %1 where %2=\"%3\" and %4=\"%5\";").arg(table_name, field, field_value,field2,field2_value);
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
    //��������
    static bool upgradePwd(QString id, QString new_pwd, QString table_name)
    {
        QSqlDatabase db = createConnection();
        if (!db.open()) {
            MsgInterface::show_error("����", "���ӷ���������");
            return false;
        }
        QSqlQuery query(db);
        QString str = QString("update %1 set pwd=\"%2\" where id=\"%3\";").arg(table_name, new_pwd, id);
        query.exec(str);
        db.close();
        return true;
    }

    //�����Ա
    static bool addStudent(QString id, QString name, QString sex, QString navite,QString tel,QString college, QString major, QString className,QString dormitory,QString pwd="123456")
    {
        QSqlDatabase db = createConnection();
        if (!db.open()) {
            MsgInterface::show_error("����", "���ӷ���������");
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
            MsgInterface::show_error("����", "���ӷ���������");
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

    //ͨ��idɾ������
    static bool delDataById(QString id,QString type)
    {
        QSqlDatabase db = createConnection();
        if (!db.open()) {
            MsgInterface::show_error("����", "���ӷ���������");
            return false;
        }
        QString table_name;
        if (type == "student") table_name = "student_info";
        else if (type == "teacher") table_name = "teacher_info";
        else {
            throw("��������");
        }
        QString str = QString("delete from %1 where id=\"%2\";").arg(table_name, id);
        if (type == "student") {
            QSqlQuery query(db);
            if (!query.exec(QString("delete from scores where studentId=\"%1\";").arg(id))) { MsgInterface::show_error("����", "����ɾ������"); query.clear(); return false;   }
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

    //score���
    static bool addScore(QString id, QString courseId, QString courseName, QString usualScore, QString experimentScore, QString paperScore,QString score)
    {
        QSqlDatabase db = createConnection();
        if (!db.open()) {
            MsgInterface::show_error("����", "���ӷ���������");
            return false;
        }
        //�����ۺϳɼ�
        float actgrade = 0;
        float d_usualScore = usualScore.toDouble();
        float d_paperScore = paperScore.toDouble();
        float d_experimentScore = experimentScore.toDouble();
        if (d_experimentScore == -1)
            actgrade = d_usualScore * 0.3 + d_paperScore * 0.7;
        //��ʵ��
        else
            actgrade = d_usualScore * 0.15 + d_experimentScore * 0.15 + d_paperScore * 0.7;
        float actscore = 0;
        //ʵ��ѧ��
        if (actgrade > 90 && actgrade <= 100) actscore = score.toDouble();
        else if (actgrade > 80 && actgrade <= 90) actscore = score.toDouble() * 0.8;
        else if (actgrade > 70 && actgrade <= 80) actscore = score.toDouble() * 0.75;
        else if (actgrade > 60 && actgrade <= 70) actscore = score.toDouble() * 0.6;
        else actscore = 0;

        QString str = QString("insert into scores values(\"" + id + "\",\"" + courseId + "\",\"" + courseName +
            "\"," + usualScore + "," + experimentScore + "," + paperScore + "," + score + "," + 
            QString::number(actscore) +","+ QString::number(actgrade) + ");");
        
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

    //�޸ĳɼ�
    static bool updateScore(QString id, QString courseId, QString courseName, QString usualScore, QString experimentScore, QString paperScore, QString score)
    {
        QSqlDatabase db = createConnection();
        if (!db.open()) {
            MsgInterface::show_error("����", "���ӷ���������");
            return false;
        }
        //�����ۺϳɼ�
        float actgrade = 0;
        float d_usualScore = usualScore.toDouble();
        float d_paperScore = paperScore.toDouble();
        float d_experimentScore = experimentScore.toDouble();
        if (d_experimentScore == -1)
            actgrade = d_usualScore * 0.3 + d_paperScore * 0.7;
        //��ʵ��
        else
            actgrade = d_usualScore * 0.15 + d_experimentScore * 0.15 + d_paperScore * 0.7;
        float actscore = 0;
        //ʵ��ѧ��
        if (actgrade > 90 && actgrade <= 100) actscore = score.toDouble();
        else if (actgrade > 80 && actgrade <= 90) actscore = score.toDouble() * 0.8;
        else if (actgrade > 70 && actgrade <= 80) actscore = score.toDouble() * 0.75;
        else if (actgrade > 60 && actgrade <= 70) actscore = score.toDouble() * 0.6;
        else actscore = 0;

        QString str = QString("update scores set usualPerformance=%1,experiment=%2,paperScore=%3,actualScore=%4,"
            "actualGrade=%5 where studentId=\"%6\" and courseId=\"%7\";").arg(usualScore, experimentScore, paperScore, QString::number(actscore), QString::number(actgrade), id, courseId);

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
    
    //ѧ���Լ��޸���Ϣ
    static bool updateStuInfo(QString id, QString name, QString sex, QString navite, QString tel, QString college, QString major, QString className, QString dormitory)
    {
        QSqlDatabase db = createConnection();
        if (!db.open()) {
            MsgInterface::show_error("����", "���ӷ���������");
            return false;
        }
        QSqlQuery query(db);
        QString str = QString("update student_info set name=\"") + name + QString("\",sex=\"") + sex + QString("\",native=\"") + navite + QString("\",tel=\"") + tel +
            QString("\",college=\"") + college + QString("\",major=\"") + major + QString("\",class=\"") + className + QString("\",dormitory=\"") + dormitory + 
            QString("\" where id=\"%1\";").arg(id);
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

