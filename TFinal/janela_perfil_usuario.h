#ifndef JANELA_PERFIL_USUARIO_H
#define JANELA_PERFIL_USUARIO_H

#include <QMainWindow>

#include "conexao.h"
#include "janela_adiciona_edicao.h"

namespace Ui {
class janela_perfil_usuario;
}

class janela_perfil_usuario : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_perfil_usuario(QWidget *parent = nullptr);
    ~janela_perfil_usuario();

    void setUserId(int id);

private slots:
    void on__btn_voltar_clicked();

    void on__btn_editar_clicked();

private:
    Ui::janela_perfil_usuario *ui;

    int _user_id;

    Conexao* conexao;

    janela_adiciona_edicao *adiciona_edicao;

signals:
    void voltarMenuInicial();
};

#endif // JANELA_PERFIL_USUARIO_H
