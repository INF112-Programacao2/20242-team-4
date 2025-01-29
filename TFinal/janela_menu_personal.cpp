#include "janela_menu_personal.h"
#include "ui_janela_menu_personal.h"

void janela_menu_personal::setUserId(int id) {
    this->_user_id = id;
    {
        if (!conexao->abrir()) {
            qDebug() << "Erro ao abrir conexão com banco de dados";
            return;
        }

        QSqlQuery query(conexao->getConexao());

        query.prepare("SELECT user_nome FROM table_usuario WHERE user_id = ?");
        query.addBindValue(_user_id);

        if (query.exec() && query.next()) {
            QString nomeUsuario = query.value("user_nome").toString();
            ui->_txt_nome->setText(nomeUsuario + "!");
        } else {
            qDebug() << "Erro ao buscar nome do usuário:" << query.lastError().text();
        }
    }

    QSqlQuery query_clientes(conexao->getConexao());

    query_clientes.prepare(
        "SELECT u.user_id, u.user_nome, p.user_objetivo "
        "FROM table_perfil_usuario p "
        "JOIN table_usuario u ON u.user_id = p.user_id "
        "WHERE p.user_idpersonal = ?"
        );

    query_clientes.addBindValue(_user_id);

    if (query_clientes.exec()){
        int cont = 0;

        ui->_tw_clientes->setColumnCount(3);
        ui->_tw_clientes->setHorizontalHeaderLabels({"Nome", "Objetivo", "ID"});
        ui->_tw_clientes->hideColumn(2);  // Esconde a coluna do ID

        ui->_tw_clientes->setHorizontalHeaderLabels({"Nome", "Objetivo"});

        while(query_clientes.next()){
            ui->_tw_clientes->insertRow(cont);
            ui->_tw_clientes->setItem(cont, 0, new QTableWidgetItem(query_clientes.value("user_nome").toString()));
            ui->_tw_clientes->setItem(cont, 1, new QTableWidgetItem(query_clientes.value("user_objetivo").toString()));
            ui->_tw_clientes->setItem(cont, 2, new QTableWidgetItem(query_clientes.value("user_id").toString()));
            ui->_tw_clientes->setRowHeight(cont, 40);
            cont++;
        }

        ui->_tw_clientes->setColumnWidth(0, 250); // Define a largura da primeira coluna
        ui->_tw_clientes->setColumnWidth(1, 240);
        ui->_tw_clientes->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->_tw_clientes->verticalHeader()->setVisible(false);


    } else {
        QMessageBox::warning(this, "ERRO", "Erro ao pesquisar clientes!");
        qDebug() << "Erro na query:" << query_clientes.lastError().text();
    }
}

janela_menu_personal::janela_menu_personal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_menu_personal)
{
    ui->setupUi(this);

    conexao = Conexao::getInstance();
}

janela_menu_personal::~janela_menu_personal()
{
    delete ui;
}

void janela_menu_personal::on__btn_editar_clicked()
{
    // Verifica se há uma linha selecionada
    int linha = ui->_tw_clientes->currentRow();
    if(linha < 0) {
        QMessageBox::warning(this, "Aviso", "Selecione um cliente para editar!");
        return;
    }

    // Pega o ID do cliente da coluna oculta
    QString id_cliente = ui->_tw_clientes->item(linha, 2)->text();

    // Cria e mostra a janela de edição
    editar = new janela_editar_treino();

    // Passa o ID do cliente
    editar->setUserId(id_cliente.toInt());

    connect(editar, &QMainWindow::destroyed, editar, &QObject::deleteLater);

    editar->show();
}


void janela_menu_personal::on__btn_excluir_clicked()
{
    // Verifica se há uma linha selecionada
    int linha = ui->_tw_clientes->currentRow();
    if(linha < 0) {
        QMessageBox::warning(this, "Aviso", "Selecione um cliente para excluir!");
        return;
    }

    // Pega o ID do cliente da coluna oculta
    QString id_cliente = ui->_tw_clientes->item(linha, 2)->text();

    QMessageBox::StandardButton resposta;
    resposta = QMessageBox::question(this, "Confirmação", "Tem certeza que deseja remover este cliente?", QMessageBox::Yes|QMessageBox::No);

    if(resposta == QMessageBox::Yes) {
        QSqlQuery query(conexao->getConexao());
        query.prepare("UPDATE table_perfil_usuario SET user_idpersonal = NULL WHERE user_id = ?");
        query.addBindValue(id_cliente);

        if(query.exec()) {
            ui->_tw_clientes->removeRow(linha);
            QMessageBox::information(this, "Sucesso", "Cliente removido com sucesso!");
        } else {
            QMessageBox::critical(this, "Erro", "Erro ao remover cliente!");
            qDebug() << "Erro na query:" << query.lastError().text();
        }
    }
}


void janela_menu_personal::on__btn_pesquisar_clicked()
{
    QString pesquisa = ui->_line_pesquisa->text().trimmed();

    QSqlQuery query_clientes(conexao->getConexao());

    if(pesquisa.isEmpty()) {
        // Se a pesquisa estiver vazia, mostra todos os clientes
        query_clientes.prepare(
            "SELECT u.user_id, u.user_nome, p.user_objetivo "
            "FROM table_perfil_usuario p "
            "JOIN table_usuario u ON u.user_id = p.user_id "
            "WHERE p.user_idpersonal = ?"
            );
        query_clientes.addBindValue(_user_id);
    } else {
        // Se tiver texto na pesquisa, filtra pelo nome
        query_clientes.prepare(
            "SELECT u.user_id, u.user_nome, p.user_objetivo "
            "FROM table_perfil_usuario p "
            "JOIN table_usuario u ON u.user_id = p.user_id "
            "WHERE p.user_idpersonal = ? "
            "AND u.user_nome LIKE ?"
            );
        query_clientes.addBindValue(_user_id);
        query_clientes.addBindValue("%" + pesquisa + "%");
    }

    if (query_clientes.exec()) {
        int cont = 0;
        ui->_tw_clientes->setRowCount(0);

        while(query_clientes.next()) {
            ui->_tw_clientes->insertRow(cont);
            ui->_tw_clientes->setItem(cont, 0, new QTableWidgetItem(query_clientes.value("user_nome").toString()));
            ui->_tw_clientes->setItem(cont, 1, new QTableWidgetItem(query_clientes.value("user_objetivo").toString()));
            ui->_tw_clientes->setItem(cont, 2, new QTableWidgetItem(query_clientes.value("user_id").toString()));
            ui->_tw_clientes->setRowHeight(cont, 40);
            cont++;
        }
    } else {
        QMessageBox::warning(this, "ERRO", "Erro ao pesquisar clientes!");
        qDebug() << "Erro na query:" << query_clientes.lastError().text();
    }
}

