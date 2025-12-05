#pragma once
#include <iostream>


inline void mostrarMenuPrincipal(bool esAdmin) {
    std::cout << "\n=== Sistema de Reserva de Boletos ===" << std::endl;
    std::cout << "1. Registrar cliente" << std::endl;
    std::cout << "2. Iniciar sesión" << std::endl;


    if (esAdmin || !esAdmin) { 
        std::cout << "3. Reservar vuelo" << std::endl;
        std::cout << "4. Ver mis reservaciones" << std::endl;
        std::cout << "5. Cerrar sesión" << std::endl;
    }

 
    if (esAdmin) {
        std::cout << "6. Administrar usuarios (solo Admin)" << std::endl;
    }

    std::cout << "0. Salir" << std::endl;
    std::cout << "Opción: ";
}

inline void mostrarMenuAdmin() {
    std::cout << "\n=== Menú administrador ===" << std::endl;
    std::cout << "1. Agregar nuevo usuario cliente" << std::endl;
    std::cout << "2. Convertir usuario a administrador" << std::endl;
    std::cout << "0. Volver" << std::endl;
    std::cout << "Opción: ";
}

