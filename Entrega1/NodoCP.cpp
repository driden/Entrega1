#ifndef NODOCP_CPP
#define NODOCP_CPP
#include "NodoCP.h"
#include "ComparadorInt.h"

template <class T>
T NodoCP<T>::GetElemento() const 
{
	return _element;
}

template <class T>
nat NodoCP<T>::GetPrioridad() const
{
	return _prioridad;
}

template <class T>
void NodoCP<T>::SetElemento(const T& e)
{
	this->_element = e;
}

template <class T>
void NodoCP<T>::SetPrioridad(const nat p)
{
	this->_prioridad = p;
}

template <class T>
Comparador<NodoCP<T>> NodoCP<T>::GetComparador()
{
	return new ComparadorInt();
}
#endif
