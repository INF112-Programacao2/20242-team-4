#ifndef JANELA_PROFISSIONAL_USUARIO_H
#define JANELA_PROFISSIONAL_USUARIO_H

#include <QMainWindow>
#include <QMessageBox>

#include "conexao.h"

namespace Ui {
class janela_profissional_usuario;
}

class janela_profissional_usuario : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_profissional_usuario(QWidget *parent = nullptr);
    ~janela_profissional_usuario();

    void setUserId(int id);

    void setTipoProfissional(bool isNutricionista); // true para nutricionista, false para personal

private slots:
    void on__btn_salvar_clicked();

    void on__btn_voltar_clicked();

private:
    Ui::janela_profissional_usuario *ui;

    int _user_id;

    bool _isNutricionista;

    Conexao *conexao;

    void carregarDadosProfissional();

    void carregarListaProfissionais();

signals:
    void dadosSalvos();
};

#endif // JANELA_PROFISSIONAL_USUARIO_H
