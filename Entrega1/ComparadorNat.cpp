#ifndef COMPARADORTUPLANATNAT_CPP
#define COMPARADORTUPLANATNAT_CPP

#include "ComparadorNat.h"

CompRetorno ComparadorNat::Comparar(const nat& t1, const nat& t2) const
{
	if (t1 == t2)
		return IGUALES;
	if (t1 < t2)
		return MENOR;
	if (t1 > t2)
		return MAYOR;

	return DISTINTOS;
}
#endif