#ifndef JANELA_ADICIONA_PRATO_H
#define JANELA_ADICIONA_PRATO_H

#include <QMainWindow>
#include <QMessageBox>

#include "conexao.h"

namespace Ui {
class janela_adiciona_prato;
}

class janela_adiciona_prato : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_adiciona_prato(QWidget *parent = nullptr);
    ~janela_adiciona_prato();

signals:
    void pratoAdicionado(const QString& prato);

private slots:
    void on__btn_adicionar_clicked();

private:
    Ui::janela_adiciona_prato *ui;

    Conexao *conexao;
};

#endif // JANELA_ADICIONA_PRATO_H
