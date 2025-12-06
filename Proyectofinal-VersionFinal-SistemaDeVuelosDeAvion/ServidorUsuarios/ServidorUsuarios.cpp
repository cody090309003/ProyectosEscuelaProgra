#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Usuario.h"

int main() {
    const std::string ARCHIVO_USUARIOS = "usuarios.txt";

    std::cout << "=========================================\n";
    std::cout << "        SERVIDOR DE USUARIOS\n";
    std::cout << "=========================================\n\n";

    // Cargar usuarios existentes
    auto usuarios = Usuario::ObtenerUsuariosDesdeArchivo(ARCHIVO_USUARIOS);
    std::cout << "[SERVIDOR] Usuarios cargados desde archivo: "
        << usuarios.size() << "\n";

    int opcion = -1;
    do {
        std::cout << "\n--- MENU SERVIDOR ---\n";
        std::cout << "1. Listar usuarios\n";
        std::cout << "2. Registrar usuario manualmente\n";
        std::cout << "0. Apagar servidor\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (opcion == 1) {
            std::cout << "\n[ SERVIDOR ] Lista de usuarios:\n";
            for (const auto& u : usuarios) {
                std::cout << "ID: " << u->getId()
                    << " | Nombre: " << u->getNombre()
                    << " | Correo: " << u->getEmail()
                    << '\n';
            }
            if (usuarios.empty()) {
                std::cout << "No hay usuarios registrados.\n";
            }
        }
        else if (opcion == 2) {
            std::string nombre, correo, password;
            int nuevoId = 1;

            // calcular siguiente ID
            for (const auto& u : usuarios) {
                if (u->getId() >= nuevoId) {
                    nuevoId = u->getId() + 1;
                }
            }

            std::cout << "Nombre: ";
            std::cin >> nombre;
            std::cout << "Correo: ";
            std::cin >> correo;
            std::cout << "Password: ";
            std::cin >> password;

            auto nuevoUsuario =
                std::make_shared<Usuario>(nuevoId, nombre, correo, password);

            usuarios.push_back(nuevoUsuario);

            if (Usuario::RegistrarUsuarioEnArchivo(
                nuevoUsuario->getId(),
                nuevoUsuario->getNombre(),
                nuevoUsuario->getEmail(),
                nuevoUsuario->getPassword(),
                ARCHIVO_USUARIOS))
            {
                std::cout << "[SERVIDOR] Usuario guardado.\n";
            }
            else {
                std::cout << "[SERVIDOR] Error al guardar.\n";
            }
        }
        else if (opcion == 0) {
            std::cout << "[SERVIDOR] Apagando servidor...\n";
        }
        else {
            std::cout << "Opción inválida.\n";
        }

    } while (opcion != 0);

    return 0;
}
