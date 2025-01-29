#ifndef JANELA_ADICIONA_EDICAO_H
#define JANELA_ADICIONA_EDICAO_H

#include <QMainWindow>
#include <QMessageBox>

#include "conexao.h"
#include "usuario.h"
#include "usuario_padrao.h"


namespace Ui {
class janela_adiciona_edicao;
}

class janela_adiciona_edicao : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_adiciona_edicao(QWidget *parent = nullptr);
    ~janela_adiciona_edicao();

    void setUserId(int id);

private slots:
    void on__btn_confirma_clicked();

private:
    Ui::janela_adiciona_edicao *ui;

    int _user_id;

    Conexao *conexao;

signals:
    void voltarPerfil();
};

#endif // JANELA_ADICIONA_EDICAO_H
