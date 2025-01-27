#ifndef JANELA_EDITAR_TREINO_H
#define JANELA_EDITAR_TREINO_H

#include <QMainWindow>
#include <QLabel>

#include "conexao.h"
#include "janela_adiciona_atividade.h"

namespace Ui {
class janela_editar_treino;
}

class janela_editar_treino : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_editar_treino(QWidget *parent = nullptr);
    ~janela_editar_treino();

    void setUserId(int id);

private slots:
    void on__btn_salvar_clicked();

    void on__btn_segunda_clicked();

    void on__btn_terca_clicked();

    void on__btn_quarta_clicked();

    void on__btn_quinta_clicked();

    void on__btn_sexta_clicked();

    void on__btn_segunda_2_clicked();

    void on__btn_terca_2_clicked();

    void on__btn_quarta_2_clicked();

    void on__btn_quinta_2_clicked();

    void on__btn_sexta_2_clicked();

private:
    Ui::janela_editar_treino *ui;

    int _user_id;

    Conexao *conexao;

    janela_adiciona_atividade *adiciona_atividade;

    void removerUltimaAtividade(QLabel* campoAlvo);

    void abrirJanelaAdicionaExercicio(QLabel *campoAlvo);

    QLabel *campoAtual;
};

#endif // JANELA_EDITAR_TREINO_H
