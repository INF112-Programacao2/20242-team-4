#include "conexao.h"

Conexao* Conexao::instance = nullptr;

Conexao::Conexao(){
    if (QSqlDatabase::contains("MyConnection")) {
        BancoDeDados = QSqlDatabase::database("MyConnection");
    } else {
        BancoDeDados = QSqlDatabase::addDatabase("QSQLITE", "MyConnection");
    }
}

Conexao* Conexao::getInstance() {
    if (instance == nullptr) {
        instance = new Conexao();
    }
	return instance;
}

void Conexao::destroyInstance() {
    if (instance != nullptr) {
        instance->fechar();
        delete instance;
        instance = nullptr;
    }
}

Conexao::~Conexao(){
    fechar();
}

bool Conexao::abrir(){
    if (BancoDeDados.isOpen()) {
        return true;
    }

    QString Banco = "C:/Users/mario/Documents/TFinal/BD/bd.db";
    BancoDeDados.setDatabaseName(Banco);

    QFileInfo checkFile(Banco);
    if (!checkFile.exists() || !checkFile.isFile()) {
        qDebug() << "Arquivo do banco de dados NÃO existe";
        return false;
    }

    if (!BancoDeDados.open()) {
        qDebug() << "Erro ao abrir banco de dados:" << BancoDeDados.lastError().text();
        return false;
    }

    qDebug() << "Banco de dados conectado com sucesso";
    return true;
}

void Conexao::fechar(){
    if (BancoDeDados.isOpen()) {
        // Finaliza todas as queries pendentes
        QSqlDatabase::database(BancoDeDados.connectionName()).rollback();
        BancoDeDados.close();
    }
}

QSqlDatabase& Conexao::getConexao(){
    return BancoDeDados;
}
