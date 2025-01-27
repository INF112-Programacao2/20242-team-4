#ifndef USUARIO_PADRAO_H
#define USUARIO_PADRAO_H

#include <QMessageBox>
#include <QDate>
#include <stdexcept>

#include "conexao.h"
#include "usuario.h"

class usuario_padrao : public usuario
{
    QString user_datadenascimento;
    double user_peso;
    double user_altura;
    int user_checkins;
    int user_ndias;
    int user_idpersonal;
    int user_idnutricionista;
    QString user_objetivo;

public:
    usuario_padrao();

    void setDatadenascimento(const QString &datadenascimento);

    void setPeso(const double &peso);

    void setAltura(const double &altura);

    void setCheckins(const int &checkins);

    void setNdias(const int &ndias);

    void setIDpersonal(const int &idpersonal);

    void setIDnutricionista(const int &idnutricionista);

    void setObjetivo(const QString &objetivo);

    bool validarDados(const QString &peso, const QString &altura, const QString &dataNascimento, const QString &objetivo);
    bool cadastrarPerfilCompleto(Conexao* conexao, int userId);
};

#endif // USUARIO_PADRAO_H
