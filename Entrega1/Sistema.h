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
	void CargarArrayVertices(Iterador<Cadena>& tareas, Array<Cadena> vertices);
	void CargarArrayAristas(Iterador<Tupla<Cadena, Cadena>>& precedencias, Array<Tupla<Cadena, Cadena>> aristas);
	void CargarArrayGradoVerticesEntrantes(Matriz<nat> matrizAdy, Array<nat> gradoEntranteVertices);
	nat GetIndiceVerticeGrado0(Array<nat>& gradoEntranteVertices,Array<bool> &eliminado);
	// Operación 3
	Tupla<TipoRetorno, Iterador<Cadena>> GerenteProyecto(Iterador<Cadena> tareas, Iterador<Tupla<Cadena, Cadena>> precedencias) override;
	nat GetCantidadAristas(Iterador<Tupla<Cadena, Cadena>> it);
	nat GetCantidadVertices(Iterador<Cadena> tareas);
	nat PosicionVerticeEnArray(Cadena tarea, Array<Cadena> tareas);
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
