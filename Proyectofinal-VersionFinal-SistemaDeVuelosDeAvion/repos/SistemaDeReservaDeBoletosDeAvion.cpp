#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <string>

#include "AdministradorDeSesion.h"
#include "Reservacion.h"
#include "Cliente.h"
#include "Admin.h"
#include "Menu.h"
#include "Usuario.h"
#include "Pago.h"
#include "ServidorPagos.h"

bool esAdmin(const std::shared_ptr<Usuario>& u) {
    return (std::dynamic_pointer_cast<Admin>(u) != nullptr);
}

int ejecutarSistema() {
    const std::string ARCHIVO_RESERVACIONES = "reservaciones.txt";
    const std::string ARCHIVO_USUARIOS = "usuarios.txt";

    AdministradorDeSesion adminSesion;
    ServidorPagos servidorPagos;

    std::vector<std::shared_ptr<Usuario>> usuarios =
        Usuario::ObtenerUsuariosDesdeArchivo(ARCHIVO_USUARIOS);

    bool existeAdmin = false;
    for (const auto& u : usuarios) {
        if (u->getEmail() == "admin@correo.com") {
            existeAdmin = true;
            break;
        }
    }

    if (!existeAdmin) {
        auto adminDefault = std::make_shared<Admin>(
            1, "Administrador", "admin@correo.com", "admin123");
        usuarios.push_back(adminDefault);

        Usuario::RegistrarUsuarioEnArchivo(
            adminDefault->getId(),
            adminDefault->getNombre(),
            adminDefault->getEmail(),
            adminDefault->getPassword(),
            ARCHIVO_USUARIOS
        );
    }

    int siguienteIdUsuario = 0;
    for (const auto& u : usuarios) {
        if (u->getId() > siguienteIdUsuario) {
            siguienteIdUsuario = u->getId();
        }
    }
    siguienteIdUsuario++;

    int siguienteIdVuelo = 1;
    int siguienteIdPago = 1;
    int opcion = -1;

    do {
        bool usuarioEsAdmin = adminSesion.isLoggedIn() && esAdmin(adminSesion.getUsuarioActivo());
        mostrarMenuPrincipal(usuarioEsAdmin);
        std::cin >> opcion;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (opcion == 1) {
            std::string nombre, email, password;
            std::cout << "Nombre: ";
            std::cin >> nombre;
            std::cout << "Email: ";
            std::cin >> email;
            std::cout << "Password: ";
            std::cin >> password;

            auto nuevoCliente = std::make_shared<Cliente>(
                siguienteIdUsuario++, nombre, email, password);
            usuarios.push_back(nuevoCliente);

            if (Usuario::RegistrarUsuarioEnArchivo(
                nuevoCliente->getId(),
                nuevoCliente->getNombre(),
                nuevoCliente->getEmail(),
                nuevoCliente->getPassword(),
                ARCHIVO_USUARIOS))
            {
                std::cout << "Cliente registrado y guardado correctamente.\n";
            }
            else {
                std::cout << "Cliente registrado, pero no se pudo guardar en archivo.\n";
            }
        }
        else if (opcion == 2) {
            std::string email, password;
            std::cout << "Email: ";
            std::cin >> email;
            std::cout << "Password: ";
            std::cin >> password;

            if (adminSesion.login(email, password, usuarios)) {
                std::cout << "Inicio de sesión exitoso. Bienvenido, "
                    << adminSesion.getUsuarioActivo()->getNombre() << "!\n";
            }
            else {
                std::cout << "Correo o contraseña incorrectos.\n";
            }
        }
        else if (opcion == 3) {
            if (!adminSesion.isLoggedIn()) {
                std::cout << "Debes iniciar sesión primero.\n";
                continue;
            }
            int idUsuario = adminSesion.getUsuarioActivo()->getId();

            std::string fecha, hora, origen, destino, numeroAvion;
            std::string asiento;
            double costo = 0.0;

            std::cout << "Fecha del vuelo (dd/mm/aaaa): ";
            std::cin >> fecha;
            std::cout << "Hora del vuelo (hh:mm): ";
            std::cin >> hora;
            std::cout << "Origen: ";
            std::cin >> origen;
            std::cout << "Destino: ";
            std::cin >> destino;
            std::cout << "Número de avión: ";
            std::cin >> numeroAvion;
            std::cout << "Asiento (ej. 12A): ";
            std::cin >> asiento;
            std::cout << "Costo del boleto: ";
            std::cin >> costo;

            Vuelo vuelo(siguienteIdVuelo++, fecha, hora, origen, destino, numeroAvion);

            std::cout << "\nResumen de tu vuelo:\n";
            std::cout << vuelo.getDescripcionCorta()
                << " | Avión: " << vuelo.getNumeroAvion() << "\n";
            std::cout << "Asiento: " << asiento
                << " | Costo: $" << costo << "\n";

            std::string numeroTarjeta;
            std::cout << "\nNúmero de tarjeta de crédito (sin espacios): ";
            std::cin >> numeroTarjeta;

            Pago pago(siguienteIdPago++, costo, numeroTarjeta);

            if (pago.procesar(servidorPagos)) {
                std::cout << "Estado del pago: " << pago.getEstado() << "\n";
                Reservacion r(idUsuario, vuelo, asiento, costo);
                if (guardarReservacionEnArchivo(r, ARCHIVO_RESERVACIONES)) {
                    std::cout << "Reservación guardada correctamente.\n";
                }
            }
            else {
                std::cout << "El pago no se pudo procesar. Reservación cancelada.\n";
            }
        }
        else if (opcion == 4) {
            if (!adminSesion.isLoggedIn()) {
                std::cout << "Debes iniciar sesión primero.\n";
                continue;
            }
            int idUsuario = adminSesion.getUsuarioActivo()->getId();
            mostrarReservacionesDeUsuario(idUsuario, ARCHIVO_RESERVACIONES);
        }
        else if (opcion == 5) {
            if (adminSesion.isLoggedIn()) {
                std::cout << "Cerrando sesión de "
                    << adminSesion.getUsuarioActivo()->getNombre() << "...\n";
                adminSesion.logout();
            }
            else {
                std::cout << "No hay sesión activa.\n";
            }
        }
        else if (opcion == 6 && usuarioEsAdmin) {
            int opAdmin = -1;
            do {
                mostrarMenuAdmin();
                std::cin >> opAdmin;
                if (!std::cin) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                if (opAdmin == 1) {
                    std::string nombre, email, password;
                    std::cout << "Nombre: ";
                    std::cin >> nombre;
                    std::cout << "Email: ";
                    std::cin >> email;
                    std::cout << "Password: ";
                    std::cin >> password;

                    auto nuevoCliente = std::make_shared<Cliente>(
                        siguienteIdUsuario++, nombre, email, password);
                    usuarios.push_back(nuevoCliente);

                    if (Usuario::RegistrarUsuarioEnArchivo(
                        nuevoCliente->getId(),
                        nuevoCliente->getNombre(),
                        nuevoCliente->getEmail(),
                        nuevoCliente->getPassword(),
                        ARCHIVO_USUARIOS))
                    {
                        std::cout << "Cliente agregado y guardado correctamente.\n";
                    }
                    else {
                        std::cout << "Cliente agregado, pero no se pudo guardar en archivo.\n";
                    }
                }
                else if (opAdmin == 2) {
                    int idPromover;
                    std::cout << "ID del usuario a convertir en administrador: ";
                    std::cin >> idPromover;
                    bool encontrado = false;
                    for (auto& u : usuarios) {
                        if (u->getId() == idPromover) {
                            auto adminPtr = std::make_shared<Admin>(
                                u->getId(), u->getNombre(), u->getEmail(), u->getPassword());
                            u = adminPtr;
                            std::cout << "Usuario " << idPromover << " ahora es administrador.\n";
                            encontrado = true;
                            break;
                        }
                    }
                    if (!encontrado) {
                        std::cout << "No se encontró un usuario con ese ID.\n";
                    }
                }
            } while (opAdmin != 0);
        }
        else if (opcion == 0) {
            std::cout << "Saliendo del sistema...\n";
        }
        else {
            std::cout << "Opción inválida.\n";
        }

    } while (opcion != 0);

    return 0;
}

int main() {
    return ejecutarSistema();
}
