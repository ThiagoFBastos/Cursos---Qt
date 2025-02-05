#include "curso.h"
#include "ui_curso.h"
#include "CourseModel.h"
#include <vector>
#include <QMessageBox>

Curso::Curso(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Curso)
    , db(new Db)
{
    ui->setupUi(this);
}

Curso::~Curso()
{
    delete ui;
    if(db) delete db;
}

void Curso::on_btnCancelar_clicked()
{
    ui->txtNome->setText("");
    ui->txtURL->setText("");
    ui->txtDescricao->setText("");
    ui->spinPreco->setValue(0);
    ui->dateInicio->setDate(QDate(2000, 1, 1));
}

void Curso::closeEvent(QCloseEvent *event)
{
    this->parentWidget()->show();
}

void Curso::on_btnCadastrar_clicked()
{
    Course course;

    course.setNome(ui->txtNome->text());
    course.setURL(ui->txtURL->text());
    course.setDescricao(ui->txtDescricao->toPlainText());
    course.setPreco(ui->spinPreco->value());
    course.setDataInicio(ui->dateInicio->date());

    if(!course.isValid())
    {
        QMessageBox::warning(this, "validação", "os dados inseridos não são válidos");
        return;
    }

    db->addCourse(course);

    QMessageBox::information(this, "cadastro", "o curso foi cadastrado com sucesso!");
}

