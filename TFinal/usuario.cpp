#include "usuario.h"

usuario::usuario() {}

void usuario::setNome(const QString& nome) {
    user_nome = nome;
}

void usuario::setEmail(const QString& email) {
    user_email = email;
}

void usuario::setSenha(const QString& senha) {
    user_senha = senha;
}


bool usuario::validarEmail(const QString& email) {
    // Verifica se contém @ e tem formato básico de email
    return email.contains("@") && email.contains(".");
}

bool usuario::emailJaCadastrado(Conexao *conexao, const QString &email) {
    QSqlQuery query(conexao->getConexao());
    query.prepare("SELECT COUNT(*) FROM table_usuario WHERE user_email = ?");
    query.addBindValue(email);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }

    return false;
}

bool usuario::validarCadastro(const QString &nome, const QString &email, const QString &senha, const QString &confirmaSenha) {
    if (nome.isEmpty() || email.isEmpty() || senha.isEmpty() || confirmaSenha.isEmpty()) {
        MessageStyle::showWarning(nullptr, "Por favor, preencha todos os campos!");
        return false;
    }

    if (senha != confirmaSenha) {
        MessageStyle::showWarning(nullptr, "Senhas incompatíveis!");
        return false;
    }

    if (!validarEmail(email)) {
        MessageStyle::showWarning(nullptr, "Email inválido!");
        return false;
    }

    return true;
}

bool usuario::cadastrar(Conexao* conexao) {
    if (emailJaCadastrado(conexao, user_email)) {
        MessageStyle::showWarning(nullptr, "Este email já está cadastrado!");
        return false;
    }

    QSqlQuery query(conexao->getConexao());

    query.prepare("INSERT INTO table_usuario (user_nome, user_email, user_senha, user_tipo) VALUES (?, ?, ?, ?)");
    query.addBindValue(user_nome);
    query.addBindValue(user_email);
    query.addBindValue(user_senha);
    query.addBindValue(1);  // usuário padrão

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Erro ao inserir registro:" << query.lastError().text();
        return false;
    }
}
