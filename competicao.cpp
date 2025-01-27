#include "competicao.h"

competicao::competicao() {}

void competicao::setUserID(int userID){
    user_id = userID;
}

void competicao::setPontuacao(int pontuacao){
    user_pontuacao = pontuacao;
}

bool competicao::verificaParticipacao(Conexao *conexao, const int &userID, int dificuldade){
    if (dificuldade == 1){
        QSqlQuery query(conexao->getConexao());
        query.prepare("SELECT COUNT(*) FROM table_comp_iniciantes WHERE user_id = ?");
        query.addBindValue(user_id);

        if (query.exec() && query.next()) {
            int count = query.value(0).toInt();
            return count > 0;
        }
        return false;

    } else if (dificuldade == 2){
        QSqlQuery query(conexao->getConexao());
        query.prepare("SELECT COUNT(*) FROM table_comp_amador WHERE user_id = ?");
        query.addBindValue(user_id);

        if (query.exec() && query.next()) {
            int count = query.value(0).toInt();
            return count > 0;
        }
        return false;

    } else if (dificuldade == 3){
        QSqlQuery query(conexao->getConexao());
        query.prepare("SELECT COUNT(*) FROM table_comp_intermediario WHERE user_id = ?");
        query.addBindValue(user_id);

        if (query.exec() && query.next()) {
            int count = query.value(0).toInt();
            return count > 0;
        }
        return false;

    } else {
        QSqlQuery query(conexao->getConexao());
        query.prepare("SELECT COUNT(*) FROM table_comp_avancado WHERE user_id = ?");
        query.addBindValue(user_id);

        if (query.exec() && query.next()) {
            int count = query.value(0).toInt();
            return count > 0;
        }
        return false;

    }

}

bool competicao::adicionaNovoCompetidor(Conexao *conexao, int dificuldade){
    // 1 - iniciante 2 - amador 3 - intermediário 4 - avançado

    if (dificuldade == 1){
        QSqlQuery query(conexao->getConexao());

        query.prepare("INSERT INTO table_comp_iniciantes (user_id, user_pontuacao) VALUES (?, ?)");
        query.addBindValue(user_id);
        query.addBindValue(0);

        if (query.exec()) {
            return true;
        } else {
            qDebug() << "Erro ao inserir competidor:" << query.lastError().text();
            return false;
        }
    } else if (dificuldade == 2){
        QSqlQuery query(conexao->getConexao());

        query.prepare("INSERT INTO table_comp_amador (user_id, user_pontuacao) VALUES (?, ?)");
        query.addBindValue(user_id);
        query.addBindValue(0);

        if (query.exec()) {
            return true;
        } else {
            qDebug() << "Erro ao inserir competidor:" << query.lastError().text();
            return false;
        }
    } else if (dificuldade == 3){
        QSqlQuery query(conexao->getConexao());

        query.prepare("INSERT INTO table_comp_intermediario (user_id, user_pontuacao) VALUES (?, ?)");
        query.addBindValue(user_id);
        query.addBindValue(0);

        if (query.exec()) {
            return true;
        } else {
            qDebug() << "Erro ao inserir competidor:" << query.lastError().text();
            return false;
        }
    } else {
        QSqlQuery query(conexao->getConexao());

        query.prepare("INSERT INTO table_comp_avancado (user_id, user_pontuacao) VALUES (?, ?)");
        query.addBindValue(user_id);
        query.addBindValue(0);

        if (query.exec()) {
            return true;
        } else {
            qDebug() << "Erro ao inserir competidor:" << query.lastError().text();
            return false;
        }
    }
}
