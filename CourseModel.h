#ifndef COURSEMODEL_H
#define COURSEMODEL_H

#include <QString>
#include <QDate>
#include <QUrl>
#include <utility>
#include <map>

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
        return nome.length() >= 5 && nome.length() <= 256;
    }

    bool descricaoValida() const
    {
        return descricao.length() >= 50 && descricao.length() <= 1000;
    }

    bool URLValida() const
    {
        QUrl url(URL);
        return url.isValid() && URL.length() <= 256;
    }

    bool dataInicioValida() const
    {
        return dataInicio > QDate(1999, 5, 17);
    }

    bool precoValido() const
    {
        return preco >= 0 && preco <= 5000;
    }
public:
    Course() = default;

    Course(const Course& other)
    {
        id = other.id;
        nome = other.nome;
        descricao = other.descricao;
        URL = other.URL;
        preco = other.preco;
        isCompleted = other.isCompleted;
        dataInicio = other.dataInicio;
    }

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

    std::pair<bool, std::map<QString, QString>> isValid() const
    {
        bool result = true;
        std::map<QString, QString> errors;

        if(!nomeValido())
        {
            result = false;
            errors["nome"] = "o nome deve ter entre 5 e 256 caracteres";
        }

        if(!descricaoValida())
        {
            result = false;
            errors["descricao"] = "a descrição deve conter entre 50 e 1000 caracteres";
        }

        if(!URLValida())
        {
            result = false;
            errors["URL"] = "a url deve ser válida";
        }

        if(!precoValido())
        {
            result = false;
            errors["preco"] = "o preço deve ser estar entre R$ 0,00 e R$ 5000,00";
        }

        if(!dataInicioValida())
        {
            result = false;
            errors["data_inicio"] = "a data de inicio deve ser depois de 17/05/1999";
        }

        return {result, errors};
    }
};

#endif // COURSEMODEL_H
