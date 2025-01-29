#ifndef JANELA_INICIAL_H
#define JANELA_INICIAL_H

#include <QMainWindow>

#include "janela_login.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class janela_inicial;
}
QT_END_NAMESPACE

class janela_inicial : public QMainWindow
{
    Q_OBJECT

public:
    janela_inicial(QWidget *parent = nullptr);
    ~janela_inicial();

private slots:
    void on__btn_inicio_clicked();

private:
    Ui::janela_inicial *ui;

    janela_login *login;
};
#endif // JANELA_INICIAL_H
