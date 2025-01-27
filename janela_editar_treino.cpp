#include "janela_editar_treino.h"
#include "ui_janela_editar_treino.h"

void janela_editar_treino::setUserId(int id) {
    this->_user_id = id;
    {
        if (!conexao->abrir()) {
            qDebug() << "Erro ao abrir conexão com banco de dados";
            return;
        }

        QSqlQuery query_usuario(conexao->getConexao());

        query_usuario.prepare("SELECT user_nome FROM table_usuario WHERE user_id = ?");
        query_usuario.addBindValue(_user_id);

        if (query_usuario.exec() && query_usuario.next()) {
            QString nomeUsuario = query_usuario.value("user_nome").toString();

            ui->_txt_usuario->setText(nomeUsuario);
        } else {
            qDebug() << "Erro ao buscar nome do usuário:" << query_usuario.lastError().text();
        }

        QSqlQuery query_treino(conexao->getConexao());

        query_treino.prepare("SELECT treino_segunda, treino_terca, treino_quarta, treino_quinta, treino_sexta, treino_comentario FROM table_treino WHERE user_id = ?");
        query_treino.addBindValue(_user_id);

        if (query_treino.exec() && query_treino.next()) {
            QString segunda = query_treino.value("treino_segunda").toString();
            QString terca = query_treino.value("treino_terca").toString();
            QString quarta = query_treino.value("treino_quarta").toString();
            QString quinta = query_treino.value("treino_quinta").toString();
            QString sexta = query_treino.value("treino_sexta").toString();
            QString comentario = query_treino.value("treino_comentario").toString();

            ui->_txt_segunda_user->setText(segunda);
            ui->_txt_terca_user->setText(terca);
            ui->_txt_quarta_user->setText(quarta);
            ui->_txt_quinta_user->setText(quinta);
            ui->_txt_sexta_user->setText(sexta);
            ui->_te_comentario->setText(comentario);

        } else {
            qDebug() << "Erro ao buscar dados do treino do cliente:" << query_treino.lastError().text();
        }
    }
}

void janela_editar_treino::abrirJanelaAdicionaExercicio(QLabel *campoAlvo){
    campoAtual = campoAlvo;

    adiciona_atividade = new janela_adiciona_atividade(this);

    connect(adiciona_atividade, &janela_adiciona_atividade::atividadeAdicionada, this, [this](const QString& atividade) {
        QString textoAtual = campoAtual->text();
        if(textoAtual.isEmpty()) {
            campoAtual->setText(atividade);
        } else {
            campoAtual->setText(textoAtual + ", " + atividade);
        }
    });

    connect(adiciona_atividade, &QMainWindow::destroyed, adiciona_atividade, &QObject::deleteLater);

    adiciona_atividade->show();
}

janela_editar_treino::janela_editar_treino(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_editar_treino)
{
    ui->setupUi(this);

    conexao = Conexao::getInstance();
}

janela_editar_treino::~janela_editar_treino()
{
    delete ui;
}

void janela_editar_treino::on__btn_salvar_clicked()
{
    QString segunda = ui->_txt_segunda_user->text();
    QString terca = ui->_txt_terca_user->text();
    QString quarta = ui->_txt_quarta_user->text();
    QString quinta = ui->_txt_quinta_user->text();
    QString sexta = ui->_txt_sexta_user->text();
    QString comentario = ui->_te_comentario->toPlainText();

    try {
        QSqlQuery query_treino(conexao->getConexao());

        query_treino.prepare("UPDATE table_treino SET "
                            "treino_segunda = ?, "
                            "treino_terca = ?, "
                            "treino_quarta = ?, "
                            "treino_quinta = ?, "
                            "treino_sexta = ?, "
                            "treino_comentario = ? "
                            "WHERE user_id = ?");

        query_treino.addBindValue(segunda);
        query_treino.addBindValue(terca);
        query_treino.addBindValue(quarta);
        query_treino.addBindValue(quinta);
        query_treino.addBindValue(sexta);
        query_treino.addBindValue(comentario);
        query_treino.addBindValue(_user_id);

        if (!query_treino.exec()) {
            throw std::runtime_error(query_treino.lastError().text().toStdString());
        }

        QMessageBox::information(this, "Sucesso", "Treino atualizado com sucesso!");
        this->close();
    }
    catch (const std::exception& e) {
        qDebug() << "Erro ao atualizar o treino:" << e.what();
        QMessageBox::critical(this, "Erro", "Não foi possível atualizar o treino.");
    }
}

void janela_editar_treino::removerUltimaAtividade(QLabel* campoAlvo) {
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

void janela_editar_treino::on__btn_segunda_clicked()
{
    abrirJanelaAdicionaExercicio(ui->_txt_segunda_user);
}


void janela_editar_treino::on__btn_terca_clicked()
{
    abrirJanelaAdicionaExercicio(ui->_txt_terca_user);
}


void janela_editar_treino::on__btn_quarta_clicked()
{
    abrirJanelaAdicionaExercicio(ui->_txt_quarta_user);
}


void janela_editar_treino::on__btn_quinta_clicked()
{
    abrirJanelaAdicionaExercicio(ui->_txt_quinta_user);
}


void janela_editar_treino::on__btn_sexta_clicked()
{
    abrirJanelaAdicionaExercicio(ui->_txt_sexta_user);
}


void janela_editar_treino::on__btn_segunda_2_clicked()
{
    removerUltimaAtividade(ui->_txt_segunda_user);
}


void janela_editar_treino::on__btn_terca_2_clicked()
{
    removerUltimaAtividade(ui->_txt_terca_user);
}


void janela_editar_treino::on__btn_quarta_2_clicked()
{
    removerUltimaAtividade(ui->_txt_quarta_user);
}


void janela_editar_treino::on__btn_quinta_2_clicked()
{
    removerUltimaAtividade(ui->_txt_quinta_user);
}


void janela_editar_treino::on__btn_sexta_2_clicked()
{
    removerUltimaAtividade(ui->_txt_sexta_user);
}

