#include <QMessageBox>
#include <QString>

class MessageStyle {
public:
    static void showError(QWidget* parent, const QString& message) {
        QMessageBox msgBox(parent);
        msgBox.setWindowTitle("Erro");
        msgBox.setText(message);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStandardButtons(QMessageBox::Ok);

        // Define o estilo CSS
        msgBox.setStyleSheet(
            "QMessageBox {"
            "    background-color: #4A90E2;"
            "    border: 2px solid #ffffff;"
            "    padding: 10px;"
            "}"
            "QMessageBox QLabel {"
            "    font-family: 'Segoe UI';"
            "    font-weight: bold;"
            "    font-size: 18px;"
            "    color: #ffffff;"
            "}"
            "QPushButton {"
            "    background-color: #4A90E2;"
            "    color: #ffffff;"
            "    font-family: 'Segoe UI';"
            "    font-weight: bold;"
            "    font-size: 20px;"
            "    border: 2px solid #ffffff;"
            "    border-radius: 18px;"
            "    padding: 10px 20px;"
            "}"
            "QPushButton:hover {"
            "    background-color: #53A3FF;"
            "    border-radius: 12px;"
            "}"
            );

        msgBox.exec();
    }

    static void showWarning(QWidget* parent, const QString& message) {
        QMessageBox msgBox(parent);
        msgBox.setWindowTitle("Atenção");
        msgBox.setText(message);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);

        msgBox.setStyleSheet(
            "QMessageBox {"
            "    background-color: #4A90E2;"
            "    border: 2px solid #ffffff;"
            "    padding: 10px;"
            "}"
            "QMessageBox QLabel {"
            "    font-family: 'Segoe UI';"
            "    font-weight: bold;"
            "    font-size: 18px;"
            "    color: #ffffff;"
            "    min-width: 200px;"
            "}"
            "QPushButton {"
            "    background-color: #4A90E2;"
            "    color: #ffffff;"
            "    font-family: 'Segoe UI';"
            "    font-weight: bold;"
            "    font-size: 20px;"
            "    border: 2px solid #ffffff;"
            "    border-radius: 18px;"
            "    padding: 10px 20px;"
            "}"
            "QPushButton:hover {"
            "    background-color: #53A3FF;"
            "    border-radius: 12px;"
            "}"
            );

        msgBox.exec();
    }

    static void showSuccess(QWidget* parent, const QString& message) {
        QMessageBox msgBox(parent);
        msgBox.setWindowTitle("Sucesso");
        msgBox.setText(message);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);

        msgBox.setStyleSheet(
            "QMessageBox {"
            "    background-color: #4A90E2;"
            "    border: 2px solid #ffffff;"
            "}"
            "QMessageBox QLabel {"
            "    font-family: 'Segoe UI';"
            "    font-weight: bold;"
            "    font-size: 18px;"
            "    color: #ffffff;"
            "    min-width: 200px;"
            "}"
            "QPushButton {"
            "    background-color: #4A90E2;"
            "    color: #ffffff;"
            "    font-family: 'Segoe UI';"
            "    font-weight: bold;"
            "    font-size: 20px;"
            "    border: 2px solid #ffffff;"
            "    border-radius: 18px;"
            "    padding: 10px 20px;"
            "}"
            "QPushButton:hover {"
            "    background-color: #53A3FF;"
            "    border-radius: 12px;"
            "}"
            );

        msgBox.exec();
    }
};
