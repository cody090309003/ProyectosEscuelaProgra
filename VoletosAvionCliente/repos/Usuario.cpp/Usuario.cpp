#include "Usuario.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool Usuario::IniciarSesion()
{
    cout << "Usuario: ";
    cin >> correo;

    cout << "Password: ";
    cin >> password;

    vector<shared_ptr<Usuario>> usuarios = ObtenerUsuarios();

    for (const shared_ptr<Usuario>& usuario : usuarios)
    {
        if (usuario->ValidarInicioSesion(correo, password))
        {
            cout << "ID: " << usuario->getId() << endl;
            cout << "Correo: " << usuario->getCorreo() << endl;
            return true;
        }
    }

    cout << "Usuario o contraseña incorrectos.\n";
    return false;
}

bool Usuario::ValidarInicioSesion(const string& enteredEmail,
                                  const string& enteredPassword) const
{
    return (correo == enteredEmail && password == enteredPassword);
}

vector<shared_ptr<Usuario>> Usuario::ObtenerUsuarios() const
{
    vector<shared_ptr<Usuario>> usuarios;
    ifstream inputFile("usuarios.txt");

    if (!inputFile.is_open())
    {
        cout << "Error al abrir el archivo.\n";
        return usuarios;
    }

    string line;
    vector<string> words;
    string word;

    while (getline(inputFile, line))
    {
        stringstream ss(line);

        while (ss >> word)
            words.push_back(word);

        if (words.size() >= 4)
        {
            usuarios.push_back(
                make_shared<Usuario>(
                    stoi(words[0]),
                    words[1],
                    words[2],
                    words[3]
                )
            );
        }

        words.clear();
    }

    inputFile.close();
    return usuarios;
}

bool Usuario::RegistrarUsuario(string nombre, string correo, string password)
{
    ofstream file("usuarios.txt", ios::app);

    if (!file.is_open())
    {
        cout << "Error al abrir archivo para registrar usuario.\n";
        return false;
    }

    // generar ID simple
    int newId = ObtenerUsuarios().size() + 1;

    file << newId << " " << nombre << " " << correo << " " << password << "\n";

    file.close();
    return true;
}
