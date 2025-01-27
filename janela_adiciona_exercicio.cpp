#include "janela_adiciona_exercicio.h"
#include "ui_janela_adiciona_exercicio.h"

janela_adiciona_exercicio::janela_adiciona_exercicio(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_adiciona_exercicio)
{
    ui->setupUi(this);
}

janela_adiciona_exercicio::~janela_adiciona_exercicio()
{
    delete ui;
}
