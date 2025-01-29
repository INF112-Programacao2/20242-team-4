#include "janela_profissional_usuario.h"
#include "ui_janela_profissional_usuario.h"

void janela_profissional_usuario::setTipoProfissional(bool isNutricionista) {
    _isNutricionista = isNutricionista;
    setWindowTitle(_isNutricionista ? "Nutricionista" : "Personal Trainer");
    carregarDadosProfissional();
}

void janela_profissional_usuario::carregarListaProfissionais() {
    if (!conexao->abrir()) {
        qDebug() << "Erro ao abrir conexão com banco de dados";
        return;
    }

    ui->_cb_nome->clear();

    QSqlQuery query(conexao->getConexao());
    query.prepare("SELECT user_id, user_nome FROM table_usuario WHERE user_tipo = ?");
    // Usa 2 para nutricionista e 3 para personal
    query.addBindValue(_isNutricionista ? 2 : 3);

    if (query.exec()) {
        while (query.next()) {
            QString nome = query.value("user_nome").toString();
            ui->_cb_nome->addItem(nome, query.value("user_id"));
        }
    } else {
        qDebug() << "Erro ao buscar lista de profissionais:" << query.lastError().text();
    }
}

void janela_profissional_usuario::carregarDadosProfissional() {
    if (!conexao->abrir()) {
        qDebug() << "Erro ao abrir conexão com banco de dados";
        return;
    }

    // Primeiro busca o profissional atual do usuário
    QSqlQuery query(conexao->getConexao());
    query.prepare("SELECT user_idpersonal, user_idnutricionista FROM table_perfil_usuario WHERE user_id = ?");
    query.addBindValue(_user_id);

    if (query.exec() && query.next()) {
        int profissionalId = _isNutricionista ?
                                 query.value("user_idnutricionista").toInt() :
                                 query.value("user_idpersonal").toInt();

        // Depois carrega a lista completa de profissionais
        carregarListaProfissionais();

        if (profissionalId > 0) {
            // Procura o índice do profissional atual no combo box
            int index = ui->_cb_nome->findData(profissionalId);
            if (index >= 0) {
                ui->_cb_nome->setCurrentIndex(index);
            }
        }
    }
}

void janela_profissional_usuario::setUserId(int id) {
    _user_id = id;
    carregarDadosProfissional();
}

janela_profissional_usuario::janela_profissional_usuario(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_profissional_usuario)
{
    ui->setupUi(this);

    conexao = Conexao::getInstance();
}

janela_profissional_usuario::~janela_profissional_usuario()
{
    delete ui;
}

void janela_profissional_usuario::on__btn_salvar_clicked()
{

    int currentIndex = ui->_cb_nome->currentIndex();
    if (currentIndex < 0) {
        QMessageBox::warning(this, "Aviso", "Por favor, selecione um profissional");
        return;
    }

    try {
        // Pega o ID diretamente dos dados do item
        int profissionalId = ui->_cb_nome->currentData().toInt();

        QSqlQuery queryUpdate(conexao->getConexao());
        QString updateField = _isNutricionista ? "user_idnutricionista" : "user_idpersonal";

        queryUpdate.prepare(QString("UPDATE table_perfil_usuario SET %1 = ? WHERE user_id = ?")
                                .arg(updateField));

        queryUpdate.addBindValue(profissionalId);
        queryUpdate.addBindValue(_user_id);

        if (!queryUpdate.exec()) {
            throw std::runtime_error(queryUpdate.lastError().text().toStdString());
        }

        QMessageBox::information(this, "Sucesso", "Profissional atualizado com sucesso!");
        emit dadosSalvos();
        this->close();
    }
    catch (const std::exception& e) {
        qDebug() << "Erro ao salvar profissional:" << e.what();
        QMessageBox::critical(this, "Erro", "Não foi possível salvar o profissional selecionado.");
    }
}


void janela_profissional_usuario::on__btn_voltar_clicked()
{
    this->close();
}

