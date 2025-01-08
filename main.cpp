#include "janela_inicial.h"

#include <QApplication>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase BancoDeDados = QSqlDatabase::addDatabase("QSQLITE");

    BancoDeDados.setDatabaseName("C:/Users/mario/Documents/TFinal/BD/bd.db");

    QFileInfo checkFile("C:/Users/mario/Documents/TFinal/BD/bd.db");
    if (checkFile.exists() && checkFile.isFile()) {
        qDebug() << "Arquivo do banco de dados existe";
    } else {
        qDebug() << "Arquivo do banco de dados NÃO existe";
    }

    if (!BancoDeDados.open()) {
        qDebug() << "Erro ao abrir o banco de dados";
        qDebug() << "Erro:" << BancoDeDados.lastError().text();  // Adicione esta linha
    } else {
        qDebug() << "Banco de dados aberto com sucesso!";
    }

    janela_inicial w;
    w.show();
    return a.exec();
}
