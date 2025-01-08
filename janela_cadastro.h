#ifndef JANELA_CADASTRO_H
#define JANELA_CADASTRO_H

#include <QMainWindow>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>

namespace Ui {
class janela_cadastro;
}

class janela_cadastro : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_cadastro(QWidget *parent = nullptr);
    ~janela_cadastro();

private slots:
    void on__btn_cadastrar_clicked();

private:
    Ui::janela_cadastro *ui;

signals:
    void voltarLogin();
};

#endif // JANELA_CADASTRO_H
