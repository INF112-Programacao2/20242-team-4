#include "janela_perfil_usuario.h"
#include "ui_janela_perfil_usuario.h"

void janela_perfil_usuario::setUserId(int id) {
    this->_user_id = id;

    conexao = Conexao::getInstance();

    if (!conexao->abrir()) {
        qDebug() << "Erro ao abrir conexão com banco de dados";
        return;
    }

    QSqlQuery query_usuario(conexao->getConexao());

    query_usuario.prepare("SELECT user_nome FROM table_usuario WHERE user_id = ?");
    query_usuario.addBindValue(_user_id);

    if (query_usuario.exec() && query_usuario.next()) {
        QString nome = query_usuario.value("user_nome").toString();

        ui->_txt_nome_user->setText(nome);

    } else {
        qDebug() << "Erro ao buscar nome do usuário:" << query_usuario.lastError().text();
    }

    QSqlQuery query_perfil(conexao->getConexao());

    query_perfil.prepare("SELECT user_datanascimento, user_peso, user_altura, user_checkins, user_ndias, user_objetivo, user_idnutricionista, user_idpersonal FROM table_perfil_usuario WHERE user_id = ?");
    query_perfil.addBindValue(_user_id);

    if (query_perfil.exec() && query_perfil.next()) {
        QString datanascimento = query_perfil.value("user_datanascimento").toString();
        QString peso = query_perfil.value("user_peso").toString();
        QString altura = query_perfil.value("user_altura").toString();
        QString checkins = query_perfil.value("user_checkins").toString();
        QString ndias = query_perfil.value("user_ndias").toString();
        QString objetivo = query_perfil.value("user_objetivo").toString();

        QDate dataAtual = QDate::currentDate();
        QDate nascimento = QDate::fromString(datanascimento, "dd/MM/yyyy");

        if (nascimento.isValid()) {
            int idade = nascimento.daysTo(dataAtual) / 365;
            ui->_txt_idade_user->setText(QString::number(idade));

        } else {
            qDebug() << "Data de nascimento inválida:" << datanascimento;
            ui->_txt_idade_user->setText("Data inválida");

        }

        ui->_txt_peso_user->setText(peso);
        ui->_txt_altura_user->setText(altura);
        ui->_txt_checkins_user->setText(checkins);
        ui->_txt_ndiasativos_user->setText(ndias);
        ui->_txt_objetivo_user->setText(objetivo);

    } else {
        qDebug() << "Erro ao buscar dados do usuário:" << query_perfil.lastError().text();
    }

    QSqlQuery query_personal(conexao->getConexao());

    QString idpersonal = query_perfil.value("user_idpersonal").toString();

    query_personal.prepare("SELECT user_nome FROM table_usuario WHERE user_id = ?");
    query_personal.addBindValue(idpersonal);

    if (query_personal.exec() && query_personal.next()) {
        QString nomeP = query_personal.value("user_nome").toString();

        ui->_txt_personal_user->setText(nomeP);

    } else {
        qDebug() << "Erro ao buscar nome do personal:" << query_personal.lastError().text();
    }

    QSqlQuery query_nutri(conexao->getConexao());

    QString idnutri = query_perfil.value("user_idnutricionista").toString();

    query_nutri.prepare("SELECT user_nome FROM table_usuario WHERE user_id = ?");
    query_nutri.addBindValue(idnutri);

    if (query_nutri.exec() && query_nutri.next()) {
        QString nomeN = query_nutri.value("user_nome").toString();

        ui->_txt_nutricionista_user->setText(nomeN);

    } else {
        qDebug() << "Erro ao buscar nome do nutricionista:" << query_nutri.lastError().text();
    }
}

janela_perfil_usuario::janela_perfil_usuario(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_perfil_usuario)
{
    ui->setupUi(this);

    conexao = Conexao::getInstance();
}

janela_perfil_usuario::~janela_perfil_usuario()
{
    delete ui;
}

void janela_perfil_usuario::on__btn_voltar_clicked()
{
    emit voltarMenuInicial();
    this->close();
}


void janela_perfil_usuario::on__btn_editar_clicked()
{

}

