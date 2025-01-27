#include "janela_login.h"
#include "ui_janela_login.h"

janela_login::janela_login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::janela_login)
{
    ui->setupUi(this);

    conexao = Conexao::getInstance();
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
    if (!conexao->abrir()) {
        qDebug() << "Erro ao abrir conexão com banco de dados";
        return;
    }

    QString Email = ui->_line_email->text();
    QString Senha = ui->_line_senha->text();

    if (Email.isEmpty() || Senha.isEmpty()) {
        QMessageBox::warning(this, "Erro", "Por favor, preencha todos os campos!");
        return;
    }

    QSqlQuery query(conexao->getConexao());
    query.prepare("SELECT * FROM table_usuario WHERE user_email = ? AND user_senha = ?");
    query.addBindValue(Email);
    query.addBindValue(Senha);

    if (!query.exec()){
        qDebug() << "Erro na consulta:" << query.lastError().text();
        return;
    }

    if (query.next()){
        bool novousuario = true;

        int userId = query.value("user_id").toInt();
        int tipo = query.value("user_tipo").toInt();

        if (tipo == 2 || tipo == 3) {
            novousuario = false;
        }

        query.prepare("SELECT * FROM table_perfil_usuario WHERE user_id = ?");
        query.addBindValue(userId);

        if (!query.exec()){
            qDebug() << "Erro na consulta:" << query.lastError().text();
            return;
        }

        if (query.next()){
            novousuario = false;
        }

        if (novousuario){
            // declara a janela de primeiro login
            primeiro_login = new janela_primeiro_login();

            // repassa o id da conta acesssada
            primeiro_login->setUserId(userId);

            // acessa a janela de primeiro login
            connect(primeiro_login, &QMainWindow::destroyed, primeiro_login, &QObject::deleteLater);
            primeiro_login->show();
            this->hide();

        } else {
            if (tipo == 2){
                // declara a janela de menu inicial
                menu_nutricionista = new janela_menu_nutricionista();

                // repassa o id da conta acesssada
                menu_nutricionista->setUserId(userId);

                // acessa a janela de menu inicial
                connect(menu_nutricionista, &QMainWindow::destroyed, menu_nutricionista, &QObject::deleteLater);
                menu_nutricionista->show();
                this->hide();

            } else if (tipo == 3){
                // declara a janela de menu inicial
                menu_personal = new janela_menu_personal();

                // repassa o id da conta acesssada
                menu_personal->setUserId(userId);

                // acessa a janela de menu inicial
                connect(menu_personal, &QMainWindow::destroyed, menu_personal, &QObject::deleteLater);
                menu_personal->show();
                this->hide();

            }else{
                // declara a janela de menu inicial
                menu_incial = new janela_menu_inicial();

                // repassa o id da conta acesssada
                menu_incial->setUserId(userId);

                // acessa a janela de menu inicial
                connect(menu_incial, &QMainWindow::destroyed, menu_incial, &QObject::deleteLater);
                menu_incial->show();
                this->hide();

            }
        }
    } else {
        QMessageBox::warning(this, "Erro", "Email ou senha incorretos!");
    }
}

