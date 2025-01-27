#include "janela_criar_uprofissional.h"
#include "ui_janela_criar_uprofissional.h"

void janela_criar_uprofissional::setUserId(int id) {
    this->_user_id = id;
    {
        if (!conexao->abrir()) {
            qDebug() << "Erro ao abrir conexão com banco de dados";
            return;
        }

        QSqlDatabase& db = conexao->getConexao();
    }
}


janela_criar_uprofissional::janela_criar_uprofissional(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_criar_uprofissional)
{
    ui->setupUi(this);

    conexao = Conexao::getInstance();
}

janela_criar_uprofissional::~janela_criar_uprofissional()
{
    delete ui;
}


void janela_criar_uprofissional::on__btn_confirmar_clicked()
{
    QString especializacao = ui->_line_especializacao->text();
    QString cr = ui->_line_cr->text();
    QString profissao;

    if (ui->_rad_nutricionista->isChecked()){
        profissao = "2";
    } else if (ui->_rad_personal->isChecked()){
        profissao = "3";
    }

    if (especializacao.isEmpty() || cr.isEmpty() || profissao.isEmpty()) {
        QMessageBox::warning(this, "Erro", "Por favor, preencha todos os campos!");
        return;
    }

    QSqlQuery query(conexao->getConexao());

    if (profissao == "2") {
        QSqlDatabase::database().transaction();

        QSqlQuery query_tipo(conexao->getConexao());

        query_tipo.prepare("UPDATE table_usuario SET user_tipo = ? WHERE user_id = ?");
        query_tipo.addBindValue(2);
        query_tipo.addBindValue(_user_id);

        if (!query_tipo.exec()) {
            QSqlDatabase::database().rollback();
            qDebug() << "Erro ao atualizar tipo:" << query_tipo.lastError().text();
            QMessageBox::critical(this, "Erro", "Erro ao atualizar tipo de usuário.");
            return;
        }

        QSqlQuery query(conexao->getConexao());

        query.prepare("INSERT INTO table_perfil_nutricionista (user_id, user_especializacao, user_crn) VALUES (?, ?, ?)");
        query.addBindValue(_user_id);
        query.addBindValue(especializacao);
        query.addBindValue(cr);


        if (query.exec()){
            QSqlDatabase::database().commit();

            QMessageBox::information(this, "", "Registro gravado com sucesso");

            menu_nutricionista = new janela_menu_nutricionista();

            // repassa o id da conta acesssada
            menu_nutricionista->setUserId(_user_id);

            // acessa a janela de menu inicial
            connect(menu_nutricionista, &QMainWindow::destroyed, menu_nutricionista, &QObject::deleteLater);
            menu_nutricionista->show();
            this->hide();

        } else {
            QSqlDatabase::database().rollback();

            qDebug() << "Erro ao inserir registro:" << query.lastError().text();
            QMessageBox::critical(this, "Erro", "Erro ao cadastrar usuário.");
        }

    } else {
        QSqlDatabase::database().transaction();

        QSqlQuery query_tipo(conexao->getConexao());

        query_tipo.prepare("UPDATE table_usuario SET user_tipo = ? WHERE user_id = ?");
        query_tipo.addBindValue(3);
        query_tipo.addBindValue(_user_id);

        if (!query_tipo.exec()) {
            QSqlDatabase::database().rollback();
            qDebug() << "Erro ao atualizar tipo:" << query_tipo.lastError().text();
            QMessageBox::critical(this, "Erro", "Erro ao atualizar tipo de usuário.");
            return;
        }

        QSqlQuery query(conexao->getConexao());

        query.prepare("INSERT INTO table_perfil_personal (user_id, user_especializacao, user_cref) VALUES (?, ?, ?)");
        query.addBindValue(_user_id);
        query.addBindValue(especializacao);
        query.addBindValue(cr);

        if (query.exec()){
            QSqlDatabase::database().commit();

            QMessageBox::information(this, "", "Registro gravado com sucesso");

            menu_personal = new janela_menu_personal();

            // repassa o id da conta acesssada
            menu_personal->setUserId(_user_id);

            // acessa a janela de menu inicial
            connect(menu_personal, &QMainWindow::destroyed, menu_personal, &QObject::deleteLater);
            menu_personal->show();
            this->hide();

        } else {
            QSqlDatabase::database().rollback();

            qDebug() << "Erro ao inserir registro:" << query.lastError().text();
            QMessageBox::critical(this, "Erro", "Erro ao cadastrar usuário.");
        }

    }

}

