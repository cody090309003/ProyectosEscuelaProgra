#pragma once
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Usuario {
public:
    int id = 0;
    string nombre;
    string correo;
    string password;

    Usuario(int id, string nombre, string correo, string password)
        : id(id), nombre(nombre), correo(correo), password(password) {
    }

    Usuario() = default;

    bool IniciarSesion();
    bool ValidarInicioSesion(const string& enteredEmail,
        const string& enteredPassword) const;

    bool RegistrarUsuario(string nombre, string correo, string password);
    vector<shared_ptr<Usuario>> ObtenerUsuarios() const;

    int getId() const { return id; }
    string getCorreo() const { return correo; }
};
