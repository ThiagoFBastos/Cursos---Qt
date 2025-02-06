#include "menu.h"
#include "./ui_menu.h"

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
    , db(new Db)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;

    if(db)
    {
        delete db;
        db = nullptr;
    }
}

void Menu::on_btnCadastrar_clicked()
{
    if(curso.get())
        curso.release();

    curso = std::unique_ptr<Curso>(new Curso(db, this));
    curso.get()->show();
    hide();
}


void Menu::on_btnListar_clicked()
{
    if(listagem.get())
        listagem.release();

    listagem = std::unique_ptr<Listagem>(new Listagem(db, this));
    listagem.get()->show();
    hide();
}

