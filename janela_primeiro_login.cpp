#include "janela_primeiro_login.h"
#include "ui_janela_primeiro_login.h"

void janela_primeiro_login::setUserId(int id) {
    this->_user_id = id;
    {
        if (!conexao->abrir()) {
            qDebug() << "Erro ao abrir conexão com banco de dados";
            return;
        }

        QSqlDatabase& db = conexao->getConexao();
    }
}

janela_primeiro_login::janela_primeiro_login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_primeiro_login)
{
    ui->setupUi(this);

    conexao = Conexao::getInstance();
}

janela_primeiro_login::~janela_primeiro_login()
{
    delete ui;
}

void janela_primeiro_login::on__btn_padrao_clicked()
{
    criar_upadrao = new janela_criar_upadrao();

    criar_upadrao->setUserId(_user_id);

    //tranforma a janela cadastro na janela login
    connect(criar_upadrao, &QMainWindow::destroyed, criar_upadrao, &QObject::deleteLater);

    //abre a janela de criar usuário padrão
    criar_upadrao->show();

    //fecha a janela
    this->hide();
}


void janela_primeiro_login::on__btn_profissional_clicked()
{
    criar_uprofissional = new janela_criar_uprofissional();

    criar_uprofissional->setUserId(_user_id);

    //tranforma a janela cadastro na janela login
    connect(criar_uprofissional, &QMainWindow::destroyed, criar_uprofissional, &QObject::deleteLater);

    //abre a janela de criar usuário padrão
    criar_uprofissional->show();

    //fecha a janela
    this->hide();
}

