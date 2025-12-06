#pragma once
#include <string>
#include <vector>
#include "Vuelo.h"

class Reservacion {
private:
    int idUsuario;
    Vuelo vuelo;
    std::string asiento;
    double costo;

public:
    Reservacion(int idUsuario,
        const Vuelo& vuelo,
        const std::string& asiento,
        double costo);

    int getIdUsuario() const;
    const Vuelo& getVuelo() const;
    const std::string& getAsiento() const;
    double getCosto() const;

    std::string serializar() const;
    static Reservacion deserializar(const std::string& linea);
};

bool guardarReservacionEnArchivo(const Reservacion& r, const std::string& nombreArchivo);
std::vector<Reservacion> cargarReservacionesDeArchivo(const std::string& nombreArchivo);
void mostrarReservacionesDeUsuario(int idUsuario, const std::string& nombreArchivo);
