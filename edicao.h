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
    explicit Edicao(Course* course, QWidget *parent = nullptr);
    ~Edicao();

private slots:
    void on_btnCancelar_clicked();

    void on_btnEditar_clicked();

private:
    Ui::Edicao *ui;
    Course* course = nullptr;

    void closeEvent(QCloseEvent *event) override;
};

#endif // EDICAO_H
