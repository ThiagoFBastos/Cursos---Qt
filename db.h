#ifndef DB_H
#define DB_H

#include <QSql>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include "CourseModel.h"
#include <vector>

class Db
{
private:
    QSqlDatabase db;
    QSqlQuery *command = nullptr;
    QSqlQueryModel *query = nullptr;
    void initDB();
public:
    Db();
    ~Db();
    void closeConnection();
    void addCourse(const Course& course);
    void updateCourse(int id, const Course& course);
    void deleteCourse(int id);
    std::vector<Course> getCourses();
};

#endif // DB_H
