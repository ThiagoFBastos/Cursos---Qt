#include "curso.h"
#include "ui_curso.h"
#include "CourseModel.h"
#include <QMessageBox>

Curso::Curso(Db *db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Curso)
    , db(db)
{
    ui->setupUi(this);
}

Curso::~Curso()
{
    delete ui;
}

void Curso::on_btnCancelar_clicked()
{
    ui->txtNome->setText("");
    ui->txtURL->setText("");
    ui->txtDescricao->setText("");
    ui->spinPreco->setValue(0);
    ui->dateInicio->setDate(QDate(2000, 1, 1));

    ui->txtNome->setStyleSheet("QLineEdit {background-color: white;}");
    ui->txtNome->setToolTip("Nome do curso");

    ui->txtURL->setStyleSheet("QLineEdit {background-color: white; color: blue; text-decoration: underline;}");
    ui->txtURL->setToolTip("https://youtube.com");

    ui->dateInicio->setStyleSheet("QDateEdit {	background-color: white;}");
    ui->dateInicio->setToolTip("Data de inicio");

    ui->spinPreco->setStyleSheet("QDoubleSpinBox {background-color: white; }");
    ui->spinPreco->setToolTip("Preço do curso");

    ui->txtDescricao->setStyleSheet("QTextEdit {background-color: white; }");
    ui->txtDescricao->setToolTip("Descrição do curso");
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

    auto [isValid, errors] = course.isValid();

    if(errors.count("nome"))
    {
        ui->txtNome->setStyleSheet("QLineEdit {background-color: white; border: 1px solid red;}");
        ui->txtNome->setToolTip(errors["nome"]);
    }

    if(errors.count("URL"))
    {
        ui->txtURL->setStyleSheet("QLineEdit {background-color: white; border: 1px solid red; color: blue; text-decoration: underline;}");
        ui->txtURL->setToolTip(errors["URL"]);
    }

    if(errors.count("descricao"))
    {
        ui->txtDescricao->setStyleSheet("QTextEdit {background-color: white; border: 1px solid red;}");
        ui->txtDescricao->setToolTip(errors["descricao"]);
    }

    if(errors.count("preco"))
    {
        ui->spinPreco->setStyleSheet("QDoubleSpinBox {background-color: white; border: 1px solid red;}");
        ui->spinPreco->setToolTip(errors["preco"]);
    }

    if(errors.count("data_inicio"))
    {
        ui->dateInicio->setStyleSheet("QDateEdit {	background-color: white; border: 1px solid red;}");
        ui->dateInicio->setToolTip(errors["data_inicio"]);
    }

    if(!isValid)
    {
        QMessageBox::warning(this, "validação", "os dados inseridos não são válidos");
        return;
    }

    db->addCourse(course);

    QMessageBox::information(this, "cadastro", "o curso foi cadastrado com sucesso!");
}


void Curso::on_txtNome_textChanged(const QString &arg1)
{
    ui->txtNome->setStyleSheet("QLineEdit {background-color: white;}");
    ui->txtNome->setToolTip("Nome do curso");
}


void Curso::on_txtURL_textChanged(const QString &arg1)
{
    ui->txtURL->setStyleSheet("QLineEdit {background-color: white; color: blue; text-decoration: underline;}");
    ui->txtURL->setToolTip("https://youtube.com");
}


void Curso::on_dateInicio_dateTimeChanged(const QDateTime &dateTime)
{
    ui->dateInicio->setStyleSheet("QDateEdit {	background-color: white;}");
    ui->dateInicio->setToolTip("Data de inicio");
}


void Curso::on_spinPreco_valueChanged(double arg1)
{
    ui->spinPreco->setStyleSheet("QDoubleSpinBox {background-color: white; }");
    ui->spinPreco->setToolTip("Preço do curso");
}

void Curso::on_txtDescricao_textChanged()
{
    ui->txtDescricao->setStyleSheet("QTextEdit {background-color: white; }");
    ui->txtDescricao->setToolTip("Descrição do curso");
}

