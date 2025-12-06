#pragma once
#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>

class Usuario {
protected:
    int id;
    std::string nombre;
    std::string correo;
    std::string password;

public:
    // Constructor
    Usuario(int id, const std::string& nombre, const std::string& correo, const std::string& password)
        : id(id), nombre(nombre), correo(correo), password(password) {
    }

    // Getters
    int getId() const { return id; }
    std::string getNombre() const { return nombre; }
    std::string getEmail()  const { return correo; }
    std::string getPassword() const { return password; }

    // Validación en memoria (login)
    bool ValidarInicioSesion(const std::string& enteredEmail,
        const std::string& enteredPassword) const
    {
        return correo == enteredEmail && password == enteredPassword;
    }

    // ==========================================================
    //     SECCIÓN DE "SERVIDOR": ARCHIVO usuarios.txt
    // ==========================================================

    // Guarda usuario al final del archivo
    static bool RegistrarUsuarioEnArchivo(int id,
        const std::string& nombre,
        const std::string& correo,
        const std::string& password,
        const std::string& nombreArchivo)
    {
        std::ofstream file(nombreArchivo, std::ios::app);
        if (!file.is_open()) {
            std::cout << "[ERROR] No se pudo abrir el archivo: " << nombreArchivo << "\n";
            return false;
        }

        // Formato: id|nombre|correo|password
        file << id << '|'
            << nombre << '|'
            << correo << '|'
            << password << '\n';

        return true;
    }

    // Cargar todos los usuarios desde el archivo
    static std::vector<std::shared_ptr<Usuario>>
        ObtenerUsuariosDesdeArchivo(const std::string& nombreArchivo)
    {
        std::vector<std::shared_ptr<Usuario>> usuarios;
        std::ifstream file(nombreArchivo);

        if (!file.is_open()) {
            // No existe archivo → no hay usuarios aún
            return usuarios;
        }

        std::string linea;
        while (std::getline(file, linea)) {
            if (linea.empty()) continue;

            // Separar por '|'
            size_t p1 = linea.find('|');
            size_t p2 = linea.find('|', p1 + 1);
            size_t p3 = linea.find('|', p2 + 1);

            if (p1 == std::string::npos || p2 == std::string::npos || p3 == std::string::npos)
                continue;

            int id = std::stoi(linea.substr(0, p1));
            std::string nombre = linea.substr(p1 + 1, p2 - p1 - 1);
            std::string correo = linea.substr(p2 + 1, p3 - p2 - 1);
            std::string password = linea.substr(p3 + 1);

            usuarios.push_back(std::make_shared<Usuario>(id, nombre, correo, password));
        }

        return usuarios;
    }
};

#endif
