#include "Sistema.h"
#include "Lista.h"
#include "ListaEnlazada.h"
#include "ComparadorNat.h"
#include "ComparadorTuplaNatNat.h"
#include "SetAcotado.h"
#include "ColaPrioridadAcotada.h"

class ComparadorTuplaNatNat;

Sistema::Sistema()
{
	
}

void Sistema::CrearListaAristas(Array<Tupla<nat, nat>> aristas, nat skip, Puntero<Lista<Tupla<nat, nat>>>& lista)
{
	lista = new ListaEnlazada<Tupla<nat, nat>>(new ComparadorTuplaNatNat());
	for (nat i = 0; i < aristas.Largo; i++)
	{
		if (i == skip)
			continue;
		lista->Insertar(aristas[i]);
	}	
}

// Operación 1
Tupla<TipoRetorno, Iterador<Tupla<nat, nat>>> Sistema::EnlacesCriticos(Iterador<nat> computadoras, Iterador<Tupla<nat, nat>> enlaces)
{
	computadoras.Reiniciar();
	enlaces.Reiniciar();
	IniciarEstructuras(CantIteracionesNat(computadoras));
	
	Array<Tupla<nat, nat>> aristas = ObtenerArrayAristas(enlaces);
	Array<nat> vertices = ObtenerArrayVertices(computadoras);

	Puntero<Lista<Tupla<nat, nat>>> enlacesCriticos = new ListaEnlazada<Tupla<nat, nat>>(new ComparadorTuplaNatNat());
	Puntero<Lista<Tupla<nat, nat>>> aux;
	nat skip = 0; // numero de arista que voy a saltear o "eliminar"
	
	//itero en las aristas que saco
	for (nat i = 0; i < aristas.Largo; i++)
	{
		aux = new ListaEnlazada<Tupla<nat, nat>>(new ComparadorTuplaNatNat());
		CrearListaAristas(aristas, skip, aux);
		Iterador<Tupla<nat, nat>> newIter = aux->ObtenerIterador();		
		
		//creo iterador y va salteando de a una arista
		//itero en todos los vertices sacando una arista
		bool esConexo = false;
		for (nat j = 0; j < vertices.Largo; j++)
		{			
			IniciarEstructuras(vertices.Largo); //pq "elimino" una
			
			
			DepthFirstSearch(vertices[j], newIter, _previous, _visited, vertices);
			bool visiteTodos = _visited[0];
			//estuve en todos los vertices?
			for (nat k = 1; k < _visited.Largo; k++)
			{
				if (!visiteTodos) break;
				visiteTodos &= _visited[k];
			}
				
			if (visiteTodos)
			{
				esConexo = true;
				break;
			}						

		}
		//si el grafo no quedo conexo
		if (!esConexo)
			enlacesCriticos->Insertar(aristas[i]);
		skip++;			
	}
	
	return Tupla<TipoRetorno, Iterador<Tupla<nat, nat>>>(OK, enlacesCriticos->ObtenerIterador());
}


void Sistema::IniciarEstructuras(nat largo)
{
	_previous = Array<nat> (largo, 0);
	_visited = Array<bool>(largo, false);
}

Array<Tupla<nat, nat>> Sistema::ObtenerArrayAristas(Iterador<Tupla<nat, nat>> it)
{
	Array<Tupla<nat, nat>> aristas = Array<Tupla<nat, nat>>(CantIteracionesTuplaNat(it));
	nat i = 0;
	it.Reiniciar();
	
	while (it.HayElemento())
	{
		aristas[i] = it.ElementoActual();
		i++;
		it.Avanzar();
	}
	it.Reiniciar();
	return aristas;
}

Array<nat> Sistema::ObtenerArrayVertices(Iterador<nat> it)
{
	Array<nat> vertices = Array<nat>(CantIteracionesNat(it));
	nat i = 0;
	it.Reiniciar();

	while (it.HayElemento())
	{
		vertices[i] = it.ElementoActual();
		i++;
		it.Avanzar();
	}
	it.Reiniciar();
	return vertices;
}

nat Sistema::ObtenerPosicionEnArray(Array<nat> vertices,nat valor)
{
	for (nat i = 0; i < vertices.Largo; i++)
		if (vertices[i] == valor)
			return i;
	return -1;
}

void Sistema::DepthFirstSearch(nat vertice, Iterador<Tupla<nat, nat>> aristas,Array<nat> &prev, Array<bool> &conocido,Array<nat> &vertices)
{
	conocido[ObtenerPosicionEnArray(vertices,vertice)] = true;
	//busco el vertice
	Puntero<Lista<nat>> vecinos = ObtenerVecinos(vertice, aristas);
	Iterador<nat> iterVecinos = vecinos->ObtenerIterador();
	iterVecinos.Reiniciar();
	while (iterVecinos.HayElemento())
	{
		nat vecino = iterVecinos.ElementoActual();
		if (!conocido[ObtenerPosicionEnArray(vertices,vecino)])
		{
			prev[ObtenerPosicionEnArray(vertices, vecino)] = vertice;
			DepthFirstSearch(vecino, aristas, prev, conocido,vertices);
		}	
		iterVecinos.Avanzar();
	}
}

