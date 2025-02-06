#include "edicao.h"
#include "ui_edicao.h"
#include <QMessageBox>

Edicao::Edicao(Db *db, Course* course, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Edicao)
    , course(course)
    , db(db)
{
    ui->setupUi(this);

    ui->txtNome->setText(course->getNome());
    ui->txtURL->setText(course->getURL());
    ui->txtDescricao->setText(course->getDescricao());
    ui->spinPreco->setValue(course->getPreco());
    ui->dateInicio->setDate(course->getDataInicio());
    ui->checkCompleto->setChecked(course->getIsCompleted());
}

Edicao::~Edicao()
{
    delete ui;
}


void Edicao::on_btnCancelar_clicked()
{
    ui->txtNome->setText(course->getNome());
    ui->txtURL->setText(course->getURL());
    ui->txtDescricao->setText(course->getDescricao());
    ui->spinPreco->setValue(course->getPreco());
    ui->dateInicio->setDate(course->getDataInicio());
    ui->checkCompleto->setChecked(course->getIsCompleted());
}


void Edicao::on_btnEditar_clicked()
{
    course->setNome(ui->txtNome->text());
    course->setDescricao(ui->txtDescricao->toPlainText());
    course->setIsCompleted(ui->checkCompleto->isChecked());
    course->setDataInicio(ui->dateInicio->date());
    course->setPreco(ui->spinPreco->value());
    course->setURL(ui->txtURL->text());

    if(!course->isValid())
    {
        QMessageBox::warning(this, "validação", "os dados inseridos não estão com a validação correta");
        return;
    }

    db->updateCourse(course->getId(), *course);

    QMessageBox::about(this, "edição", "os dados foram alterados com suceso");
}

void Edicao::closeEvent(QCloseEvent *event)
{
    this->parentWidget()->close();
}
