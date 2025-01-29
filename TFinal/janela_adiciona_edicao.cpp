#include "janela_adiciona_edicao.h"
#include "ui_janela_adiciona_edicao.h"

void janela_adiciona_edicao::setUserId(int id) {
    this->_user_id = id;
    if (!conexao->abrir()) {
        qDebug() << "Erro ao abrir conexão com banco de dados";
        return;
    }

    // Buscar dados existentes do usuário
    QSqlQuery query(conexao->getConexao());
    query.prepare("SELECT user_peso, user_altura, user_datanascimento, user_objetivo "
                  "FROM table_perfil_usuario WHERE user_id = ?");
    query.addBindValue(_user_id);

    if (query.exec() && query.next()) {
        // Preencher campos com dados existentes
        ui->_line_peso->setText(query.value("user_peso").toString());
        ui->_line_altura->setText(query.value("user_altura").toString());

        // Converter a data para o formato correto e definir no DateEdit
        QString dataNascimento = query.value("user_datanascimento").toString();
        QDate data = QDate::fromString(dataNascimento, "dd/MM/yyyy");
        ui->_date_nascimento->setDate(data);

        // Marcar o radio button correto baseado no objetivo
        QString objetivo = query.value("user_objetivo").toString();
        if (objetivo == ui->_rad_condicionamento->text()) {
            ui->_rad_condicionamento->setChecked(true);
        } else if (objetivo == ui->_rad_hipertrofia->text()) {
            ui->_rad_hipertrofia->setChecked(true);
        } else if (objetivo == ui->_rad_emagrecimento->text()) {
            ui->_rad_emagrecimento->setChecked(true);
        } else if (objetivo == ui->_rad_ganhoforca->text()) {
            ui->_rad_ganhoforca->setChecked(true);
        } else if (objetivo == ui->_rad_mobilidade->text()) {
            ui->_rad_mobilidade->setChecked(true);
        } else if (objetivo == ui->_rad_disciplina->text()) {
            ui->_rad_disciplina->setChecked(true);
        }
    }
}

janela_adiciona_edicao::janela_adiciona_edicao(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_adiciona_edicao)
{
    ui->setupUi(this);

    conexao = Conexao::getInstance();
}

janela_adiciona_edicao::~janela_adiciona_edicao()
{
    delete ui;
}

void janela_adiciona_edicao::on__btn_confirma_clicked()
{
    QString Peso = ui->_line_peso->text();
    QString Altura = ui->_line_altura->text();
    QString DataNascimento = ui->_date_nascimento->date().toString("dd/MM/yyyy");
    QString Objetivo;

    // Verifica se o usuário usou vírgula ao invés de ponto
    if (Peso.contains(",") || Altura.contains(",")) {
        QMessageBox::warning(this, "Atenção", "Por favor, use ponto (.) ao invés de vírgula (,) para números decimais!");
        return;
    }

    // Define o objetivo baseado no radio button selecionado
    if (ui->_rad_condicionamento->isChecked()) {
        Objetivo = ui->_rad_condicionamento->text();
    } else if (ui->_rad_hipertrofia->isChecked()) {
        Objetivo = ui->_rad_hipertrofia->text();
    } else if (ui->_rad_emagrecimento->isChecked()) {
        Objetivo = ui->_rad_emagrecimento->text();
    } else if (ui->_rad_ganhoforca->isChecked()) {
        Objetivo = ui->_rad_ganhoforca->text();
    } else if (ui->_rad_mobilidade->isChecked()) {
        Objetivo = ui->_rad_mobilidade->text();
    } else if (ui->_rad_disciplina->isChecked()) {
        Objetivo = ui->_rad_disciplina->text();
    }

    usuario_padrao user;

    // Valida os dados fornecidos
    if (!user.validarDados(Peso, Altura, DataNascimento, Objetivo)) {
        return; // A função validarDados já mostra mensagem de erro apropriada
    }

    try {
        if (!conexao->abrir()) {
            throw std::runtime_error("Erro ao abrir conexão com banco de dados");
        }

        QSqlQuery query(conexao->getConexao());
        query.prepare("UPDATE table_perfil_usuario SET "
                      "user_peso = ?, "
                      "user_altura = ?, "
                      "user_datanascimento = ?, "
                      "user_objetivo = ? "
                      "WHERE user_id = ?");

        query.addBindValue(Peso);
        query.addBindValue(Altura);
        query.addBindValue(DataNascimento);
        query.addBindValue(Objetivo);
        query.addBindValue(_user_id);

        if (query.exec()) {
            QMessageBox::information(this, "Sucesso", "Perfil atualizado com sucesso!");

            emit voltarPerfil();
            this->close();
        } else {
            throw std::runtime_error("Erro ao atualizar perfil no banco de dados");
        }

    } catch (const std::exception& e) {
        qDebug() << "Erro ao processar dados:" << e.what();
        QMessageBox::critical(this, "Erro", "Ocorreu um erro ao processar os dados. Por favor, tente novamente.");
    }
}

