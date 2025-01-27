#include "janela_editar_dieta.h"
#include "ui_janela_editar_dieta.h"

void janela_editar_dieta::abrirJanelaAdicionaPrato(QLabel *campoAlvo){
    campoAtual = campoAlvo;

    janela_prato = new janela_adiciona_prato(this);

    connect(janela_prato, &janela_adiciona_prato::pratoAdicionado, this, [this](const QString& prato) {
        QString textoAtual = campoAtual->text();
        if(textoAtual.isEmpty()) {
            campoAtual->setText(prato);
        } else {
            campoAtual->setText(textoAtual + ", " + prato);
        }
    });

    connect(janela_prato, &QMainWindow::destroyed, janela_prato, &QObject::deleteLater);

    janela_prato->show();
}

void janela_editar_dieta::removerUltimoPrato(QLabel* campoAlvo) {
    QString texto = campoAlvo->text();
    int ultimaVirgula = texto.lastIndexOf(",");

    if (ultimaVirgula != -1) {
        // Remove o último item e a vírgula
        texto = texto.left(ultimaVirgula);
        // Remove espaços em branco no final
        texto = texto.trimmed();
        campoAlvo->setText(texto);
    } else {
        // Se não houver vírgula, limpa todo o texto
        campoAlvo->setText("");
    }
}

void janela_editar_dieta::setUserId(int id) {
    this->_user_id = id;
    {
        if (!conexao->abrir()) {
            qDebug() << "Erro ao abrir conexão com banco de dados";
            return;
        }

        QSqlDatabase& db = conexao->getConexao();

        QSqlQuery query_usuario(db);

        query_usuario.prepare("SELECT user_nome FROM table_usuario WHERE user_id = ?");
        query_usuario.addBindValue(_user_id);

        if (query_usuario.exec() && query_usuario.next()) {
            QString nomeUsuario = query_usuario.value("user_nome").toString();

            ui->_txt_usuario->setText(nomeUsuario);
        } else {
            qDebug() << "Erro ao buscar nome do usuário:" << query_usuario.lastError().text();
        }

        QSqlQuery query_dieta(conexao->getConexao());

        query_dieta.prepare("SELECT user_cafe_da_manha, user_lanche_da_manha, user_almoco, user_lanche_da_tarde, user_jantar, user_ceia, user_comentario FROM table_dieta WHERE user_id = ?");
        query_dieta.addBindValue(_user_id);

        if (query_dieta.exec() && query_dieta.next()) {
            QString cafedamanha = query_dieta.value("user_cafe_da_manha").toString();
            QString lanchedamanha = query_dieta.value("user_lanche_da_manha").toString();
            QString almoco = query_dieta.value("user_almoco").toString();
            QString lanchedatarde = query_dieta.value("user_lanche_da_tarde").toString();
            QString jantar = query_dieta.value("user_jantar").toString();
            QString ceia = query_dieta.value("user_ceia").toString();
            QString comentario = query_dieta.value("user_comentario").toString();

            ui->_txt_cafedamanha_user->setText(cafedamanha);
            ui->_txt_lanchedamanha_user->setText(lanchedamanha);
            ui->_txt_almoco_user->setText(almoco);
            ui->_txt_lanchedatarde_user->setText(lanchedatarde);
            ui->_txt_jantar_user->setText(jantar);
            ui->_txt_ceia_user->setText(ceia);
            ui->_te_comentario->setText(comentario);

        } else {
            qDebug() << "Erro ao buscar dados da dieta do cliente:" << query_dieta.lastError().text();
        }

    }
}

janela_editar_dieta::janela_editar_dieta(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_editar_dieta)
{
    ui->setupUi(this);

    conexao = Conexao::getInstance();
}

janela_editar_dieta::~janela_editar_dieta()
{
    delete ui;
}

void janela_editar_dieta::on__btn_salvar_clicked()
{
    QString cafedamanha = ui->_txt_cafedamanha_user->text();
    QString lanchedamanha = ui->_txt_lanchedamanha_user->text();
    QString almoco = ui->_txt_almoco_user->text();
    QString lanchedatarde = ui->_txt_lanchedatarde_user->text();
    QString jantar = ui->_txt_jantar_user->text();
    QString ceia = ui->_txt_ceia_user->text();
    QString comentario = ui->_te_comentario->toPlainText();

    try {
        QSqlQuery query_dieta(conexao->getConexao());

        query_dieta.prepare("UPDATE table_dieta SET "
                            "user_cafe_da_manha = ?, "
                            "user_lanche_da_manha = ?, "
                            "user_almoco = ?, "
                            "user_lanche_da_tarde = ?, "
                            "user_jantar = ?, "
                            "user_ceia = ?, "
                            "user_comentario = ? "
                            "WHERE user_id = ?");

        query_dieta.addBindValue(cafedamanha);
        query_dieta.addBindValue(lanchedamanha);
        query_dieta.addBindValue(almoco);
        query_dieta.addBindValue(lanchedatarde);
        query_dieta.addBindValue(jantar);
        query_dieta.addBindValue(ceia);
        query_dieta.addBindValue(comentario);
        query_dieta.addBindValue(_user_id);

        if (!query_dieta.exec()) {
            throw std::runtime_error(query_dieta.lastError().text().toStdString());
        }

        QMessageBox::information(this, "Sucesso", "Dieta atualizada com sucesso!");
        this->close();
    }
    catch (const std::exception& e) {
        qDebug() << "Erro ao atualizar dieta:" << e.what();
        QMessageBox::critical(this, "Erro", "Não foi possível atualizar a dieta.");
    }
}


void janela_editar_dieta::on__btn_cafedamanha_clicked()
{
    abrirJanelaAdicionaPrato(ui->_txt_cafedamanha_user);
}


void janela_editar_dieta::on__btn_lanchedamanha_clicked()
{
    abrirJanelaAdicionaPrato(ui->_txt_lanchedamanha_user);
}


void janela_editar_dieta::on__btn_almoco_clicked()
{
    abrirJanelaAdicionaPrato(ui->_txt_almoco_user);
}


void janela_editar_dieta::on__btn_lanchedatarde_clicked()
{
    abrirJanelaAdicionaPrato(ui->_txt_lanchedatarde_user);
}


void janela_editar_dieta::on__btn_jantar_clicked()
{
    abrirJanelaAdicionaPrato(ui->_txt_jantar_user);
}


void janela_editar_dieta::on__btn_ceia_clicked()
{
    abrirJanelaAdicionaPrato(ui->_txt_ceia_user);
}


void janela_editar_dieta::on__btn_cafedamanha_2_clicked()
{
    removerUltimoPrato(ui->_txt_cafedamanha_user);
}


void janela_editar_dieta::on__btn_lanchedamanha_2_clicked()
{
    removerUltimoPrato(ui->_txt_lanchedamanha_user);
}


void janela_editar_dieta::on__btn_almoco_2_clicked()
{
    removerUltimoPrato(ui->_txt_almoco_user);
}


void janela_editar_dieta::on__btn_lanchedatarde_2_clicked()
{
    removerUltimoPrato(ui->_txt_lanchedatarde_user);
}


void janela_editar_dieta::on__btn_jantar_2_clicked()
{
    removerUltimoPrato(ui->_txt_jantar_user);
}


void janela_editar_dieta::on__btn_ceia_2_clicked()
{
    removerUltimoPrato(ui->_txt_ceia_user);
}

