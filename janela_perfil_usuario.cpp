#include "janela_perfil_usuario.h"
#include "ui_janela_perfil_usuario.h"

janela_perfil_usuario::janela_perfil_usuario(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_perfil_usuario)
{
    ui->setupUi(this);
}

janela_perfil_usuario::~janela_perfil_usuario()
{
    delete ui;
}
