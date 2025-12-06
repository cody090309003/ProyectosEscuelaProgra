#pragma once
#include <string>

class ServidorPagos; 

class Pago {
private:
    int idPago;
    double monto;
    std::string numeroTarjeta;
    std::string estado; 

public:
    Pago(int idPago, double monto, const std::string& numeroTarjeta);

    bool procesar(ServidorPagos& servidor);

    double getMonto() const { return monto; }
    const std::string& getNumeroTarjeta() const { return numeroTarjeta; }
    const std::string& getEstado() const { return estado; }
};