bool Sistema::GrafoConexo(Array<bool> c1 , Array<bool> c2)
{
	bool conexo = true;

	for (nat i = 0; i < c1.Largo && conexo; i++)
	{
		conexo = conexo && (c1[i] || c2[i]);
	}		

	return conexo;
}
///Devuelve una lista de vecinos del vertice

Puntero<Lista<nat>> Sistema::ObtenerVecinos(nat vertice, Iterador<Tupla<nat, nat>> aristas)
{
	Comparador<nat> cmp = new ComparadorNat();
	Puntero<Lista<nat>> vecinos = new ListaEnlazada<nat>(cmp);
	aristas.Reiniciar();
	while (aristas.HayElemento())
	{
		if (aristas.ElementoActual().ObtenerDato1() == vertice) {
			//agrego al array
			nat actual = aristas.ElementoActual().ObtenerDato2();
			vecinos->Insertar(actual);
		}
		aristas.Avanzar();
	}
	return vecinos;
}

nat Sistema::CantIteracionesNat(Iterador<nat> it)
{
	nat cant = 0;
	it.Reiniciar();

	while (it.HayElemento())
	{
		cant++;
		it.Avanzar();
	}
	it.Reiniciar();
	
	return cant;
}

nat Sistema::CantIteracionesTuplaNat(Iterador<Tupla<nat, nat>> it)
{
	nat cant = 0;
	it.Reiniciar();

	while (it.HayElemento())
	{
		cant++;
		it.Avanzar();
	}
	it.Reiniciar();

	return cant;
}


// Operación 2
Tupla<TipoRetorno, Iterador<Tupla<nat, nat>>> Sistema::AhorroEnlaces(Matriz<nat> & laboratorio)
{

	//pasar todas las aristas(sets de vertices) a una PQUEUE para usar Kruskal
	Tupla<nat, nat> arista;
	nat l = laboratorio.ObtenerLargo();
	Puntero<ColaPrioridad<Tupla<nat, nat>>> pqueue = new ColaPrioridadAcotada<Tupla<nat, nat>>(l*l);
	Array<Puntero<Set<nat>>> compConexa = Array<Puntero<Set<nat>>>(l);
	for (nat m = 0; m < l; m++)
		compConexa[m] = new SetAcotado<nat>(l, new ComparadorNat());
	
	Matriz<nat> arbol= Matriz<nat>(l,l);	

	//recorro la matriz para obtener los sets con su prioridad
	//son aristas no dirigidas, por lo tanto miro de la diagonal para la derecha
	for (nat f = 0; f < laboratorio.Largo; f++) {
		compConexa[f]->Insertar(f);
		for (nat c = 0; c < laboratorio.Largo; c++)
		{
			arbol[f][c] = 0;
			//si tiene arista
			if (laboratorio[f][c])
			{
				arista = Tupla<nat, nat>(f, c);
				pqueue->Insertar(arista, laboratorio[f][c]);
			}				
		}
	}
	//hasta aca el inicio de las estructuras usadas para Kruskal

	bool fin = false;
	while (!fin)
	{
		nat min_prioridad = pqueue->GetMinPrioridad();
		Tupla<nat, nat> arista = pqueue->BorrarMin();
		
		nat posO = arista.ObtenerDato1();
		nat posD = arista.ObtenerDato2();

		if (posO != -1 && posD != -1 && posO != posD)
		{
			arbol[posO][posD] = min_prioridad;
			arbol[posD][posO] = min_prioridad;
			compConexa[posO] = compConexa[posO]->Union(compConexa[posD]);
			compConexa[posD]->VaciarSet();
		}
		fin = pqueue->EstaVacia() || (compConexa[posO]->Tamanio() == l);
	}
	Array<Tupla<nat, nat>> res = Array<Tupla<nat, nat>>(l*l);
	nat tope = 0;
	for (nat x = 0; x < l; x++)
		for (nat y = 0; y < l; y++)
		{
			if (arbol[x][y])
			{
				Tupla<nat, nat> t(x, y);
				res[tope] = t;
				tope++;
			}
		}
	//copiar el array hasta el tope
	Array<Tupla<nat, nat>> arrayTope = Array<Tupla<nat, nat>>(tope);
	Array<Tupla<nat, nat>>::Copiar(res, 0, tope, arrayTope);
	return Tupla<TipoRetorno, Iterador<Tupla<nat, nat>>>(OK, arrayTope.ObtenerIterador());
}


