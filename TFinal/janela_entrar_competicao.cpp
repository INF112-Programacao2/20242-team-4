#include "janela_entrar_competicao.h"
#include "ui_janela_entrar_competicao.h"

void janela_entrar_competicao::setUserId(int id) {
    this->_user_id = id;
    if (!conexao->abrir()) {
        qDebug() << "Erro ao abrir conexão com banco de dados";
        return;
    }

    verificarParticipacoes();
}

void janela_entrar_competicao::verificarParticipacoes()
{
    if (!conexao->abrir()) {
        QMessageBox::critical(this, "Erro", "Não foi possível conectar ao banco de dados");
        return;
    }

    if (_user_id <= 0) {
        qDebug() << "User ID not set";
        return;
    }

    competicao comp;
    comp.setUserID(_user_id);

    // Check participation for each difficulty level
    if (comp.verificaParticipacao(conexao, _user_id, 1)) {
        ui->_btn_iniciante->setStyleSheet("background-color: green; color: white;");
    }

    if (comp.verificaParticipacao(conexao, _user_id, 2)) {
        ui->_btn_amador->setStyleSheet("background-color: green; color: white;");
    }

    if (comp.verificaParticipacao(conexao, _user_id, 3)) {
        ui->_btn_intermediario->setStyleSheet("background-color: green; color: white;");
    }

    if (comp.verificaParticipacao(conexao, _user_id, 4)) {
        ui->_btn_avancado->setStyleSheet("background-color: green; color: white;");
    }
}

janela_entrar_competicao::janela_entrar_competicao(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_entrar_competicao)
{
    ui->setupUi(this);

    conexao = Conexao::getInstance();

    verificarParticipacoes();
}

janela_entrar_competicao::~janela_entrar_competicao()
{
    delete ui;
}

void janela_entrar_competicao::on__btn_iniciante_clicked()
{
    // Verificar se a conexão está aberta
    if (!conexao->abrir()) {
        QMessageBox::critical(this, "Erro", "Não foi possível conectar ao banco de dados");
        return;
    }

    // Criar um objeto competicao
    competicao comp;
    comp.setUserID(_user_id);

    // Verificar se já está participando
    bool jaParticipa = comp.verificaParticipacao(conexao, _user_id, 1);

    if (jaParticipa) {
        // Botão verde para indicar participação
        ui->_btn_iniciante->setStyleSheet("background-color: green; color: white;");

        QMessageBox::information(this, "Participação", "Você já está participando desta competição de nível Iniciante.");
    } else {
        // Tentar adicionar o competidor
        bool adicionado = comp.adicionaNovoCompetidor(conexao, 1);

        if (adicionado) {
            // Botão verde
            ui->_btn_iniciante->setStyleSheet("background-color: green; color: white;");

            QMessageBox::information(this, "Sucesso", "Você foi adicionado à competição de nível Iniciante.");
        } else {
            QMessageBox::warning(this, "Erro", "Não foi possível adicionar você à competição.");
        }
    }
}


void janela_entrar_competicao::on__btn_amador_clicked()
{
    // Verificar se a conexão está aberta
    if (!conexao->abrir()) {
        QMessageBox::critical(this, "Erro", "Não foi possível conectar ao banco de dados");
        return;
    }

    // Criar um objeto competicao
    competicao comp;
    comp.setUserID(_user_id);

    // Verificar se já está participando
    bool jaParticipa = comp.verificaParticipacao(conexao, _user_id, 2);

    if (jaParticipa) {
        // Botão verde para indicar participação
        ui->_btn_amador->setStyleSheet("background-color: #1DD029; color: white;");

        QMessageBox::information(this, "Participação", "Você já está participando desta competição de nível Amador.");
    } else {
        // Tentar adicionar o competidor
        bool adicionado = comp.adicionaNovoCompetidor(conexao, 2);

        if (adicionado) {
            // Botão verde
            ui->_btn_amador->setStyleSheet("background-color: green; color: white;");

            QMessageBox::information(this, "Sucesso", "Você foi adicionado à competição de nível Iniciante.");
        } else {
            QMessageBox::warning(this, "Erro", "Não foi possível adicionar você à competição.");
        }
    }
}


void janela_entrar_competicao::on__btn_intermediario_clicked()
{
    // Verificar se a conexão está aberta
    if (!conexao->abrir()) {
        QMessageBox::critical(this, "Erro", "Não foi possível conectar ao banco de dados");
        return;
    }

    // Criar um objeto competicao
    competicao comp;
    comp.setUserID(_user_id);

    // Verificar se já está participando
    bool jaParticipa = comp.verificaParticipacao(conexao, _user_id, 3);

    if (jaParticipa) {
        // Botão verde para indicar participação
        ui->_btn_intermediario->setStyleSheet("background-color: green; color: white;");

        QMessageBox::information(this, "Participação", "Você já está participando desta competição de nível Intermediário.");
    } else {
        // Tentar adicionar o competidor
        bool adicionado = comp.adicionaNovoCompetidor(conexao, 3);

        if (adicionado) {
            // Botão verde
            ui->_btn_intermediario->setStyleSheet("background-color: green; color: white;");

            QMessageBox::information(this, "Sucesso", "Você foi adicionado à competição de nível Iniciante.");
        } else {
            QMessageBox::warning(this, "Erro", "Não foi possível adicionar você à competição.");
        }
    }
}


void janela_entrar_competicao::on__btn_avancado_clicked()
{
    // Verificar se a conexão está aberta
    if (!conexao->abrir()) {
        QMessageBox::critical(this, "Erro", "Não foi possível conectar ao banco de dados");
        return;
    }

    // Criar um objeto competicao
    competicao comp;
    comp.setUserID(_user_id);

    // Verificar se já está participando
    bool jaParticipa = comp.verificaParticipacao(conexao, _user_id, 4);

    if (jaParticipa) {
        // Botão verde para indicar participação
        ui->_btn_avancado->setStyleSheet("background-color: green; color: white;");

        QMessageBox::information(this, "Participação", "Você já está participando desta competição de nível Avançado.");
    } else {
        // Tentar adicionar o competidor
        bool adicionado = comp.adicionaNovoCompetidor(conexao, 4);

        if (adicionado) {
            // Botão verde
            ui->_btn_avancado->setStyleSheet("background-color: green; color: white;");

            QMessageBox::information(this, "Sucesso", "Você foi adicionado à competição de nível Iniciante.");
        } else {
            QMessageBox::warning(this, "Erro", "Não foi possível adicionar você à competição.");
        }
    }
}


void janela_entrar_competicao::on__btn_voltar_clicked()
{
    emit voltarMenuInicial();
    this->close();
}

