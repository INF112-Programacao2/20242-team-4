#include "usuario_padrao.h"

usuario_padrao::usuario_padrao() {}

void usuario_padrao::setDatadenascimento(const QString &datadenascimento){
    user_datadenascimento = datadenascimento;
}

void usuario_padrao::setPeso(const double &peso){
    user_peso = peso;
}

void usuario_padrao::setAltura(const double &altura){
    user_altura = altura;
}

void usuario_padrao::setCheckins(const int &checkins){
    user_checkins = checkins;
}

void usuario_padrao::setNdias(const int &ndias){
    user_ndias = ndias;
}

void usuario_padrao::setIDpersonal(const int &idpersonal){
    user_idpersonal = idpersonal;
}

void usuario_padrao::setIDnutricionista(const int &idnutricionista){
    user_idnutricionista = idnutricionista;
}

void usuario_padrao::setObjetivo(const QString &objetivo) {
    user_objetivo = objetivo;
}

bool usuario_padrao::validarDados(const QString &peso, const QString &altura, const QString &dataNascimento, const QString &objetivo) {
    if (peso.isEmpty() || altura.isEmpty() || dataNascimento.isEmpty() || objetivo.isEmpty()) {
        MessageStyle::showWarning(nullptr, "Por favor, preencha todos os campos!");
        return false;
    }

    bool pesoOk, alturaOk;
    double pesoValue = peso.toDouble(&pesoOk);
    double alturaValue = altura.toDouble(&alturaOk);

    if (!pesoOk || pesoValue <= 0) {
        MessageStyle::showWarning(nullptr, "Peso inválido!");
        return false;
    }

    if (!alturaOk || alturaValue <= 0) {
        MessageStyle::showWarning(nullptr, "Altura inválida!");
        return false;
    }

    QDate dataNasc = QDate::fromString(dataNascimento, "dd/MM/yyyy");
    if (!dataNasc.isValid()) {
        MessageStyle::showWarning(nullptr, "Data de nascimento inválida!");
        return false;
    }

    return true;
}

bool usuario_padrao::cadastrarPerfilCompleto(Conexao* conexao, int userId) {
    try {
        conexao->getConexao().transaction();

        // Cadastra perfil do usuário
        QSqlQuery queryPerfil(conexao->getConexao());
        queryPerfil.prepare("INSERT INTO table_perfil_usuario (user_id, user_datanascimento, user_peso, user_altura, user_checkins, user_ndias, user_objetivo) VALUES (?, ?, ?, ?, ?, ?, ?)");
        queryPerfil.addBindValue(userId);
        queryPerfil.addBindValue(user_datadenascimento);
        queryPerfil.addBindValue(user_peso);
        queryPerfil.addBindValue(user_altura);
        queryPerfil.addBindValue(0);  // checkins inicial
        queryPerfil.addBindValue(0);  // ndias inicial
        queryPerfil.addBindValue(user_objetivo);

        if (!queryPerfil.exec()) {
            throw std::runtime_error(queryPerfil.lastError().text().toStdString());
        }

        // Cadastra dieta inicial vazia
        QSqlQuery queryDieta(conexao->getConexao());
        queryDieta.prepare("INSERT INTO table_dieta (user_id, user_cafe_da_manha, user_lanche_da_manha, user_almoco, user_lanche_da_tarde, user_jantar, user_ceia, user_comentario) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
        queryDieta.addBindValue(userId);
        for (int i = 0; i < 7; ++i) {  // 7 campos vazios
            queryDieta.addBindValue("");
        }

        if (!queryDieta.exec()) {
            throw std::runtime_error(queryDieta.lastError().text().toStdString());
        }

        // Cadastra treino inicial vazio
        QSqlQuery queryTreino(conexao->getConexao());
        queryTreino.prepare("INSERT INTO table_treino (user_id, treino_segunda, treino_terca, treino_quarta, treino_quinta, treino_sexta) VALUES (?, ?, ?, ?, ?, ?)");
        queryTreino.addBindValue(userId);
        for (int i = 0; i < 5; ++i) {  // 5 campos vazios
            queryTreino.addBindValue("");
        }

        if (!queryTreino.exec()) {
            throw std::runtime_error(queryTreino.lastError().text().toStdString());
        }

        // Cadastra primeiro check-in
        QSqlQuery queryCheckin(conexao->getConexao());
        queryCheckin.prepare("INSERT INTO table_checkin (user_id, user_data) VALUES (?, ?)");
        queryCheckin.addBindValue(userId);
        queryCheckin.addBindValue(QDate::currentDate().toString("dd/MM/yyyy"));

        if (!queryCheckin.exec()) {
            throw std::runtime_error(queryCheckin.lastError().text().toStdString());
        }

        if (!conexao->getConexao().commit()) {
            throw std::runtime_error("Erro ao confirmar transação");
        }

        return true;

    } catch (const std::exception& e) {
        conexao->getConexao().rollback();
        qDebug() << "Erro ao cadastrar perfil completo:" << e.what();
        MessageStyle::showWarning(nullptr, "Não foi possível completar o cadastro.");
        return false;
    }
}

