#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Usuario.h"

class AdministradorDeSesion {
private:
    std::shared_ptr<Usuario> usuarioActivo;

public:
    bool login(const std::string& email,
        const std::string& password,
        const std::vector<std::shared_ptr<Usuario>>& usuarios);

    void logout();

    bool isLoggedIn() const;

    std::shared_ptr<Usuario> getUsuarioActivo() const;
};