void Sistema::CargarArrayVertices(Iterador<Cadena>& tareas, Array<Cadena> vertices)
{
	nat i = 0;
	while (tareas.HayElemento())
	{
		vertices[i] = tareas.ElementoActual();
		tareas.Avanzar();
		i++;
	}
}

void Sistema::CargarArrayAristas(Iterador<Tupla<Cadena, Cadena>>& precedencias, Array<Tupla<Cadena, Cadena>> aristas)
{
	nat i = 0;
	precedencias.Reiniciar();
	while (precedencias.HayElemento())
	{
		aristas[i] = precedencias.ElementoActual();
		i++;
		precedencias.Avanzar();
	}
}

void Sistema::CargarArrayGradoVerticesEntrantes(Matriz<nat> matrizAdy, Array<nat> gradoEntranteVertices)
{
	//recorro las columnas y por cada una sumo los 1 en las filas
	//busco la posicion en el array y lo updateo
	for (nat c = 0; c < matrizAdy.Largo; c++)
	{
		nat acumulador = 0;
		for (nat f = 0;f < matrizAdy.Largo; f++)
		{
			if (matrizAdy[f][c])
				acumulador++;
		}
		gradoEntranteVertices[c] = acumulador;
		
	}	
}

nat Sistema::GetIndiceVerticeGrado0(Array<nat>& gradoEntranteVertices, Array<bool> &eliminado)
{
	nat indiceCero = 0;
	for (nat i = 0; i < gradoEntranteVertices.Largo; i++)
		if ((gradoEntranteVertices[i] == 0) && !eliminado[i])
		{
			indiceCero = i;
			break;
		}			
	return indiceCero;
}

// Operación 3
Tupla<TipoRetorno, Iterador<Cadena>> Sistema::GerenteProyecto(Iterador<Cadena> tareas, Iterador<Tupla<Cadena, Cadena>> precedencias)
{
	nat largoV = GetCantidadVertices(tareas);
	nat largoA = GetCantidadAristas(precedencias);
	
	Array<Cadena> vertices = Array<Cadena>(largoV);
	CargarArrayVertices(tareas, vertices);
	
	
	Array<Tupla<Cadena, Cadena>> aristas = Array<Tupla<Cadena, Cadena>>(largoA);
	CargarArrayAristas(precedencias, aristas);

	Array<nat> gradoEntranteVertices = Array<nat>(largoV, 0);
	Array<bool> eliminado = Array<bool>(largoV, false);
	Array<nat> ordinal = Array<nat>(largoV, 0);	

	Matriz<nat> matrizAdy = Matriz<nat>(largoV);
	for (nat f = 0; f < largoV; f++)
		for (nat c = 0; c < largoV; c++)
			matrizAdy[f][c] = 0;

	//Cargo la matriz con los valores
	for (nat i = 0; i < largoA; i++)
	{
		nat x = PosicionVerticeEnArray(aristas[i].ObtenerDato1(), vertices);
		nat y = PosicionVerticeEnArray(aristas[i].ObtenerDato2(), vertices);
		matrizAdy[x][y] = 1;
	}
	CargarArrayGradoVerticesEntrantes(matrizAdy, gradoEntranteVertices);
	for (nat cont = 0; cont < largoV; cont++)
	{
		
		nat indice0 = GetIndiceVerticeGrado0(gradoEntranteVertices,eliminado);
		//asigno posicion en el resultado
		ordinal[indice0] = cont;
		eliminado[indice0] = true;
		//tengo que borrar aristas y bajarles el grado
		for (nat w = 0; w < largoV; w++)
		{
			if (matrizAdy[indice0][w] == 1)
			{
				gradoEntranteVertices[w]--;
			}
		}
	}
	Array<Cadena> tareasOrdenadas = Array<Cadena>(largoV);
	for (nat i = 0; i < ordinal.Largo; i++)
	{
		tareasOrdenadas[i] = vertices[ordinal[i]];
	}


	return Tupla<TipoRetorno, Iterador<Cadena>>(OK, tareasOrdenadas.ObtenerIterador());
}
nat Sistema::GetCantidadAristas(Iterador<Tupla<Cadena, Cadena>> it)
{
	nat cant = 0;
	it.Reiniciar();
	while (it.HayElemento())
	{
		cant++;
		it.Avanzar();
	}
	it.Reiniciar();
	return cant;
}

nat Sistema::GetCantidadVertices(Iterador<Cadena> tareas)
{
	nat cantTareas = 0;
	tareas.Reiniciar();
	while (tareas.HayElemento())
	{
		cantTareas++;
		tareas.Avanzar();
	}
	tareas.Reiniciar();
	return cantTareas;
}

nat Sistema::PosicionVerticeEnArray(Cadena tarea, Array<Cadena> tareas)
{
	nat index = 0;
	for (nat i = 0; i < tareas.Largo; i++)
	{
		if (tareas[i] == tarea)
		{
			index = i;
			break;
		}
	}
	return index;
}