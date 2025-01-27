#ifndef JANELA_MENU_NUTRICIONISTA_H
#define JANELA_MENU_NUTRICIONISTA_H

#include <QMainWindow>
#include <QMessageBox>

#include "conexao.h"
#include "janela_editar_dieta.h"

namespace Ui {
class janela_menu_nutricionista;
}

class janela_menu_nutricionista : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_menu_nutricionista(QWidget *parent = nullptr);
    ~janela_menu_nutricionista();

    void setUserId(int id);

private slots:
    void on__btn_editar_clicked();

    void on__btn_excluir_clicked();

    void on__btn_pesquisar_clicked();

private:
    Ui::janela_menu_nutricionista *ui;

    int _user_id;

    Conexao* conexao;

    janela_editar_dieta *editar;
};

#endif // JANELA_MENU_NUTRICIONISTA_H
