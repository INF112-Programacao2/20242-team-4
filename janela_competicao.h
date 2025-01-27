#ifndef JANELA_COMPETICAO_H
#define JANELA_COMPETICAO_H

#include <QMainWindow>
#include <QMessageBox>

#include "conexao.h"

namespace Ui {
class janela_competicao;
}

class janela_competicao : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_competicao(int competicaoNivel, QWidget *parent = nullptr);
    ~janela_competicao();

private slots:
    void on__btn_voltar_clicked();

private:
    Ui::janela_competicao *ui;

    Conexao *conexao;

    int nivel;
};

#endif // JANELA_COMPETICAO_H
