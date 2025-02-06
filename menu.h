#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "curso.h"
#include "listagem.h"
#include <memory>
#include "db.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Menu;
}
QT_END_NAMESPACE

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_btnCadastrar_clicked();

    void on_btnListar_clicked();

private:
    Ui::Menu *ui;
    Db *db = nullptr;
    std::unique_ptr<Curso> curso {};
    std::unique_ptr<Listagem> listagem {};
};
#endif // MENU_H
