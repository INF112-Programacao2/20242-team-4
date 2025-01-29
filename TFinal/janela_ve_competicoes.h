#ifndef JANELA_VE_COMPETICOES_H
#define JANELA_VE_COMPETICOES_H

#include <QMainWindow>
#include <QMessageBox>

#include "conexao.h"
#include "janela_competicao.h"

namespace Ui {
class janela_ve_competicoes;
}

class janela_ve_competicoes : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_ve_competicoes(QWidget *parent = nullptr);
    ~janela_ve_competicoes();

    void setUserId(int id);

private slots:
    void on__btn_voltar_clicked();

    void on__btn_acessar_clicked();

signals:
    void voltarMenuInicial();

private:
    Ui::janela_ve_competicoes *ui;

    int _user_id;

    Conexao* conexao;

    void carregarCompetições();

    janela_competicao *j_competicao = nullptr;
};

#endif // JANELA_VE_COMPETICOES_H
