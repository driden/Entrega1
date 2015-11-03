#pragma once
#include "Puntero.h"
#include "Iterable.h"
#include "NodoLista.h"

typedef unsigned int nat;

template <class T>
class Lista : public Iterable<T>
{
	public:
	
	~Lista() {}

	virtual void Insertar(const T &x) abstract;

	const virtual nat Largo() const abstract;

	virtual void Eliminar(const T &x) abstract;

	virtual bool Existe(const T &x) abstract;

	virtual Puntero<NodoLista<T>> Recuperar(const T &x) abstract;

	virtual Iterador<T> ObtenerIterador() const override abstract;
	
};