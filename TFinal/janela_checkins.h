#ifndef JANELA_CHECKINS_H
#define JANELA_CHECKINS_H

#include <QMainWindow>
#include <QMessageBox>

#include <QTextEdit>
#include <QTextBlock>
#include <QFileDialog>
#include <QPixmap>
#include <QTextCursor>
#include <QTextDocument>

#include "conexao.h"
#include "competicao.h"

namespace Ui {
class janela_checkins;
}

class ImageTextEdit : public QTextEdit {
    Q_OBJECT

public:
    explicit ImageTextEdit(QWidget *parent = nullptr) : QTextEdit(parent) {}

    void insertImage() {
        QString filePath = QFileDialog::getOpenFileName(this, "Selecionar Imagem", "", "Imagens (.png .jpg.jpeg *.bmp)");
        if (!filePath.isEmpty()) {
            QTextCursor cursor = this->textCursor();
            cursor.insertImage(filePath);
        }
    }
};

class janela_checkins : public QMainWindow
{
    Q_OBJECT

public:
    explicit janela_checkins(QWidget *parent = nullptr);
    ~janela_checkins();

    void setUserId(int id);

private:
    Ui::janela_checkins *ui;

    int _user_id;

    Conexao* conexao;

signals:
    void voltarMenuInicial();

private slots:
    void on__btn_voltar_clicked();
    void on__btn_validar_clicked();
    void inserirImagem();
};

#endif // JANELA_CHECKINS_H
