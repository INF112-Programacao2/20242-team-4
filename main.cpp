#include "janela_inicial.h"
#include "conexao.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Conexao* conexao = Conexao::getInstance();

    if (!conexao->abrir()){
        qDebug() << "Erro ao localizar o banco de dados";
        return -1;
    }

    QSqlDatabase BancoDeDados = conexao->getConexao();

    if (!BancoDeDados.open()) {
        qDebug() << "Erro ao abrir o banco de dados";
        qDebug() << "Erro:" << BancoDeDados.lastError().text();
        return -1;
    } else {
        qDebug() << "Banco de dados aberto com sucesso!";
    }

    janela_inicial w;
    w.show();

    Conexao::destroyInstance();
    return a.exec();
}
