#ifndef CURSO_H
#define CURSO_H

#include <QMainWindow>
#include <QCloseEvent>
#include "db.h"
#include <memory>

namespace Ui {
class Curso;
}

class Curso : public QMainWindow
{
    Q_OBJECT

public:
    explicit Curso(Db *db, QWidget *parent = nullptr);
    ~Curso();

private slots:
    void on_btnCancelar_clicked();

    void on_btnCadastrar_clicked();

    void on_txtNome_textChanged(const QString &arg1);

    void on_txtURL_textChanged(const QString &arg1);

    void on_dateInicio_dateTimeChanged(const QDateTime &dateTime);

    void on_spinPreco_valueChanged(double arg1);

    void on_txtDescricao_textChanged();

private:
    Ui::Curso *ui;
    Db *db;

    void closeEvent(QCloseEvent *event) override;
};

#endif // CURSO_H
