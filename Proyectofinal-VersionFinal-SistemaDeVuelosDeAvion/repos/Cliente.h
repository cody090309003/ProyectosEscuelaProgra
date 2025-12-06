#pragma once
#include "Usuario.h"

class Cliente : public Usuario {
public:
    Cliente(int id, const std::string& nombre, const std::string& email, const std::string& password)
        : Usuario(id, nombre, email, password) {
    }
};
