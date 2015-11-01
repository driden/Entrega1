#ifndef ISISTEMA_H
#define ISISTEMA_H

#include "Cadena.h"
#include "Iterador.h"
#include "Puntero.h"
#include "TipoRetorno.h"
#include "Tupla.h"
#include "Matriz.h"

class ISistema abstract
{
public:
	virtual ~ISistema(){}

	// Operación 1
	virtual Tupla<TipoRetorno, Iterador<Tupla<nat, nat>>> EnlacesCriticos(Iterador<nat> computadoras, Iterador<Tupla<nat, nat>> enlaces) abstract;

	// Operación 2
	virtual Tupla<TipoRetorno, Iterador<Tupla<nat, nat>>> AhorroEnlaces(Matriz<nat> & laboratorio) abstract;

	// Operación 3
	virtual Tupla<TipoRetorno, Iterador<Cadena>> GerenteProyecto(Iterador<Cadena> tareas, Iterador<Tupla<Cadena, Cadena>> precedencias) abstract;
};

#endif
