#ifndef LISTAITERACION_H
#define LISTAITERACION_H

#include "Iteracion.h"
#include "NodoLista.h"

template<class T>
class ListaIteracion : public Iteracion<T>
{
	private:
	Puntero<NodoLista<T>> _lista;
	Puntero<NodoLista<T>> _inicio;

	public:

	ListaIteracion<T>(const Puntero<NodoLista<T>> nodo)
	{
		_lista = nodo;
		_inicio = nodo;
	}

	~ListaIteracion<T>() {};

	bool HayElemento() const override;
	const T& ElementoActual() const override;
	void Avanzar() override;
	void Reiniciar() override;

	Puntero<Iteracion<T>> Clonar() const override;
	//AUX
	Puntero<NodoLista<T>> ClonarLista(const Puntero<NodoLista<T>> lista) const;
};
#endif
#include "ListaIteracion.cpp"