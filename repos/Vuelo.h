#pragma once
#include <string>
#include <iostream>

class Vuelo {
private:
    int idVuelo;
    std::string fecha;
    std::string hora;
    std::string origen;
    std::string destino;
    std::string numeroAvion;

public:
    Vuelo() : idVuelo(0) {}

    Vuelo(int idVuelo,
        const std::string& fecha,
        const std::string& hora,
        const std::string& origen,
        const std::string& destino,
        const std::string& numeroAvion)
        : idVuelo(idVuelo),
        fecha(fecha),
        hora(hora),
        origen(origen),
        destino(destino),
        numeroAvion(numeroAvion) {
    }

    int getId() const { return idVuelo; }
    const std::string& getFecha() const { return fecha; }
    const std::string& getHora() const { return hora; }
    const std::string& getOrigen() const { return origen; }
    const std::string& getDestino() const { return destino; }
    const std::string& getNumeroAvion() const { return numeroAvion; }

    std::string getDescripcionCorta() const {
        return origen + " -> " + destino + " (" + fecha + " " + hora + ")";
    }
};






		
		
		
		
