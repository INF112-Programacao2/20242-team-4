#ifndef JANELA_ADICIONA_ATIVIDADE_H
#define JANELA_ADICIONA_ATIVIDADE_H

#include <QMainWindow>
#include <QMessageBox>

#include "conexao.h"

namespace Ui {
class janela_adiciona_atividade;
}

class janela_adiciona_atividade : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_adiciona_atividade(QWidget *parent = nullptr);
    ~janela_adiciona_atividade();

signals:
    void atividadeAdicionada(const QString& atividade);

private slots:
    void on__btn_adicionar_clicked();

private:
    Ui::janela_adiciona_atividade *ui;

    Conexao *conexao;
};

#endif // JANELA_ADICIONA_ATIVIDADE_H
