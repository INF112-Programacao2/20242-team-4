#include "janela_menu_inicial.h"
#include "ui_janela_menu_inicial.h"

janela_menu_inicial::janela_menu_inicial(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_menu_inicial)
{
    ui->setupUi(this);
}

janela_menu_inicial::~janela_menu_inicial()
{
    delete ui;
}

void janela_menu_inicial::on_pushButton_6_clicked()
{

}

