#ifndef JANELA_DIETA_USUARIO_H
#define JANELA_DIETA_USUARIO_H

#include <QMainWindow>

namespace Ui {
class janela_dieta_usuario;
}

class janela_dieta_usuario : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_dieta_usuario(QWidget *parent = nullptr);
    ~janela_dieta_usuario();

private:
    Ui::janela_dieta_usuario *ui;
};

#endif // JANELA_DIETA_USUARIO_H
