#ifndef JANELA_EDITAR_DIETA_H
#define JANELA_EDITAR_DIETA_H

#include <QMainWindow>

#include "conexao.h"
#include "janela_adiciona_prato.h"

namespace Ui {
class janela_editar_dieta;
}

class janela_editar_dieta : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_editar_dieta(QWidget *parent = nullptr);
    ~janela_editar_dieta();

    void setUserId(int id);

    void setNutriId(int id);

private slots:
    void on__btn_salvar_clicked();

    void on__btn_cafedamanha_clicked();

    void on__btn_lanchedamanha_clicked();

    void on__btn_almoco_clicked();

    void on__btn_lanchedatarde_clicked();

    void on__btn_jantar_clicked();

    void on__btn_ceia_clicked();

    void on__btn_cafedamanha_2_clicked();

    void on__btn_lanchedamanha_2_clicked();

    void on__btn_almoco_2_clicked();

    void on__btn_lanchedatarde_2_clicked();

    void on__btn_jantar_2_clicked();

    void on__btn_ceia_2_clicked();

private:
    Ui::janela_editar_dieta *ui;

    int _user_id;

    Conexao *conexao;

    janela_adiciona_prato* janela_prato;

    void abrirJanelaAdicionaPrato(QLabel* campoAlvo);

    void removerUltimoPrato(QLabel* campoAlvo);

    QLabel *campoAtual; //lembrar qual campo está sendo adicionado

    int _nutri_id;
};

#endif // JANELA_EDITAR_DIETA_H
