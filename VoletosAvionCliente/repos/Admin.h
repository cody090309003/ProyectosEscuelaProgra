#pragma once
#include "Usuario.h"

class Admin : public Usuario {
public:
    Admin(int id, const std::string& nombre, const std::string& email, const std::string& password)
        : Usuario(id, nombre, email, password) {
    }
};
