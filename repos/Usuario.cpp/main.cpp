#include <iostream>
#include "Usuario.h"
using namespace std;

int main()
{
    Usuario u;

    int opcion;

    do
    {
        cout << "---- SISTEMA DE USUARIOS ----\n";
        cout << "1. Registrar usuario\n";
        cout << "2. Iniciar sesion\n";
        cout << "3. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1: {
            string nombre, correo, password;

            cout << "Nombre: ";
            cin >> nombre;

            cout << "Correo: ";
            cin >> correo;

            cout << "Password: ";
            cin >> password;

            if (u.RegistrarUsuario(nombre, correo, password))
                cout << "Usuario registrado con exito.\n";
            else
                cout << "Error al registrar usuario.\n";

            break;
        }
        case 2:
            if (u.IniciarSesion())
                cout << "Sesion iniciada correctamente.\n";
            else
                cout << "Datos incorrectos.\n";
            break;

        case 3:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opcion invalida.\n";
            break;
        }

    } while (opcion != 3);

    return 0;
}
