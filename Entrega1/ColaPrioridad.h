#pragma once
#include "Puntero.h"
typedef unsigned int nat;

template <class T>
class ColaPrioridad abstract
{
	public:

	virtual ~ColaPrioridad() {}

	virtual void Insertar(const T &x, const nat p) abstract;

	virtual T BorrarMin() abstract;

	virtual nat Tamanio() abstract;

	virtual bool EstaVacia() abstract;
	
	virtual void ActualizarPrioridad(const T elem, nat nuevaPrioridad) abstract;

	virtual nat GetMinPrioridad() abstract;
};