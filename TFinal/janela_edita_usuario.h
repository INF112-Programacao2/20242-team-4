#ifndef JANELA_EDITA_USUARIO_H
#define JANELA_EDITA_USUARIO_H

#include <QMainWindow>

namespace Ui {
class janela_edita_usuario;
}

class janela_edita_usuario : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_edita_usuario(QWidget *parent = nullptr);
    ~janela_edita_usuario();

private:
    Ui::janela_edita_usuario *ui;
};

#endif // JANELA_EDITA_USUARIO_H
