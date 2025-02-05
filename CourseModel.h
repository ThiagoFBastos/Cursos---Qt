#ifndef COURSEMODEL_H
#define COURSEMODEL_H

#include <QString>
#include <QDate>
#include <QUrl>

class Course
{
private:
    int id = 0;
    QString nome = "";
    QString descricao = "";
    QString URL = "";
    QDate dataInicio;
    double preco = 0;
    bool isCompleted = false;

    bool nomeValido() const
    {
        return nome.length() >= 5;
    }

    bool descricaoValida() const
    {
        return descricao.length() >= 50;
    }

    bool URLValida() const
    {
        QUrl url(URL);
        return url.isValid();
    }

    bool dataInicioValida() const
    {
        return dataInicio > QDate(1999, 5, 17);
    }

    bool precoValido() const
    {
        return preco >= 0;
    }
public:
    Course() = default;

    int getId() const
    {
        return id;
    }

    void setId(int id)
    {
        this->id = id;
    }

    QString getNome() const
    {
        return nome;
    }

    void setNome(QString nome)
    {
        this->nome = nome;
    }

    QString getDescricao() const
    {
        return descricao;
    }

    void setDescricao(QString descricao)
    {
        this->descricao = descricao;
    }

    QString getURL() const
    {
        return URL;
    }

    void setURL(QString URL)
    {
        this->URL = URL;
    }

    QDate getDataInicio() const
    {
        return dataInicio;
    }

    void setDataInicio(QDate dataInicio)
    {
        this->dataInicio = dataInicio;
    }

    double getPreco() const
    {
        return preco;
    }

    void setPreco(double preco)
    {
        this->preco = preco;
    }

    bool getIsCompleted() const
    {
        return isCompleted;
    }

    void setIsCompleted(bool isCompleted)
    {
        this->isCompleted = isCompleted;
    }

    bool isValid() const
    {
        return nomeValido() && descricaoValida() && URLValida() && dataInicioValida() && precoValido();
    }
};

#endif // COURSEMODEL_H
