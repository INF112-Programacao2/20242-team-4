#include "janela_dieta_usuario.h"
#include "ui_janela_dieta_usuario.h"

void janela_dieta_usuario::setUserId(int id) {
    this->_user_id = id;
    {
        if (!conexao->abrir()) {
            qDebug() << "Erro ao abrir conexão com banco de dados";
            return;
        }

        QSqlQuery query(conexao->getConexao());

        query.prepare("SELECT user_cafe_da_manha, user_lanche_da_manha, user_almoco, user_lanche_da_tarde, user_jantar, user_ceia, user_comentario FROM table_dieta WHERE user_id = ?");
        query.addBindValue(_user_id);

        if (query.exec() && query.next()) {
            QString cafedamanha = query.value("user_cafe_da_manha").toString();
            QString lanchedamanha = query.value("user_lanche_da_manha").toString();
            QString almoco = query.value("user_almoco").toString();
            QString lanchedatarde = query.value("user_lanche_da_tarde").toString();
            QString jantar = query.value("user_jantar").toString();
            QString ceia = query.value("user_ceia").toString();
            QString comentario = query.value("user_comentario").toString();

            ui->_txt_cafedamanha_user->setText(cafedamanha);
            ui->_txt_lanchedamanha_user->setText(lanchedamanha);
            ui->_txt_almoco_user->setText(almoco);
            ui->_txt_lanchedatarde_user->setText(lanchedatarde);
            ui->_txt_jantar_user->setText(jantar);
            ui->_txt_ceia_user->setText(ceia);
            ui->_txt_comentario_user->setText(comentario);

        } else {
            qDebug() << "Erro ao buscar dados da dieta do cliente:" << query.lastError().text();
        }
    }
}

janela_dieta_usuario::janela_dieta_usuario(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_dieta_usuario)
{
    ui->setupUi(this);

    conexao = Conexao::getInstance();
}

janela_dieta_usuario::~janela_dieta_usuario()
{
    delete ui;
}

void janela_dieta_usuario::on__btn_voltar_clicked()
{
    emit voltarMenuInicial();
    this->close();
}


void janela_dieta_usuario::on__btn_nutricionista_clicked()
{
    profissional_usuario = new janela_profissional_usuario(this);
    profissional_usuario->setUserId(_user_id);
    profissional_usuario->setTipoProfissional(true); // true para nutricionista

    connect(profissional_usuario, &janela_profissional_usuario::dadosSalvos, this, [this]() {
        setUserId(_user_id); // Recarrega os dados após salvar
    });

    connect(profissional_usuario, &QMainWindow::destroyed, profissional_usuario, &QObject::deleteLater);
    profissional_usuario->show();
}

