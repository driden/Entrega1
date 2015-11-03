#ifndef COMPARADORINT_CPP
#define COMPARADORINT_CPP
#include "ComparadorInt.h"

CompRetorno ComparadorInt::Comparar(const int& t1, const int& t2) const {
	if (t1 == t2)
	{
		return IGUALES;
	}
	else if (t1 < t2)
	{
		return MENOR;
	}
	else
	{
		return MAYOR;
	}
}
#endif // !COMPARADOR_INT
