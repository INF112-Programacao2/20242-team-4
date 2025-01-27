#include "janela_ve_competicoes.h"
#include "ui_janela_ve_competicoes.h"

void janela_ve_competicoes::carregarCompetições() {
    // Limpar tabela existente
    ui->_tw_competicoes->clearContents();
    ui->_tw_competicoes->setRowCount(0);

    if (!conexao->abrir()) {
        QMessageBox::critical(this, "Erro", "Não foi possível conectar ao banco de dados");
        return;
    }

    QStringList tabelas = {
        "table_comp_iniciantes",
        "table_comp_amador",
        "table_comp_intermediario",
        "table_comp_avancado"
    };

    QStringList niveis = {"Iniciante", "Amador", "Intermediário", "Avançado"};

    for (int i = 0; i < tabelas.size(); ++i) {
        QSqlQuery query(conexao->getConexao());
        query.prepare(QString("SELECT user_pontuacao FROM %1 WHERE user_id = ?").arg(tabelas[i]));
        query.addBindValue(_user_id);

        if (query.exec() && query.next()) {
            int rowCount = ui->_tw_competicoes->rowCount();
            ui->_tw_competicoes->insertRow(rowCount);

            ui->_tw_competicoes->setItem(rowCount, 0, new QTableWidgetItem(niveis[i]));
            ui->_tw_competicoes->setItem(rowCount, 1, new QTableWidgetItem(QString::number(query.value(0).toInt())));
        }
    }
}

void janela_ve_competicoes::setUserId(int id) {
    this->_user_id = id;
    if (!conexao->abrir()) {
        qDebug() << "Erro ao abrir conexão com banco de dados";
        return;
    }

    carregarCompetições();
}

janela_ve_competicoes::janela_ve_competicoes(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_ve_competicoes)
{
    ui->setupUi(this);

    conexao = Conexao::getInstance();

    ui->_tw_competicoes->setColumnCount(2);
    ui->_tw_competicoes->setHorizontalHeaderLabels({"Nível", "Pontuação"});
    ui->_tw_competicoes->setColumnWidth(0, 250); // Define a largura da primeira coluna
    ui->_tw_competicoes->setColumnWidth(1, 240);
    ui->_tw_competicoes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->_tw_competicoes->verticalHeader()->setVisible(false);
}

janela_ve_competicoes::~janela_ve_competicoes()
{
    delete ui;
}

void janela_ve_competicoes::on__btn_voltar_clicked()
{
    emit voltarMenuInicial();
    this->close();
}


void janela_ve_competicoes::on__btn_acessar_clicked()
{
    // Verifica se há uma linha selecionada
    int linha = ui->_tw_competicoes->currentRow();

    if(linha < 0) {
        QMessageBox::warning(this, "Aviso", "Selecione uma competição para acessar!");
        return;
    }

    // Pega o ID do cliente da coluna oculta
    QString nivel = ui->_tw_competicoes->item(linha, 0)->text();

    int n = 1;
    if (nivel == "Iniciante"){
        n  = 1;
    } else if (nivel == "Amador"){
        n = 2;
    } else if (nivel == "Intermediário"){
        n = 3;
    } else {
        n = 4;
    }

    // Cria e mostra a janela de competição
    j_competicao = new janela_competicao(n, this);

    j_competicao->show();
}

