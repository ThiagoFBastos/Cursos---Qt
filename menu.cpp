#include "menu.h"
#include "./ui_menu.h"

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_btnCadastrar_clicked()
{
    if(curso.get())
        curso.release();

    curso = std::unique_ptr<Curso>(new Curso(this));
    curso.get()->show();
    hide();
}


void Menu::on_btnListar_clicked()
{
    if(listagem.get())
        listagem.release();

    listagem = std::unique_ptr<Listagem>(new Listagem(this));
    listagem.get()->show();
    hide();
}

