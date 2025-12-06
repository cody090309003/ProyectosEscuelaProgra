#pragma once
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>

class Usuario {
protected:
    int id;
    std::string nombre;
    std::string correo;
    std::string password;

public:
    Usuario(int id,
        const std::string& nombre,
        const std::string& correo,
        const std::string& password)
        : id(id), nombre(nombre), correo(correo), password(password) {
    }

    virtual ~Usuario() = default;

    // -------- Getters --------
    int getId() const { return id; }
    const std::string& getNombre() const { return nombre; }
    const std::string& getCorreo() const { return correo; }
    const std::string& getEmail() const { return correo; } // alias
    const std::string& getPassword() const { return password; }

    // -------- Login en memoria --------
    bool ValidarInicioSesion(const std::string& enteredEmail,
        const std::string& enteredPassword) const {
        return (correo == enteredEmail && password == enteredPassword);
    }

    // =========================================================
    //        "SERVIDOR" DE USUARIOS BASADO EN ARCHIVO
    // =========================================================

    // Guarda un usuario al final del archivo
    static bool RegistrarUsuarioEnArchivo(
        int id,
        const std::string& nombre,
        const std::string& correo,
        const std::string& password,
        const std::string& nombreArchivo)
    {
        std::ofstream file(nombreArchivo, std::ios::app);
        if (!file.is_open()) {
            std::cerr << "No se pudo abrir el archivo de usuarios: "
                << nombreArchivo << std::endl;
            return false;
        }

        // Formato: id|nombre|correo|password
        file << id << '|'
            << nombre << '|'
            << correo << '|'
            << password << '\n';

        return true;
    }

    // Lee todos los usuarios del archivo
    static std::vector<std::shared_ptr<Usuario>>
        ObtenerUsuariosDesdeArchivo(const std::string& nombreArchivo)
    {
        std::vector<std::shared_ptr<Usuario>> usuarios;

        std::ifstream file(nombreArchivo);
        if (!file.is_open()) {
            // Si el archivo no existe, regresamos lista vacía
            return usuarios;
        }

        std::string linea;
        while (std::getline(file, linea)) {
            if (linea.empty()) continue;

            std::stringstream ss(linea);
            std::string token;
            std::vector<std::string> campos;

            // Dividir por '|'
            while (std::getline(ss, token, '|')) {
                campos.push_back(token);
            }

            if (campos.size() != 4) {
                std::cerr << "Línea inválida en usuarios.txt: "
                    << linea << std::endl;
                continue;
            }

            int id = std::stoi(campos[0]);
            std::string nombre = campos[1];
            std::string correo = campos[2];
            std::string password = campos[3];

            usuarios.push_back(
                std::make_shared<Usuario>(id, nombre, correo, password)
            );
        }

        return usuarios;
    }
};
