#ifndef SISTEMA_H
#define SISTEMA_H

#include "ISistema.h"
#include "Lista.h"

class Sistema : public ISistema
{
	private:
	Array<nat> _previous;
	Array<bool> _visited;
public:
	Sistema();

	void CrearListaAristas(Array<Tupla<nat, nat>> aristas, nat skip, Puntero<Lista<Tupla<nat, nat>>>& lista);
	// Operación 1
	Tupla<TipoRetorno, Iterador<Tupla<nat, nat>>> EnlacesCriticos(Iterador<nat> computadoras, Iterador<Tupla<nat, nat>> enlaces) override;

	// Operación 2
	Tupla<TipoRetorno, Iterador<Tupla<nat, nat>>> AhorroEnlaces(Matriz<nat> & laboratorio) override;

	// Operación 3
	Tupla<TipoRetorno, Iterador<Cadena>> GerenteProyecto(Iterador<Cadena> tareas, Iterador<Tupla<Cadena, Cadena>> precedencias) override;
	
	void IniciarEstructuras(nat largo);
	Array<Tupla<nat, nat>> ObtenerArrayAristas(Iterador<Tupla<nat, nat>> it);
	Array<nat> ObtenerArrayVertices(Iterador<nat> it);
	nat ObtenerPosicionEnArray(Array<nat> vertices, nat valor);
	void DepthFirstSearch(nat vertice, Iterador<Tupla<nat, nat>> aristas, Array<nat>& prev, Array<bool>& conocido, Array<nat>& vertices);
	bool GrafoConexo(Array<bool> c1, Array<bool> c2);
	Puntero<Lista<nat>> ObtenerVecinos(nat vertice, Iterador<Tupla<nat, nat>> aristas);
	nat CantIteracionesNat(Iterador<nat> it);
	nat CantIteracionesTuplaNat(Iterador<Tupla<nat, nat>> it);
	
private:
};

#endif
