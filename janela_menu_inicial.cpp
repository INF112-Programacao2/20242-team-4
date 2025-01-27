#include "janela_menu_inicial.h"
#include "ui_janela_menu_inicial.h"

void janela_menu_inicial::setUserId(int id) {
    this->_user_id = id;
    {
        if (!conexao->abrir()) {
            qDebug() << "Erro ao abrir conexão com banco de dados";
            return;
        }

        QSqlDatabase& db = conexao->getConexao();

        QSqlQuery query(db);

        query.prepare("SELECT user_nome FROM table_usuario WHERE user_id = ?");
        query.addBindValue(_user_id);

        if (query.exec() && query.next()) {
            QString nomeUsuario = query.value("user_nome").toString();
            ui->_txt_nome->setText(nomeUsuario + "!");
        } else {
            qDebug() << "Erro ao buscar nome do usuário:" << query.lastError().text();
        }
    }
}

janela_menu_inicial::janela_menu_inicial(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_menu_inicial)
{
    ui->setupUi(this);

    conexao = Conexao::getInstance();
}

janela_menu_inicial::~janela_menu_inicial()
{
    delete ui;
}


void janela_menu_inicial::on__btn_perfil_clicked()
{
    perfil_usuario = new janela_perfil_usuario();

    perfil_usuario->setUserId(_user_id);

    //tranforma a janela cadastro na janela login
    connect(perfil_usuario, &janela_perfil_usuario::voltarMenuInicial, this, &QMainWindow::show);

    //abre a janela de cadastro
    perfil_usuario->show();

    //fecha a janela de login
    this->hide();
}

void janela_menu_inicial::on__btn_dieta_clicked()
{
    dieta_usuario = new janela_dieta_usuario();

    dieta_usuario->setUserId(_user_id);

    //tranforma a janela cadastro na janela login
    connect(dieta_usuario, &janela_dieta_usuario::voltarMenuInicial, this, &QMainWindow::show);

    //abre a janela de cadastro
    dieta_usuario->show();

    //fecha a janela de login
    this->hide();
}


void janela_menu_inicial::on__btn_treino_clicked()
{
    treino_usuario = new janela_treino_usuario();

    treino_usuario->setUserId(_user_id);

    //tranforma a janela menu inicial na janela treino
    connect(treino_usuario, &janela_treino_usuario::voltarMenuInicial, this, &QMainWindow::show);

    //abre a janela de treino
    treino_usuario->show();

    //fecha a janela de menu inicial
    this->hide();
}


void janela_menu_inicial::on__btn_checkin_clicked()
{
    checkins = new janela_checkins();

    checkins->setUserId(_user_id);

    connect(checkins, &janela_checkins::voltarMenuInicial, this, &QMainWindow::show);

    checkins->show();

    this->hide();
}


void janela_menu_inicial::on__btn_go_competicao_clicked()
{
    entrar_competicao = new janela_entrar_competicao();

    entrar_competicao->setUserId(_user_id);

    //tranforma a janela cadastro na janela login
    connect(entrar_competicao, &janela_entrar_competicao::voltarMenuInicial, this, &QMainWindow::show);

    //abre a janela de cadastro
    entrar_competicao->show();

    //fecha a janela de login
    this->hide();
}


void janela_menu_inicial::on__btn_my_competicao_clicked()
{
    ve_competicao = new janela_ve_competicoes();

    ve_competicao->setUserId(_user_id);

    //tranforma a janela cadastro na janela login
    connect(ve_competicao, &janela_ve_competicoes::voltarMenuInicial, this, &QMainWindow::show);

    //abre a janela de cadastro
    ve_competicao->show();

    //fecha a janela de login
    this->hide();

}

