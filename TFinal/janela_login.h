#ifndef JANELA_LOGIN_H
#define JANELA_LOGIN_H

#include "conexao.h"
#include <QDialog>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

#include "janela_cadastro.h"
#include "janela_menu_inicial.h"
#include "janela_menu_nutricionista.h"
#include "janela_menu_personal.h"
#include "janela_primeiro_login.h"

namespace Ui {
class janela_login;
}

class janela_login : public QDialog
{
    Q_OBJECT

public:
    explicit janela_login(QWidget *parent = nullptr);
    ~janela_login();

    void playAudio(const QString& audioPath);

private slots:
    void on__btn_cadastrar_clicked();

    void on__btn_entrar_clicked();

private:
    Ui::janela_login *ui;

    QMediaPlayer *player;

    QAudioOutput *audioOutput;

    janela_cadastro *cadastro;

    janela_menu_inicial *menu_incial;

    janela_primeiro_login *primeiro_login;

    janela_menu_nutricionista *menu_nutricionista;

    janela_menu_personal *menu_personal;

    Conexao* conexao;
};

#endif // JANELA_LOGIN_H
