#ifndef JANELA_MENU_INICIAL_H
#define JANELA_MENU_INICIAL_H

#include <QMainWindow>

#include "conexao.h"
#include "janela_perfil_usuario.h"
#include "janela_dieta_usuario.h"
#include "janela_treino_usuario.h"
#include "janela_entrar_competicao.h"
#include "janela_ve_competicoes.h"
#include "janela_checkins.h"

namespace Ui {
class janela_menu_inicial;
}

class janela_menu_inicial : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_menu_inicial(QWidget *parent = nullptr);
    ~janela_menu_inicial();

    void setUserId(int id);

private slots:
    void on__btn_checkin_clicked();

    void on__btn_perfil_clicked();

    void on__btn_dieta_clicked();

    void on__btn_treino_clicked();

    void on__btn_go_competicao_clicked();

    void on__btn_my_competicao_clicked();

private:
    Ui::janela_menu_inicial *ui;

    int _user_id;

    Conexao* conexao;

    janela_perfil_usuario *perfil_usuario;

    janela_dieta_usuario *dieta_usuario;

    janela_treino_usuario *treino_usuario;

    janela_entrar_competicao *entrar_competicao;

    janela_ve_competicoes *ve_competicao;

    janela_checkins *checkins;
};

#endif // JANELA_MENU_INICIAL_H
