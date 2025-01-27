#include "janela_edita_usuario.h"
#include "ui_janela_edita_usuario.h"

janela_edita_usuario::janela_edita_usuario(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_edita_usuario)
{
    ui->setupUi(this);
}

janela_edita_usuario::~janela_edita_usuario()
{
    delete ui;
}
