#include "janela_criar_upadrao.h"
#include "ui_janela_criar_upadrao.h"

void janela_criar_upadrao::setUserId(int id) {
    this->_user_id = id;
        if (!conexao->abrir()) {
            qDebug() << "Erro ao abrir conexão com banco de dados";
            return;
        }
}

janela_criar_upadrao::janela_criar_upadrao(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_criar_upadrao)
{
    ui->setupUi(this);

    conexao = Conexao::getInstance();
}

janela_criar_upadrao::~janela_criar_upadrao()
{
    delete ui;
}

void janela_criar_upadrao::on__btn_confirma_clicked()
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
        // Converte os valores após validação
        bool pesoOk, alturaOk;
        double pesoValue = Peso.toDouble(&pesoOk);
        double alturaValue = Altura.toDouble(&alturaOk);

        if (!pesoOk || !alturaOk) {
            throw std::runtime_error("Erro ao converter valores numéricos");
        }

        // Configure o usuário com os dados validados
        user.setDatadenascimento(DataNascimento);
        user.setPeso(pesoValue);
        user.setAltura(alturaValue);
        user.setObjetivo(Objetivo);

        // Tenta cadastrar o perfil completo
        if (!conexao->abrir()) {
            throw std::runtime_error("Erro ao abrir conexão com banco de dados");
        }

        if (user.cadastrarPerfilCompleto(conexao, _user_id)) {
            QMessageBox::information(this, "Sucesso", "Perfil criado com sucesso!");

            // Criar e mostrar janela do menu inicial
            menu_incial = new janela_menu_inicial();
            menu_incial->setUserId(_user_id);
            connect(menu_incial, &QMainWindow::destroyed, menu_incial, &QObject::deleteLater);
            menu_incial->show();
            this->close();
        }

    } catch (const std::exception& e) {
        qDebug() << "Erro ao processar dados:" << e.what();
        QMessageBox::critical(this, "Erro", "Ocorreu um erro ao processar os dados. Por favor, tente novamente.");
    }
}

