#ifndef LISTAGEM_H
#define LISTAGEM_H

#include <QMainWindow>
#include <QCloseEvent>
#include "CourseModel.h"
#include <vector>
#include "edicao.h"
#include <memory>

namespace Ui {
class Listagem;
}

class Listagem : public QMainWindow
{
    Q_OBJECT

public:
    explicit Listagem(QWidget *parent = nullptr);
    ~Listagem();

private slots:

    void on_btnExcluir_clicked();

    void on_btnEditar_clicked();

private:
    Ui::Listagem *ui;
    Db *db = nullptr;
    std::vector<Course> cursos;
    std::unique_ptr<Edicao> edicao {};
    void closeEvent(QCloseEvent *event) override;
};

#endif // LISTAGEM_H
