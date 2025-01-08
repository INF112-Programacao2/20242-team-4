#include "janela_dieta_usuario.h"
#include "ui_janela_dieta_usuario.h"

janela_dieta_usuario::janela_dieta_usuario(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_dieta_usuario)
{
    ui->setupUi(this);
}

janela_dieta_usuario::~janela_dieta_usuario()
{
    delete ui;
}
