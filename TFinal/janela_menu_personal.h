#ifndef JANELA_MENU_PERSONAL_H
#define JANELA_MENU_PERSONAL_H

#include <QMainWindow>
#include <QMessageBox>

#include "conexao.h"
#include "janela_editar_treino.h"

namespace Ui {
class janela_menu_personal;
}

class janela_menu_personal : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_menu_personal(QWidget *parent = nullptr);
    ~janela_menu_personal();

    void setUserId(int id);

private slots:
    void on__btn_editar_clicked();

    void on__btn_excluir_clicked();

    void on__btn_pesquisar_clicked();

private:
    Ui::janela_menu_personal *ui;

    int _user_id;

    Conexao* conexao;

    janela_editar_treino *editar;
};

#endif // JANELA_MENU_PERSONAL_H
