#include "listagem.h"
#include "ui_listagem.h"
#include <QCheckBox>
#include <QMessageBox>

Listagem::Listagem(Db *db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Listagem)
    , db(db)
{
    ui->setupUi(this);

    cursos = db->getCourses();

    for(int i = 0; i < (int)cursos.size(); ++i)
    {
        auto& curso = cursos[i];

        ui->tableCursos->insertRow(i);

        auto idCell = new QTableWidgetItem(QString::number(curso.getId()));
        auto nomeCell = new QTableWidgetItem(curso.getNome());
        auto urlCell = new QTableWidgetItem(curso.getURL());
        auto descricaoCell = new QTableWidgetItem(curso.getDescricao());
        auto dataInicioCell = new QTableWidgetItem(curso.getDataInicio().toString());
        auto precoCell = new QTableWidgetItem(QString::number(curso.getPreco()));
        auto isCompletedCell = new QTableWidgetItem(curso.getIsCompleted() ? "completo" : "incompleto");

        idCell->setFlags(idCell->flags() ^ Qt::ItemIsEditable);
        idCell->setTextAlignment(Qt::AlignCenter);

        nomeCell->setFlags(nomeCell->flags() ^ Qt::ItemIsEditable);
        nomeCell->setTextAlignment(Qt::AlignCenter);

        urlCell->setFlags(urlCell->flags() ^ Qt::ItemIsEditable);
        urlCell->setTextAlignment(Qt::AlignCenter);

        descricaoCell->setFlags(descricaoCell->flags() ^ Qt::ItemIsEditable);
        descricaoCell->setTextAlignment(Qt::AlignCenter);

        dataInicioCell->setFlags(dataInicioCell->flags() ^ Qt::ItemIsEditable);
        dataInicioCell->setTextAlignment(Qt::AlignCenter);

        precoCell->setFlags(precoCell->flags() ^ Qt::ItemIsEditable);
        precoCell->setTextAlignment(Qt::AlignCenter);

        isCompletedCell->setFlags(isCompletedCell->flags() ^ Qt::ItemIsEditable);
        isCompletedCell->setTextAlignment(Qt::AlignCenter);

        ui->tableCursos->setItem(i, 0, idCell);
        ui->tableCursos->setItem(i, 1, nomeCell);
        ui->tableCursos->setItem(i, 2, urlCell);
        ui->tableCursos->setItem(i, 3, descricaoCell);
        ui->tableCursos->setItem(i, 4, dataInicioCell);
        ui->tableCursos->setItem(i, 5, precoCell);
        ui->tableCursos->setItem(i, 6, isCompletedCell);
    }
}

Listagem::~Listagem()
{
    delete ui;
}

void Listagem::closeEvent(QCloseEvent *event)
{
    this->parentWidget()->show();
}

void Listagem::on_btnExcluir_clicked()
{
    QModelIndexList selectedRows = ui->tableCursos->selectionModel()->selectedRows();

    if(selectedRows.size() == 1)
    {
        auto selectedRow = selectedRows.front();
        int row = selectedRow.row();
        QTableWidgetItem *item = ui->tableCursos->item(row, 0);
        int id = item->text().toInt();
        cursos.erase(cursos.begin() + row);
        db->deleteCourse(id);
        ui->tableCursos->removeRow(row);
    }
}


void Listagem::on_btnEditar_clicked()
{
    QModelIndexList selectedRows = ui->tableCursos->selectionModel()->selectedRows();

    if(selectedRows.size() == 1)
    {
        auto selectedRow = selectedRows.front();
        int row = selectedRow.row();

        if(edicao.get())
            edicao.release();

        edicao = std::unique_ptr<Edicao>(new Edicao(db, &cursos[row], this));

        edicao.get()->show();
        hide();
    }
}

