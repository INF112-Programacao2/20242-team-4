#include "janela_cadastro.h"
#include "ui_janela_cadastro.h"

janela_cadastro::janela_cadastro(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_cadastro)
{
    ui->setupUi(this);


}

janela_cadastro::~janela_cadastro()
{
    delete ui;
}

void janela_cadastro::on__btn_cadastrar_clicked()
{
    QSqlDatabase BancoDeDados = QSqlDatabase::database();

    if (!BancoDeDados.isOpen()) {
        BancoDeDados.open();  // Tenta reabrir
        qDebug() << "Tentando reabrir banco de dados";
        if (!BancoDeDados.isOpen()) {
            qDebug() << "Falha ao reabrir:" << BancoDeDados.lastError().text();
            return;
        }
    }

    QString Nome   = ui->_line_nome->text();
    QString Email  = ui->_line_email->text();
    QString Senha  = ui->_line_senha->text();
    QString cSenha = ui->_line_confirmas->text();

    if (Nome.isEmpty() || Email.isEmpty() || Senha.isEmpty() || cSenha.isEmpty()) {
        QMessageBox::warning(this, "Erro", "Por favor, preencha todos os campos!");
        return;
    }

    if (Senha != cSenha){
        QMessageBox::warning(this, "Erro", "Senhas incompatíveis!");
        return;
    }

    QSqlQuery query;

    query.prepare("INSERT INTO table_usuario (user_nome, user_email, user_senha) VALUES (?, ?, ?)");
    query.addBindValue(Nome);
    query.addBindValue(Email);
    query.addBindValue(Senha);

    if (query.exec()){
        QMessageBox::information(this, "", "Registro gravado com sucesso");

        emit voltarLogin();
        this->close();
    } else {
        qDebug() << "Erro ao inserir registro:" << query.lastError().text();
        QMessageBox::critical(this, "Erro", "Erro ao cadastrar usuário. Verifique se o email já está cadastrado.");
    }
}

