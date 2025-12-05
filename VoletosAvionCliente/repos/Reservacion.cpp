#include "Reservacion.h"
#include <sstream>
#include <fstream>
#include <iostream>

Reservacion::Reservacion(int idUsuario, const Vuelo& vuelo)
    : idUsuario(idUsuario), vuelo(vuelo) {
}

int Reservacion::getIdUsuario() const {
    return idUsuario;
}

const Vuelo& Reservacion::getVuelo() const {
    return vuelo;
}

// Formato: idUsuario;idVuelo;fecha;hora;origen;destino;numeroAvion
std::string Reservacion::serializar() const {
    std::ostringstream oss;
    oss << idUsuario << ';'
        << vuelo.getId() << ';'
        << vuelo.getFecha() << ';'
        << vuelo.getHora() << ';'
        << vuelo.getOrigen() << ';'
        << vuelo.getDestino() << ';'
        << vuelo.getNumeroAvion();
    return oss.str();
}

Reservacion Reservacion::deserializar(const std::string& linea) {
    std::istringstream iss(linea);
    std::string token;
    std::vector<std::string> campos;

    while (std::getline(iss, token, ';')) {
        campos.push_back(token);
    }

    if (campos.size() != 7) {
        throw std::runtime_error("Línea de reservación inválida: " + linea);
    }

    int idUsuario = std::stoi(campos[0]);
    int idVuelo = std::stoi(campos[1]);
    std::string fecha = campos[2];
    std::string hora = campos[3];
    std::string origen = campos[4];
    std::string destino = campos[5];
    std::string numeroAvion = campos[6];

    Vuelo vuelo(idVuelo, fecha, hora, origen, destino, numeroAvion);
    return Reservacion(idUsuario, vuelo);
}

bool guardarReservacionEnArchivo(const Reservacion& r, const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo, std::ios::app);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo de reservaciones." << std::endl;
        return false;
    }
    archivo << r.serializar() << std::endl;
    return true;
}

std::vector<Reservacion> cargarReservacionesDeArchivo(const std::string& nombreArchivo) {
    std::vector<Reservacion> reservaciones;
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        // Si no existe el archivo, regresamos lista vacía
        return reservaciones;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;
        try {
            reservaciones.push_back(Reservacion::deserializar(linea));
        }
        catch (const std::exception& e) {
            std::cerr << "Error al leer reservación: " << e.what() << std::endl;
        }
    }
    return reservaciones;
}

void mostrarReservacionesDeUsuario(int idUsuario, const std::string& nombreArchivo) {
    auto reservaciones = cargarReservacionesDeArchivo(nombreArchivo);
    std::cout << "\n--- Reservaciones del usuario " << idUsuario << " ---\n";
    bool hay = false;
    for (const auto& r : reservaciones) {
        if (r.getIdUsuario() == idUsuario) {
            const Vuelo& v = r.getVuelo();
            std::cout << "Vuelo " << v.getId()
                << " | " << v.getOrigen() << " -> " << v.getDestino()
                << " | Fecha: " << v.getFecha()
                << " Hora: " << v.getHora()
                << " | Avión: " << v.getNumeroAvion() << '\n';
            hay = true;
        }
    }
    if (!hay) {
        std::cout << "No tienes reservaciones registradas.\n";
    }
}
