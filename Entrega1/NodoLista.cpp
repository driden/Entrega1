#ifndef NODOLISTA_CPP
#define NODOLISTA_CPP
#include "NodoLista.h"

template<class T>
const T& NodoLista<T>::GetDato() const
{
	return _dato;
}
template <class T>
const Puntero<NodoLista<T>>& NodoLista<T>::GetSiguiente() const
{
	return _sig;
}
template <class T>
void NodoLista<T>::SetSiguiente(const Puntero < NodoLista<T>> &sig)
{
	_sig = sig;
}

template <class T>
Puntero<NodoLista<T>> NodoLista<T>::Clonar() const
{
	Puntero<NodoLista<T>> newNodo = new NodoLista<T>(this->GetDato());
	newNodo->SetSiguiente(this->GetSiguiente());
	return newNodo;
}
#endif
