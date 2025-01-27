#ifndef JANELA_ADICIONA_EXERCICIO_H
#define JANELA_ADICIONA_EXERCICIO_H

#include <QMainWindow>

#include "conexao.h"

namespace Ui {
class janela_adiciona_exercicio;
}

class janela_adiciona_exercicio : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_adiciona_exercicio(QWidget *parent = nullptr);
    ~janela_adiciona_exercicio();

signals:
    void exercicioAdicionado(const QString& exercicio);

private:
    Ui::janela_adiciona_exercicio *ui;


};

#endif // JANELA_ADICIONA_EXERCICIO_H
