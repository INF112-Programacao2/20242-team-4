#include "janela_adiciona_prato.h"
#include "ui_janela_adiciona_prato.h"

janela_adiciona_prato::janela_adiciona_prato(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_adiciona_prato)
{
    ui->setupUi(this);

    conexao = Conexao::getInstance();

    QString tipos[8] = {"Carboidratos", "Proteínas", "Laticínios", "Gorduras", "Frutas", "Vegetais", "Bebidas", "Outros"};
    QString icon_tipos[8] = {
        ":/img/Imagens/imagem_wheat_b.png",
        ":/img/Imagens/imagem_turkey_b.png",
        ":/img/Imagens/imagem_cheese_b.png",
        ":/img/Imagens/imagem_olive_oil_b.png",
        ":/img/Imagens/imagem_lemon_b.png",
        ":/img/Imagens/imagem_salad_b.png",
        ":/img/Imagens/imagem_drink_b.png",
        ":/img/Imagens/imagem_candy_b.png"
    };

    for (int i = 0; i < 8; i++){
        ui->_cb_tipo->addItem(QIcon(icon_tipos[i]), tipos[i]);
    }

    connect(ui->_cb_tipo, &QComboBox::currentTextChanged, this, [this](const QString& tipo) {
        ui->_cb_prato->clear();

        try {
            QSqlQuery query(conexao->getConexao());

            query.prepare("SELECT food_nome FROM table_refeicao WHERE food_tipo = ?");
            query.addBindValue(tipo);

            if (!query.exec()) {
                throw std::runtime_error(query.lastError().text().toStdString());
            }

            while(query.next()) {
                ui->_cb_prato->addItem(query.value("food_nome").toString());
            }
        }
        catch (const std::exception& e) {
            qDebug() << "Erro ao atualizar pratos do banco de dados:" << e.what();
            QMessageBox::critical(this, "Erro", "Não foi possível atualizar a lista de pratos.");
        }
    });

    QString foodtipo = ui->_cb_tipo->currentText();

    try {
        QSqlQuery query(conexao->getConexao());

        query.prepare("SELECT food_nome FROM table_refeicao WHERE food_tipo = ?");
        query.addBindValue(foodtipo);

        if (!query.exec()) {
            throw std::runtime_error(query.lastError().text().toStdString());
        }

        while(query.next()) {
            ui->_cb_prato->addItem(query.value("food_nome").toString());
        }
    }
    catch (const std::exception& e) {
        qDebug() << "Erro ao buscar pratos do banco de dados:" << e.what();
        QMessageBox::critical(this, "Erro", "Não foi possível carregar a lista de pratos.");
    }
}

janela_adiciona_prato::~janela_adiciona_prato()
{
    delete ui;
}

void janela_adiciona_prato::on__btn_adicionar_clicked()
{
    QString quantia = ui->_line_quantia->text();
    QString prato = ui->_cb_prato->currentText();

    if (quantia.isEmpty() || prato.isEmpty()){
        QMessageBox::warning(this, "Aviso", "Preencha todos os campos!");
        return;
    }

    QString pratoCompleto = quantia + " " + prato;
    emit pratoAdicionado(pratoCompleto);
    this->close();
}

