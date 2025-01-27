#include "janela_treino_usuario.h"
#include "ui_janela_treino_usuario.h"

void janela_treino_usuario::setUserId(int id) {
    this->_user_id = id;
    try {
        if (!conexao->abrir()) {
            throw std::runtime_error("Erro ao abrir conexão com banco de dados");
        }

        QSqlQuery query(conexao->getConexao());

        query.prepare("SELECT treino_segunda, treino_terca, treino_quarta, treino_quinta, treino_sexta, treino_comentario FROM table_treino WHERE user_id = ?");
        query.addBindValue(_user_id);

        if (!query.exec()) {
            throw std::runtime_error(query.lastError().text().toStdString());
        }

        if (query.next()) {
            QString segunda = query.value("treino_segunda").toString();
            QString terca = query.value("treino_terca").toString();
            QString quarta = query.value("treino_quarta").toString();
            QString quinta = query.value("treino_quinta").toString();
            QString sexta = query.value("treino_sexta").toString();
            QString comentario = query.value("treino_comentario").toString();

            ui->_txt_segunda_user->setText(segunda);
            ui->_txt_terca_user->setText(terca);
            ui->_txt_quarta_user->setText(quarta);
            ui->_txt_quinta_user->setText(quinta);
            ui->_txt_sexta_user->setText(sexta);
            ui->_txt_comentario_user->setText(comentario);
        } else {
            throw std::runtime_error("Nenhum treino encontrado para este usuário");
        }
    }
    catch (const std::exception& e) {
        qDebug() << "Erro ao buscar dados do treino do cliente:" << e.what();
        QMessageBox::critical(this, "Erro", "Não foi possível carregar os dados do treino.");
    }
}

janela_treino_usuario::janela_treino_usuario(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_treino_usuario)
{
    ui->setupUi(this);

    conexao = Conexao::getInstance();
}

janela_treino_usuario::~janela_treino_usuario()
{
    delete ui;
}

void janela_treino_usuario::on__btn_voltar_clicked()
{
    emit voltarMenuInicial();
    this->close();
}


void janela_treino_usuario::on__btn_personal_clicked()
{
    profissional_usuario = new janela_profissional_usuario(this);
    profissional_usuario->setUserId(_user_id);
    profissional_usuario->setTipoProfissional(false); // false para personal

    connect(profissional_usuario, &janela_profissional_usuario::dadosSalvos, this, [this]() {
        setUserId(_user_id); // Recarrega os dados após salvar
    });

    connect(profissional_usuario, &QMainWindow::destroyed, profissional_usuario, &QObject::deleteLater);
    profissional_usuario->show();
}

