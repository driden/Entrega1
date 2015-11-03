#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H


#include "Lista.h"

template<class T>
class ListaEnlazada : public Lista<T>
{
	nat cantElementos;
	Puntero<NodoLista<T>> _lista;
	Comparador<T> _comp;
	Iterador<T> _iter;

	public:

	ListaEnlazada(const Comparador<T> comp)
	{
		_lista = nullptr;
		_comp = comp;
		cantElementos = 0;
		_iter = nullptr;
	}

	void Insertar(const T &x) override;

	const nat Largo() const override;

	void Eliminar(const T &x) override;

	bool Existe(const T &x) override;

	Puntero<NodoLista<T>> Recuperar(const T &x) override;

	Iterador<T> ObtenerIterador() const override;

};
#endif
#include "ListaEnlazada.cpp"




