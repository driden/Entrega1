#ifndef COMPARADORTUPLANATNAT_H
#define COMPARADORTUPLANATNAT_H

typedef unsigned int nat;
#include "Comparador.h"
#include "Tupla.h"

class ComparadorTuplaNatNat : public Comparacion<Tupla<nat,nat>>
{
	public:
	CompRetorno Comparar(const Tupla<nat, nat>& t1, const Tupla<nat, nat>& t2) const override;
};
#endif