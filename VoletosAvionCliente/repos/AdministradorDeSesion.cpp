#include "AdministradorDeSesion.h"

bool AdministradorDeSesion::login(const std::string& email,
	const std::string& password,
	const std::vector<std::shared_ptr<Usuario>>& usuarios) {
	for (const auto& usuario : usuarios) {
		if (usuario->ValidarInicioSesion(email, password)) {
			usuarioActivo = usuario;
			return true;
		}
	}
	return false;
}


void AdministradorDeSesion::logout() {
	usuarioActivo.reset();
}

bool AdministradorDeSesion::isLoggedIn() const {
	return usuarioActivo != nullptr;
}

std::shared_ptr<Usuario> AdministradorDeSesion::getUsuarioActivo() const {
	return usuarioActivo;
}