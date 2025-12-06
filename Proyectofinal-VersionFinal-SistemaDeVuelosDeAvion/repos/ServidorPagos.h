#pragma once
#include <string>

class ServidorPagos {
public:
    bool procesarPago(double monto, const std::string& numeroTarjeta);
};
