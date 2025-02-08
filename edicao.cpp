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


void Edicao::on_btnEditar_clicked()
{
    QMessageBox::StandardButton choice = QMessageBox::question(this, "atualização", "deseja realmente atualizar esses dados", QMessageBox::Yes | QMessageBox::No);

    if(choice == QMessageBox::No)
        return;

    Course newCourse;

    newCourse.setId(course->getId());
    newCourse.setNome(ui->txtNome->text());
    newCourse.setDescricao(ui->txtDescricao->toPlainText());
    newCourse.setIsCompleted(ui->checkCompleto->isChecked());
    newCourse.setDataInicio(ui->dateInicio->date());
    newCourse.setPreco(ui->spinPreco->value());
    newCourse.setURL(ui->txtURL->text());

    auto [isValid, errors] = newCourse.isValid();

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
        QMessageBox::warning(this, "validação", "os dados inseridos não estão com a validação correta");
        return;
    }

    db->updateCourse(course->getId(), newCourse);

    *course = newCourse;

    QMessageBox::about(this, "edição", "os dados foram alterados com suceso");
}

void Edicao::closeEvent(QCloseEvent *event)
{
    this->parentWidget()->close();
}

void Edicao::on_txtNome_textChanged(const QString &arg1)
{
    ui->txtNome->setStyleSheet("QLineEdit {background-color: white;}");
    ui->txtNome->setToolTip("Nome do curso");
}


void Edicao::on_txtURL_textChanged(const QString &arg1)
{
    ui->txtURL->setStyleSheet("QLineEdit {background-color: white; color: blue; text-decoration: underline;}");
    ui->txtURL->setToolTip("https://youtube.com");
}


void Edicao::on_dateInicio_dateTimeChanged(const QDateTime &dateTime)
{
    ui->dateInicio->setStyleSheet("QDateEdit {	background-color: white;}");
    ui->dateInicio->setToolTip("Data de inicio");
}


void Edicao::on_spinPreco_valueChanged(double arg1)
{
    ui->spinPreco->setStyleSheet("QDoubleSpinBox {background-color: white; }");
    ui->spinPreco->setToolTip("Preço do curso");
}


void Edicao::on_txtDescricao_textChanged()
{
    ui->txtDescricao->setStyleSheet("QTextEdit {background-color: white; }");
    ui->txtDescricao->setToolTip("Descrição do curso");
}

