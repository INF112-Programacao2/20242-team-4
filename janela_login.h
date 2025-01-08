#ifndef JANELA_LOGIN_H
#define JANELA_LOGIN_H

#include <QDialog>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>

#include "janela_cadastro.h"
#include "janela_menu_inicial.h"

namespace Ui {
class janela_login;
}

class janela_login : public QDialog
{
    Q_OBJECT

public:
    explicit janela_login(QWidget *parent = nullptr);
    ~janela_login();

private slots:
    void on__btn_cadastrar_clicked();

    void on__btn_entrar_clicked();

private:
    Ui::janela_login *ui;

    janela_cadastro *cadastro;

    janela_menu_inicial *menu_incial;
};

#endif // JANELA_LOGIN_H
