#ifndef JANELA_CRIAR_UPADRAO_H
#define JANELA_CRIAR_UPADRAO_H

#include <QMainWindow>
#include <QMessageBox>

#include "conexao.h"
#include "janela_menu_inicial.h"
#include "usuario.h"
#include "usuario_padrao.h"

namespace Ui {
class janela_criar_upadrao;
}

class janela_criar_upadrao : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_criar_upadrao(QWidget *parent = nullptr);
    ~janela_criar_upadrao();

    void setUserId(int id);

private slots:
    void on__btn_confirma_clicked();

private:
    Ui::janela_criar_upadrao *ui;

    int _user_id;

    Conexao *conexao;

    janela_menu_inicial *menu_incial;
};

#endif // JANELA_CRIAR_UPADRAO_H
