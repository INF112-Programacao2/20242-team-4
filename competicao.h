#ifndef COMPETICAO_H
#define COMPETICAO_H

#include <QMessageBox>
#include "conexao.h"

class competicao
{
protected:
    int user_id;
    int user_pontuacao;

public:
    competicao();

    void setUserID(int userID);

    void setPontuacao(int pontuacao);

    bool adicionaNovoCompetidor(Conexao *conexao, int dificuldade);

    bool verificaParticipacao(Conexao *conexao, const int &userID, int dificuldade);

};

#endif // COMPETICAO_H
