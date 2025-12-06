#include "Pago.h"
#include "ServidorPagos.h"

Pago::Pago(int idPago, double monto, const std::string& numeroTarjeta)
    : idPago(idPago),
    monto(monto),
    numeroTarjeta(numeroTarjeta),
    estado("pendiente")
{
}

bool Pago::procesar(ServidorPagos& servidor)
{
    bool aprobado = servidor.procesarPago(monto, numeroTarjeta);
    estado = aprobado ? "aprobado" : "rechazado";
    return aprobado;
}
