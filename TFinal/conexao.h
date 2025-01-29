#ifndef CONEXAO_H
#define CONEXAO_H

#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QFileInfo>

class Conexao {
    private:
    	static Conexao* instance;
        QSqlDatabase BancoDeDados;
        Conexao();
    
    public:
    	static Conexao* getInstance();

        static void destroyInstance();

        ~Conexao();

        bool abrir();          // cria a conexão

        void fechar();         // fechar a conexão

        QSqlDatabase& getConexao();   // obtem a conexão

};

#endif // CONEXAO_H
