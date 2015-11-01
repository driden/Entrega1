#ifndef SISTEMA_H
#define SISTEMA_H

#include "ISistema.h"

class Sistema : public ISistema
{
public:
	Sistema();

	// Operación 1
	Tupla<TipoRetorno, Iterador<Tupla<nat, nat>>> EnlacesCriticos(Iterador<nat> computadoras, Iterador<Tupla<nat, nat>> enlaces) override;

	// Operación 2
	Tupla<TipoRetorno, Iterador<Tupla<nat, nat>>> AhorroEnlaces(Matriz<nat> & laboratorio) override;

	// Operación 3
	Tupla<TipoRetorno, Iterador<Cadena>> GerenteProyecto(Iterador<Cadena> tareas, Iterador<Tupla<Cadena, Cadena>> precedencias) override;

private:
};

#endif
