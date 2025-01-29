#ifndef JANELA_CRIAR_UPROFISSIONAL_H
#define JANELA_CRIAR_UPROFISSIONAL_H

#include <QMainWindow>
#include <QMessageBox>

#include "conexao.h"
#include "janela_menu_personal.h"
#include "janela_menu_nutricionista.h"

namespace Ui {
class janela_criar_uprofissional;
}

class janela_criar_uprofissional : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_criar_uprofissional(QWidget *parent = nullptr);
    ~janela_criar_uprofissional();

    void setUserId(int id);

private slots:
    void on__btn_confirmar_clicked();

private:
    Ui::janela_criar_uprofissional *ui;

    int _user_id;

    Conexao *conexao;

    janela_menu_nutricionista *menu_nutricionista;

    janela_menu_personal *menu_personal;
};

#endif // JANELA_CRIAR_UPROFISSIONAL_H
