#include "janela_login.h"
#include "ui_janela_login.h"

janela_login::janela_login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::janela_login)
{
    ui->setupUi(this);

    QSqlDatabase BancoDeDados = QSqlDatabase::database();

    if (!BancoDeDados.isValid()) {
        qDebug() << "Conexão com banco de dados é inválida";
    }
}

janela_login::~janela_login()
{
    delete ui;
}

void janela_login::on__btn_cadastrar_clicked()
{
    cadastro = new janela_cadastro();

    //tranforma a janela cadastro na janela login
    connect(cadastro, &janela_cadastro::voltarLogin, this, &QDialog::show);

    //abre a janela de cadastro
    cadastro->show();

    //fecha a janela de login
    this->hide();
}


void janela_login::on__btn_entrar_clicked()
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

    QString Email = ui->_line_email->text();
    QString Senha = ui->_line_senha->text();

    if (Email.isEmpty() || Senha.isEmpty()) {
        QMessageBox::warning(this, "Erro", "Por favor, preencha todos os campos!");
        return;
    }

    if (!BancoDeDados.isOpen()){
        qDebug() << "Bando de dados não está aberto!";
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM table_usuario WHERE user_email = ? AND user_senha = ?");
    query.addBindValue(Email);
    query.addBindValue(Senha);

    if (!query.exec()){
        qDebug() << "Erro na consulta:" << query.lastError().text();
        return;
    }

    if (query.next()){
        menu_incial = new janela_menu_inicial();
        connect(menu_incial, &QMainWindow::destroyed, menu_incial, &QObject::deleteLater);
        menu_incial->show();
        this->hide();
    } else {
        QMessageBox::warning(this, "Erro", "Email ou senha incorretos!");
    }
}

