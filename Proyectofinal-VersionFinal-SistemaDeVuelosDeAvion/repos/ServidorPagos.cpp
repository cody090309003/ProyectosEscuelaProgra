#include "ServidorPagos.h"
#include <iostream>

bool ServidorPagos::procesarPago(double monto, const std::string& numeroTarjeta)
{
    std::cout << "\n[ServidorPagos] Recibiendo solicitud de pago...\n";
    std::cout << "  Monto: $" << monto << '\n';

    std::string ultimos4 = numeroTarjeta;
    if (numeroTarjeta.size() > 4) {
        ultimos4 = numeroTarjeta.substr(numeroTarjeta.size() - 4);
    }

    std::cout << "  Tarjeta: **** **** **** " << ultimos4 << '\n';
    std::cout << "[ServidorPagos] Pago aprobado.\n\n";
    return true;
}
