#pragma once

#include "Set.h"
#include "Array.h"

template <class T>
class SetAcotado : public Set<T>
{
	private:
	Array<T> _set;
	nat _tope;
	Comparador<T> _comp;
	

	public:
	SetAcotado(nat tamanio, Comparador<T> comp);

	void Insertar(const T &x) override;
	void Eliminar(const T &x) override;
	bool EsVacio() const override;
	bool EsLleno() const override;
	nat Tamanio() const override;
	bool Pertenece(const T &x) const override;

	Puntero<Set<T>> Union(Puntero<Set<T>> A) const override;
	Puntero<Set<T>> Interseccion(Puntero<Set<T>> A) const override;
	Puntero<Set<T>> Diferencia(Puntero<Set<T>> A) const override;

	Iterador<T> ObtenerIterador() const override;
	void VaciarSet() override;

	
};


#include "SetAcotado.cpp"