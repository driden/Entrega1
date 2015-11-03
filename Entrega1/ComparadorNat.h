#ifndef COMPARADORNAT_H
#define COMPARADORNAT_H

typedef unsigned int nat;
#include "Comparador.h"

class ComparadorNat : public Comparacion<nat>
{
public:
	CompRetorno Comparar(const nat& t1, const nat& t2) const override;
};
#endif