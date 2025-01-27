#include "janela_checkins.h"
#include "ui_janela_checkins.h"

void janela_checkins::setUserId(int id) {
    this->_user_id = id;
    if (!conexao->abrir()) {
        qDebug() << "Erro ao abrir conexão com banco de dados";
        return;
    }
}

void janela_checkins::inserirImagem() {
    QString filePath = QFileDialog::getOpenFileName(this, "Selecionar Imagem", "", "Imagens (*.png *.jpg *.jpeg *.bmp)");
    if (!filePath.isEmpty()) {
        QTextCursor cursor = ui->_te_foto->textCursor();
        cursor.insertImage(filePath);
    }
}

janela_checkins::janela_checkins(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_checkins)
{
    ui->setupUi(this);

    conexao = Conexao::getInstance();

    connect(ui->_btn_inserir_imagem, &QPushButton::clicked, this, &janela_checkins::inserirImagem);
}

janela_checkins::~janela_checkins()
{
    delete ui;
}

void janela_checkins::on__btn_voltar_clicked()
{
    emit voltarMenuInicial();
    this->close();
}

enum Dificuldade {
    INICIANTE = 1,
    AMADOR = 2,
    INTERMEDIARIO = 3,
    AVANCADO = 4
};

void janela_checkins::on__btn_validar_clicked()
{
    QTextDocument *document = ui->_te_foto->document();
    bool imagemEncontrada = false;

    // Percorre todos os blocos do documento
    for (QTextBlock block = document->begin(); block.isValid(); block = block.next()) {
        QTextBlock::iterator it;
        for (it = block.begin(); !(it.atEnd()); ++it) {
            QTextFragment fragment = it.fragment();
            if (fragment.charFormat().isImageFormat()) {
                imagemEncontrada = true;
                break;
            }
        }

        if (imagemEncontrada) break;
    }

    if (!imagemEncontrada) {
        QMessageBox::warning(this, "Erro", "Por favor, insira uma foto!");
        return;
    }

    try {
        QSqlQuery query(conexao->getConexao());
        query.prepare("SELECT user_checkins FROM table_perfil_usuario WHERE user_id = ?");
        query.addBindValue(_user_id);

        if (query.exec() && query.next()) {
            int check = query.value("user_checkins").toInt() + 1;

            conexao->getConexao().transaction();

            QSqlQuery queryUpdate(conexao->getConexao());
            queryUpdate.prepare("UPDATE table_perfil_usuario SET user_checkins = ? WHERE user_id = ?");
            queryUpdate.addBindValue(check);
            queryUpdate.addBindValue(_user_id);

            if (!queryUpdate.exec()) {
                throw std::runtime_error(queryUpdate.lastError().text().toStdString());
            }

            competicao comp;
            comp.setUserID(_user_id);

            bool participaCompeticao = false;

            const int pontosIniciante = 100;
            const int pontosAmador = 50;
            const int pontosIntermediario = 20;
            const int pontosAvancado = 10;

            if (comp.verificaParticipacao(conexao, _user_id, INICIANTE)) {
                QSqlQuery queryIniciante(conexao->getConexao());
                queryIniciante.prepare("UPDATE table_comp_iniciantes SET user_pontuacao = user_pontuacao + ? WHERE user_id = ?");
                queryIniciante.addBindValue(pontosIniciante);
                queryIniciante.addBindValue(_user_id);
                if (!queryIniciante.exec()) {
                    conexao->getConexao().rollback();
                    throw std::runtime_error(queryIniciante.lastError().text().toStdString());
                }

                participaCompeticao = true;
            }
            if (comp.verificaParticipacao(conexao, _user_id, AMADOR)) {
                QSqlQuery queryAmador(conexao->getConexao());
                queryAmador.prepare("UPDATE table_comp_amador SET user_pontuacao = user_pontuacao + ? WHERE user_id = ?");
                queryAmador.addBindValue(pontosAmador);
                queryAmador.addBindValue(_user_id);
                if (!queryAmador.exec()) {
                    conexao->getConexao().rollback();
                    throw std::runtime_error(queryAmador.lastError().text().toStdString());
                }

                participaCompeticao = true;
            }
            if (comp.verificaParticipacao(conexao, _user_id, INTERMEDIARIO)) {
                QSqlQuery queryIntermediario(conexao->getConexao());
                queryIntermediario.prepare("UPDATE table_comp_intermediario SET user_pontuacao = user_pontuacao + ? WHERE user_id = ?");
                queryIntermediario.addBindValue(pontosIntermediario);
                queryIntermediario.addBindValue(_user_id);
                if (!queryIntermediario.exec()) {
                    conexao->getConexao().rollback();
                    throw std::runtime_error(queryIntermediario.lastError().text().toStdString());
                }

                participaCompeticao = true;
            }
            if (comp.verificaParticipacao(conexao, _user_id, AVANCADO)) {
                QSqlQuery queryAvancado(conexao->getConexao());
                queryAvancado.prepare("UPDATE table_comp_avancado SET user_pontuacao = user_pontuacao + ? WHERE user_id = ?");
                queryAvancado.addBindValue(pontosAvancado);
                queryAvancado.addBindValue(_user_id);
                if (!queryAvancado.exec()) {
                    conexao->getConexao().rollback();
                    throw std::runtime_error(queryAvancado.lastError().text().toStdString());
                }

                participaCompeticao = true;
            }

            if (!participaCompeticao) {
                conexao->getConexao().rollback();
                QMessageBox::information(this, "Ops", "Você não participa de nenhuma competição!");
                emit voltarMenuInicial();
                this->close();
                return;
            }

            if (participaCompeticao) {
                QSqlQuery queryDias(conexao->getConexao());
                queryDias.prepare("SELECT user_data FROM table_checkin WHERE user_id = ?");
                queryDias.addBindValue(_user_id);

                if (queryDias.exec() && queryDias.next()) {
                    QString datac = queryDias.value("user_data").toString();
                    QDate dataAtual = QDate::currentDate();

                    if (datac != dataAtual.toString("dd/MM/yyyy")) {
                        // Atualiza a data do último check-in
                        queryDias.prepare("UPDATE table_checkin SET user_data = ? WHERE user_id = ?");
                        queryDias.addBindValue(dataAtual.toString("dd/MM/yyyy"));
                        queryDias.addBindValue(_user_id);

                        if (!queryDias.exec()) {
                            conexao->getConexao().rollback();
                            throw std::runtime_error(queryDias.lastError().text().toStdString());
                        }

                        // Busca o número atual de dias consecutivos
                        QSqlQuery queryNDIAS(conexao->getConexao());
                        queryNDIAS.prepare("SELECT user_ndias FROM table_perfil_usuario WHERE user_id = ?");
                        queryNDIAS.addBindValue(_user_id);

                        if (queryNDIAS.exec() && queryNDIAS.next()) {
                            int ndias = queryNDIAS.value("user_ndias").toInt() + 1;

                            // Atualiza o número de dias consecutivos
                            QSqlQuery querynewUpdate(conexao->getConexao());
                            querynewUpdate.prepare("UPDATE table_perfil_usuario SET user_ndias = ? WHERE user_id = ?");
                            querynewUpdate.addBindValue(ndias);
                            querynewUpdate.addBindValue(_user_id);

                            if (!querynewUpdate.exec()) {
                                conexao->getConexao().rollback();
                                throw std::runtime_error(querynewUpdate.lastError().text().toStdString());
                            }
                        } else {
                            conexao->getConexao().rollback();
                            throw std::runtime_error("Erro ao buscar número de dias consecutivos");
                        }
                    }
                } else {
                    conexao->getConexao().rollback();
                    throw std::runtime_error("Erro ao buscar data do último check-in");
                }
            }

            if (conexao->getConexao().commit()) {
                QMessageBox::information(this, "Sucesso", "Check-in realizado com sucesso!");
                emit voltarMenuInicial();
                this->close();
            } else {
                conexao->getConexao().rollback();
                throw std::runtime_error("Erro ao confirmar transação");
            }
        }
    }
    catch (const std::exception& e) {
        qDebug() << "Erro ao salvar checkin:" << e.what();
        QMessageBox::critical(this, "Erro", "Não foi possível realizar o check-in.");
    }
}

