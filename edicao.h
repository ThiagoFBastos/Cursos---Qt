#ifndef EDICAO_H
#define EDICAO_H

#include <QMainWindow>
#include "CourseModel.h"
#include "db.h"
#include <QCloseEvent>

namespace Ui {
class Edicao;
}

class Edicao : public QMainWindow
{
    Q_OBJECT

public:
    explicit Edicao(Db *db, Course* course, QWidget *parent = nullptr);
    ~Edicao();

private slots:
    void on_btnCancelar_clicked();

    void on_btnEditar_clicked();

    void on_txtNome_textChanged(const QString &arg1);

    void on_txtURL_textChanged(const QString &arg1);

    void on_dateInicio_dateTimeChanged(const QDateTime &dateTime);

    void on_spinPreco_valueChanged(double arg1);

    void on_txtDescricao_textChanged();

private:
    Ui::Edicao *ui;
    Db *db;
    Course* course = nullptr;

    void closeEvent(QCloseEvent *event) override;
};

#endif // EDICAO_H
