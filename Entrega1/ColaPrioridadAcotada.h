#ifndef COLAPRIORIDADACOTADA_H
#define COLAPRIORIDADACOTADA_H

#include "ColaPrioridad.h"
#include "Array.h"
#include "NodoCP.h"


template<class T>
class ColaPrioridadAcotada : public ColaPrioridad < T >
{
private:
	Array<Puntero<NodoCP<T>>> _pqueue;
	nat _tope;
	Comparador<nat> _comp;
	Comparador<T> _comp_tipo;

public:
	~ColaPrioridadAcotada() {}

	ColaPrioridadAcotada<T>(nat max);

	void Insertar(const T &x, const nat p) override;

	T BorrarMin() override ;

	nat Tamanio() override;

	bool EstaVacia() override;

	void ActualizarPrioridad(const T elem, nat nuevaPrioridad) override;

	void SetComparadorTipo(const Comparador<T> compTipo);

	nat GetMinPrioridad() override;
};

#endif
#include "ColaPrioridadAcotada.cpp"
