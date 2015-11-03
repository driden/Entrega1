#ifndef NODOCP_H
#define NODOCP_H
#include <Comparador.h>
typedef unsigned int nat;

template <class T>
class NodoCP
{
	private:
	// Menor prioridad = Mayor Urgencia
	T _element;
	nat _prioridad;

	public:
	~NodoCP(){}
	NodoCP(){}
	NodoCP(const T &e, const nat &p)
	{
		_element = e;
		_prioridad = p;
	}

	T GetElemento() const;
	nat GetPrioridad() const;
	void SetElemento(const T &e);
	void SetPrioridad(const nat p);
	Comparador<NodoCP<T>> GetComparador();
};
#endif
#include "NodoCP.cpp"