#ifndef JANELA_ENTRAR_COMPETICAO_H
#define JANELA_ENTRAR_COMPETICAO_H

#include <QMainWindow>
#include <QMessageBox>

#include "conexao.h"
#include "competicao.h"

namespace Ui {
class janela_entrar_competicao;
}

class janela_entrar_competicao : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_entrar_competicao(QWidget *parent = nullptr);
    ~janela_entrar_competicao();

    void setUserId(int id);

private slots:
    void on__btn_iniciante_clicked();

    void on__btn_amador_clicked();

    void on__btn_intermediario_clicked();

    void on__btn_avancado_clicked();

    void on__btn_voltar_clicked();

signals:
    void voltarMenuInicial();

private:
    Ui::janela_entrar_competicao *ui;

    int _user_id;

    Conexao* conexao;

    void verificarParticipacoes();
};

#endif // JANELA_ENTRAR_COMPETICAO_H
