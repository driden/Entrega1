#ifndef NODOLISTA_H
#define NODOLISTA_H

#include "Puntero.h"

template <class T>
class NodoLista
{
	T _dato;
	Puntero<NodoLista<T>> _sig;
public:
	NodoLista<T>(const T& dato){
		_dato = dato;
		_sig = nullptr;
	};
	const T& GetDato() const;
	const Puntero<NodoLista<T>>& GetSiguiente() const;
	void SetSiguiente(const Puntero<NodoLista<T>> &sig);
	

	Puntero<NodoLista<T>> Clonar() const;


};
#endif
#include "NodoLista.cpp"
