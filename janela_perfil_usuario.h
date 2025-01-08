#ifndef JANELA_PERFIL_USUARIO_H
#define JANELA_PERFIL_USUARIO_H

#include <QMainWindow>

namespace Ui {
class janela_perfil_usuario;
}

class janela_perfil_usuario : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_perfil_usuario(QWidget *parent = nullptr);
    ~janela_perfil_usuario();

private:
    Ui::janela_perfil_usuario *ui;
};

#endif // JANELA_PERFIL_USUARIO_H
