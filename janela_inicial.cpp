#include "janela_inicial.h"
#include "./ui_janela_inicial.h"

janela_inicial::janela_inicial(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_inicial)
{
    ui->setupUi(this);
}

janela_inicial::~janela_inicial()
{
    delete ui;
}

void janela_inicial::on__btn_inicio_clicked()
{
    login = new janela_login();

    //tranforma a janela login na janela inicial
    connect(login, &QDialog::finished, login, &QObject::deleteLater);

    //abre a janela de login
    login->show();

    //fecha a janela da tela inicial
    this->hide();
}

