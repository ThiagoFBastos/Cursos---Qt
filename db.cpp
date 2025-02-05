#include "db.h"
#include <QDir>
#include <QDebug>
#include <QSqlRecord>

Db::Db(): query {new QSqlQueryModel()}
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::currentPath() + QDir::separator() +  "courses.db");
    db.open();

    if(!db.isOpen())
        throw QSqlError();

    command = new QSqlQuery(db);

    initDB();
}

void Db::initDB()
{
    const QString table = "create table if not exists courses (id integer primary key, nome varchar(256), url varchar(256), descricao varchar(1000), is_completed integer default 0, preco real, data_inicio date)";
    if(!command->exec(table))
    {
        qCritical() << "a tabela não pôde ser criada\n";
        throw QSqlError();
    }
}

Db::~Db()
{
    db.close();
    delete command;
    delete query;
}

void Db::addCourse(const Course& course)
{
    const QString insert = "insert into courses (id, nome, url, data_inicio, descricao, preco) values (NULL, :nome, :url, :data_inicio, :descricao, :preco)";

    if(!command->prepare(insert))
    {
        qCritical() << "a inserção não pôde ser preparada\n";
        throw QSqlError();
    }

    command->bindValue(":nome", course.getNome());
    command->bindValue(":url", course.getURL());
    command->bindValue(":data_inicio", course.getDataInicio());
    command->bindValue(":descricao", course.getDescricao());
    command->bindValue(":preco", course.getPreco());

    if(!command->exec())
    {
        qCritical() << "a inserção não pôde ser feita\n";
        throw QSqlError();
    }
}

void Db::updateCourse(int id, const Course& course)
{
    const QString update = "update courses set nome = :nome, url = :url, descricao = :descricao, is_completed = :is_completed, preco = :preco, data_inicio = :data_inicio where id = :id";

    if(!command->prepare(update))
    {
        qCritical() << "a inserção não pôde ser preparada\n";
        throw QSqlError();
    }

    command->bindValue(":nome", course.getNome());
    command->bindValue(":url", course.getURL());
    command->bindValue(":descricao", course.getDescricao());
    command->bindValue(":is_completed", course.getIsCompleted());
    command->bindValue(":preco", course.getPreco());
    command->bindValue(":data_inicio", course.getDataInicio());
    command->bindValue(":id", course.getId());

    if(!command->exec())
    {
        qCritical() << "a atualização não pôde ser feita\n";
        throw QSqlError();
    }
}

void Db::deleteCourse(int id)
{
    const QString deleteQuery = "delete from courses where id = :id";

    if(!command->prepare(deleteQuery))
    {
        qCritical() << "o comando delete não pode ser preparado\n";
        throw QSqlError();
    }

    command->bindValue(":id", id);

    if(!command->exec())
    {
        qCritical() << "a remoção do registro com id: " << id << " não pôde ser feita\n";
        throw QSqlError();
    }
}

std::vector<Course> Db::getCourses()
{
    query->setQuery("SELECT * from courses", db);

    if(query->lastError().isValid())
    {
        qCritical() << "a query é inválida\n";
        throw QSqlError();
    }

    std::vector<Course> courses;

    for(int i = 0; i < query->rowCount(); ++i)
    {
        QSqlRecord record = query->record(i);
        Course course;

        course.setId(record.value("id").toInt());
        course.setNome(record.value("nome").toString());
        course.setDescricao(record.value("descricao").toString());
        course.setURL(record.value("url").toString());
        course.setPreco(record.value("preco").toDouble());
        course.setIsCompleted(record.value("is_completed").toBool());
        course.setDataInicio(record.value("data_inicio").toDate());

        courses.push_back(course);
    }

    return courses;
}
