#ifndef JANELA_MENU_INICIAL_H
#define JANELA_MENU_INICIAL_H

#include <QMainWindow>

namespace Ui {
class janela_menu_inicial;
}

class janela_menu_inicial : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_menu_inicial(QWidget *parent = nullptr);
    ~janela_menu_inicial();

private slots:
    void on_pushButton_6_clicked();

private:
    Ui::janela_menu_inicial *ui;
};

#endif // JANELA_MENU_INICIAL_H
