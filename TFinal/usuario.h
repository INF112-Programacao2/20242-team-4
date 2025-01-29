#ifndef USUARIO_H
#define USUARIO_H

#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>

#include "conexao.h"
#include "Message_Style.h"

class usuario
{
protected:
    int user_id;
    QString user_nome;
    QString user_email;
    QString user_senha;
    int user_tipo;

public:
    usuario();

    void setNome(const QString& nome);

    void setEmail(const QString& email);

    void setSenha(const QString& senha);

    bool cadastrar(Conexao* conexao);

    bool validarEmail(const QString& email);

    bool emailJaCadastrado(Conexao* conexao, const QString& email);

    bool validarCadastro(const QString& nome, const QString& email, const QString& senha, const QString& confirmaSenha);
};

#endif // USUARIO_H
