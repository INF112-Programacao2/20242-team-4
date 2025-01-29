#include "janela_competicao.h"
#include "ui_janela_competicao.h"

janela_competicao::janela_competicao(int competicaoNivel, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_competicao)
    , nivel(competicaoNivel)
{
    ui->setupUi(this);

    conexao = Conexao::getInstance();

    if (nivel == 1) {
        ui->_txt_titulo->setText("Iniciante");

        QSqlQuery query(conexao->getConexao());
        query.prepare("SELECT u.user_nome, c.user_pontuacao "
                      "FROM table_comp_iniciantes c "
                      "JOIN table_usuario u ON c.user_id = u.user_id "
                      "ORDER BY c.user_pontuacao DESC");

        if (query.exec()) {
            ui->_tw_ranking->setColumnCount(2);
            ui->_tw_ranking->setHorizontalHeaderLabels({"Nome", "Pontuação"});

            int cont = 0;
            while(query.next()) {
                ui->_tw_ranking->insertRow(cont);
                ui->_tw_ranking->setItem(cont, 0, new QTableWidgetItem(query.value("user_nome").toString()));
                ui->_tw_ranking->setItem(cont, 1, new QTableWidgetItem(query.value("user_pontuacao").toString()));
                ui->_tw_ranking->setRowHeight(cont, 40);
                cont++;
            }

            ui->_tw_ranking->setColumnWidth(0, 250);
            ui->_tw_ranking->setColumnWidth(1, 240);
            ui->_tw_ranking->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->_tw_ranking->verticalHeader()->setVisible(false);
        } else {
            QMessageBox::warning(this, "ERRO", "Erro ao pesquisar competidores!");
            qDebug() << "Erro na query:" << query.lastError().text();
        }
    } else if (nivel == 2) {
        ui->_txt_titulo->setText("Amador");

        QSqlQuery query(conexao->getConexao());
        query.prepare("SELECT u.user_nome, c.user_pontuacao "
                      "FROM table_comp_amador c "
                      "JOIN table_usuario u ON c.user_id = u.user_id "
                      "ORDER BY c.user_pontuacao DESC");

        if (query.exec()) {
            ui->_tw_ranking->setColumnCount(2);
            ui->_tw_ranking->setHorizontalHeaderLabels({"Nome", "Pontuação"});

            int cont = 0;
            while(query.next()) {
                ui->_tw_ranking->insertRow(cont);
                ui->_tw_ranking->setItem(cont, 0, new QTableWidgetItem(query.value("user_nome").toString()));
                ui->_tw_ranking->setItem(cont, 1, new QTableWidgetItem(query.value("user_pontuacao").toString()));
                ui->_tw_ranking->setRowHeight(cont, 40);
                cont++;
            }

            ui->_tw_ranking->setColumnWidth(0, 250);
            ui->_tw_ranking->setColumnWidth(1, 240);
            ui->_tw_ranking->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->_tw_ranking->verticalHeader()->setVisible(false);
        } else {
            QMessageBox::warning(this, "ERRO", "Erro ao pesquisar competidores!");
            qDebug() << "Erro na query:" << query.lastError().text();
        }
    } else if (nivel == 3) {
        ui->_txt_titulo->setText("Intermediário");

        QSqlQuery query(conexao->getConexao());
        query.prepare("SELECT u.user_nome, c.user_pontuacao "
                      "FROM table_comp_intermediario c "
                      "JOIN table_usuario u ON c.user_id = u.user_id "
                      "ORDER BY c.user_pontuacao DESC");

        if (query.exec()) {
            ui->_tw_ranking->setColumnCount(2);
            ui->_tw_ranking->setHorizontalHeaderLabels({"Nome", "Pontuação"});

            int cont = 0;
            while(query.next()) {
                ui->_tw_ranking->insertRow(cont);
                ui->_tw_ranking->setItem(cont, 0, new QTableWidgetItem(query.value("user_nome").toString()));
                ui->_tw_ranking->setItem(cont, 1, new QTableWidgetItem(query.value("user_pontuacao").toString()));
                ui->_tw_ranking->setRowHeight(cont, 40);
                cont++;
            }

            ui->_tw_ranking->setColumnWidth(0, 250);
            ui->_tw_ranking->setColumnWidth(1, 240);
            ui->_tw_ranking->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->_tw_ranking->verticalHeader()->setVisible(false);
        } else {
            QMessageBox::warning(this, "ERRO", "Erro ao pesquisar competidores!");
            qDebug() << "Erro na query:" << query.lastError().text();
        }
    } else {
        ui->_txt_titulo->setText("Avançado");

        QSqlQuery query(conexao->getConexao());
        query.prepare("SELECT u.user_nome, c.user_pontuacao "
                      "FROM table_comp_avancado c "
                      "JOIN table_usuario u ON c.user_id = u.user_id "
                      "ORDER BY c.user_pontuacao DESC");

        if (query.exec()) {
            ui->_tw_ranking->setColumnCount(2);
            ui->_tw_ranking->setHorizontalHeaderLabels({"Nome", "Pontuação"});

            int cont = 0;
            while(query.next()) {
                ui->_tw_ranking->insertRow(cont);
                ui->_tw_ranking->setItem(cont, 0, new QTableWidgetItem(query.value("user_nome").toString()));
                ui->_tw_ranking->setItem(cont, 1, new QTableWidgetItem(query.value("user_pontuacao").toString()));
                ui->_tw_ranking->setRowHeight(cont, 40);
                cont++;
            }

            ui->_tw_ranking->setColumnWidth(0, 250);
            ui->_tw_ranking->setColumnWidth(1, 240);
            ui->_tw_ranking->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->_tw_ranking->verticalHeader()->setVisible(false);
        } else {
            QMessageBox::warning(this, "ERRO", "Erro ao pesquisar competidores!");
            qDebug() << "Erro na query:" << query.lastError().text();
        }
    }
}

janela_competicao::~janela_competicao()
{
    delete ui;
}

void janela_competicao::on__btn_voltar_clicked()
{
    this->close();
}

