#ifndef JANELA_PRIMEIRO_LOGIN_H
#define JANELA_PRIMEIRO_LOGIN_H

#include <QMainWindow>

#include "conexao.h"
#include "janela_criar_upadrao.h"
#include "janela_criar_uprofissional.h"

namespace Ui {
class janela_primeiro_login;
}

class janela_primeiro_login : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_primeiro_login(QWidget *parent = nullptr);
    ~janela_primeiro_login();

    void setUserId(int id);

private slots:
    void on__btn_padrao_clicked();

    void on__btn_profissional_clicked();

private:
    Ui::janela_primeiro_login *ui;

    int _user_id;

    Conexao *conexao;

    janela_criar_upadrao *criar_upadrao;

    janela_criar_uprofissional *criar_uprofissional;
};

#endif // JANELA_PRIMEIRO_LOGIN_H
