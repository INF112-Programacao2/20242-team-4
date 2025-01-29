#ifndef JANELA_DIETA_USUARIO_H
#define JANELA_DIETA_USUARIO_H

#include <QMainWindow>

#include "conexao.h"
#include "janela_profissional_usuario.h"

namespace Ui {
class janela_dieta_usuario;
}

class janela_dieta_usuario : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_dieta_usuario(QWidget *parent = nullptr);
    ~janela_dieta_usuario();

    void setUserId(int id);

private:
    Ui::janela_dieta_usuario *ui;

    int _user_id;

    Conexao *conexao;

    janela_profissional_usuario *profissional_usuario;

signals:
    void voltarMenuInicial();

private slots:
    void on__btn_voltar_clicked();
    void on__btn_nutricionista_clicked();
};

#endif // JANELA_DIETA_USUARIO_H
