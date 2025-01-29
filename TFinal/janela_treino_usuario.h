#ifndef JANELA_TREINO_USUARIO_H
#define JANELA_TREINO_USUARIO_H

#include <QMainWindow>
#include <QMessageBox>

#include "conexao.h"
#include "janela_profissional_usuario.h"

namespace Ui {
class janela_treino_usuario;
}

class janela_treino_usuario : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_treino_usuario(QWidget *parent = nullptr);
    ~janela_treino_usuario();

    void setUserId(int id);

private:
    Ui::janela_treino_usuario *ui;

    int _user_id;

    Conexao *conexao;

    janela_profissional_usuario *profissional_usuario;

signals:
    void voltarMenuInicial();

private slots:
    void on__btn_voltar_clicked();

    void on__btn_personal_clicked();
};

#endif // JANELA_TREINO_USUARIO_H
