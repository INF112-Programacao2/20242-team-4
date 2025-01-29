#include "janela_cadastro.h"
#include "ui_janela_cadastro.h"

janela_cadastro::janela_cadastro(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_cadastro)
{
    ui->setupUi(this);

    conexao = Conexao::getInstance();
}

janela_cadastro::~janela_cadastro()
{
    delete ui;
}

void janela_cadastro::on__btn_cadastrar_clicked()
{
    usuario novoUsuario;

    if (novoUsuario.validarCadastro(
            ui->_line_nome->text(),
            ui->_line_email->text(),
            ui->_line_senha->text(),
            ui->_line_confirmas->text()))
    {
        // Use setter methods
        novoUsuario.setNome(ui->_line_nome->text());
        novoUsuario.setEmail(ui->_line_email->text());
        novoUsuario.setSenha(ui->_line_senha->text());

        if (novoUsuario.cadastrar(conexao)) {
            QMessageBox::information(nullptr, "", "Registro gravado com sucesso");
            emit voltarLogin();
            this->close();
        } else {
            MessageStyle::showWarning(nullptr, "Erro ao cadastrar usuário. Verifique se o email já está cadastrado.");
        }
    }
}

