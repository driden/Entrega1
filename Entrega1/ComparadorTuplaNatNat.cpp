#ifndef COMPARADORNAT_CPP
#define COMPARADORNAT_CPP

#include "ComparadorTuplaNatNat.h"

CompRetorno ComparadorTuplaNatNat::Comparar(const Tupla<nat,nat> &t1, const Tupla<nat,nat> &t2) const
{
	if (t1.ObtenerDato1() == t2.ObtenerDato1() && t1.ObtenerDato2() == t2.ObtenerDato2())
		return IGUALES;
	
	return DISTINTOS;
}
#endif