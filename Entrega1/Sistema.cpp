#include "Sistema.h"

Sistema::Sistema()
{
}

// Operación 1
Tupla<TipoRetorno, Iterador<Tupla<nat, nat>>> Sistema::EnlacesCriticos(Iterador<nat> computadoras, Iterador<Tupla<nat, nat>> enlaces)
{
	return Tupla<TipoRetorno, Iterador<Tupla<nat, nat>>>(NO_IMPLEMENTADA, NULL);
}

// Operación 2
Tupla<TipoRetorno, Iterador<Tupla<nat, nat>>> Sistema::AhorroEnlaces(Matriz<nat> & laboratorio)
{
	return Tupla<TipoRetorno, Iterador<Tupla<nat, nat>>>(NO_IMPLEMENTADA, NULL);
}

// Operación 3
Tupla<TipoRetorno, Iterador<Cadena>> Sistema::GerenteProyecto(Iterador<Cadena> tareas, Iterador<Tupla<Cadena, Cadena>> precedencias)
{
	return Tupla<TipoRetorno, Iterador<Cadena>>(NO_IMPLEMENTADA, NULL);
}
