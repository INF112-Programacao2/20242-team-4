#include "janela_adiciona_atividade.h"
#include "ui_janela_adiciona_atividade.h"

janela_adiciona_atividade::janela_adiciona_atividade(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_adiciona_atividade)
{
    ui->setupUi(this);

    conexao = Conexao::getInstance();

    QString tipos[4] = {"Musculação", "Aeróbico", "Mobilidade", "Outros"};
    QString icon_tipos[4] = {
        ":/img/Imagens/imagem_dumbbell_fitness_b.png",
        ":/img/Imagens/imagem_treadmill_b.png",
        ":/img/Imagens/imagem_person_lunge_b.png",
        ":/img/Imagens/imagem_bolt_b.png"
    };

    for (int i = 0; i < 4; i++){
        ui->_cb_tipo->addItem(QIcon(icon_tipos[i]), tipos[i]);
    }

    connect(ui->_cb_tipo, &QComboBox::currentTextChanged, this, [this](const QString& tipo) {
        ui->_cb_atividade->clear();

        try {
            QSqlQuery query(conexao->getConexao());

            query.prepare("SELECT a_nome FROM table_atividade WHERE a_tipo = ?");
            query.addBindValue(tipo);

            if (!query.exec()) {
                throw std::runtime_error(query.lastError().text().toStdString());
            }

            while(query.next()) {
                ui->_cb_atividade->addItem(query.value("a_nome").toString());
            }
        }
        catch (const std::exception& e) {
            qDebug() << "Erro ao atualizar atividades do banco de dados:" << e.what();
            QMessageBox::critical(this, "Erro", "Não foi possível atualizar a lista de ativvidades.");
        }
    });

    QString atipo = ui->_cb_tipo->currentText();

    try {
        QSqlQuery query(conexao->getConexao());

        query.prepare("SELECT a_nome FROM table_atividade WHERE a_tipo = ?");
        query.addBindValue(atipo);

        if (!query.exec()) {
            throw std::runtime_error(query.lastError().text().toStdString());
        }

        while(query.next()) {
            ui->_cb_atividade->addItem(query.value("a_nome").toString());
        }
    }
    catch (const std::exception& e) {
        qDebug() << "Erro ao buscar atividades no banco de dados:" << e.what();
        QMessageBox::critical(this, "Erro", "Não foi possível carregar a lista de atividades.");
    }
}

janela_adiciona_atividade::~janela_adiciona_atividade()
{
    delete ui;
}

void janela_adiciona_atividade::on__btn_adicionar_clicked()
{
    QString repeticao = ui->_line_repeticao->text();
    QString atividade = ui->_cb_atividade->currentText();

    if (repeticao.isEmpty() || atividade.isEmpty()){
        QMessageBox::warning(this, "Aviso", "Preencha todos os campos!");
        return;
    }

    QString atividadeCompleta = repeticao + " " + atividade;
    emit atividadeAdicionada(atividadeCompleta);
    this->close();
}

